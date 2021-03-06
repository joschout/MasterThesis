#include "TreeTraverser.h"

using namespace std;

int TreeTraverser::firstNode(double tx0, double ty0, double tz0, double txm, double tym, double tzm){
	unsigned char answer = 0;	// initialize to 00000000

	//calculate the entry face of the current voxel
	// => max(tx0, ty0, tz0)

	// select the entry plane and set bits
	if(tx0 > ty0){
		if(tx0 > tz0){ 
			// tx0 is maximum
			// PLANE YZ -> VOXELS 0,1,2,3
			if(tym < tx0) answer|=2;	// set bit at position 1
			// answer = answer OR 0000 0010
			if(tzm < tx0) answer|=1;	// set bit at position 0
			// answer = answer OR 000 0001
			return (int) answer;
		}
	} else {
		if(ty0 > tz0){
			// ty0 is maximum
			// PLANE XZ -> VOXELS  0, 1, 4, 5
			if(txm < ty0) answer|=4;	// set bit at position 2
			// answer = answer OR 0000 1000
			if(tzm < ty0) answer|=1;	// set bit at position 0
			// answer = answer OR 0000 0001
			return (int) answer;
		}
	}//tz0 is maximum
	// PLANE XY -> VOXELS 0, 2, 4, 6
	if(txm < tz0) answer|=4;	// set bit at position 2
	// answer = answer OR 0000 0100
	if(tym < tz0) answer|=2;	// set bit at position 1
	// answer = answer OR 0000 0010

	return (int) answer;
}

// perform PUSH, POP or ADVANCE
void TreeTraverser::step(){
	stepcount++;
	// if the stack is empty, we're done
	if(stack.empty()) return;

	// define some aliases to make code readable
	vec3_d& t0 = stack.back().t0; 
	vec3_d& t1 = stack.back().t1; 
	vec3_d& tm = stack.back().tm;

	//POP
	// if we're in a terminal node or if we visited all children of that node (next child = 8), 
	// or if the t1 values have become negative, pop the current node from the stack
	if(stack.back().nextchild == 8 || stack.back().node->isLeaf()){
		stack.pop_back();
		return;
	}

	// PUSH
	// we haven't looked at any child in this voxel yet: pick the first and push down
	if(stack.back().nextchild == -1){
		// calculate midpoint and save it in stack
		tm = 0.5*(t0+t1);
		// calculate first node
		stack.back().nextchild = firstNode(t0[0],t0[1],t0[2],tm[0],tm[1],tm[2]);
	}

	// ADVANCE
	// let's look at the next child in this voxel
	switch (stack.back().nextchild)
	{
	case 0: { 
		stack.back().nextchild = newNode(tm[0],4,tm[1],2,tm[2],1);
		if(stack.back().node->hasChild(a)){
			TraversalNodeInfo_ info = buildNodeInfo(t0[0],t0[1],t0[2],tm[0],tm[1],tm[2],octree->getNode(stack.back().node->getChildPos(a)));
			stack.push_back(info);
		} return;}
	case 1: { 
		stack.back().nextchild = newNode(tm[0],5,tm[1],3,t1[2],8);
		if(stack.back().node->hasChild(1^a)){
			TraversalNodeInfo_ info = buildNodeInfo(t0[0],t0[1],tm[2],tm[0],tm[1],t1[2],octree->getNode(stack.back().node->getChildPos(1^a)));
			stack.push_back(info);
		} return;}
	case 2: { 
		stack.back().nextchild = newNode(tm[0],6,t1[1],8,tm[2],3);
		if(stack.back().node->hasChild(2^a)){
			TraversalNodeInfo_ info = buildNodeInfo(t0[0],tm[1],t0[2],tm[0],t1[1],tm[2],octree->getNode(stack.back().node->getChildPos(2^a)));
			stack.push_back(info);
		} return;}
	case 3: { 
		stack.back().nextchild = newNode(tm[0],7,t1[1],8,t1[2],8);
		if(stack.back().node->hasChild(3^a)){
			TraversalNodeInfo_ info = buildNodeInfo(t0[0],tm[1],tm[2],tm[0],t1[1],t1[2],octree->getNode(stack.back().node->getChildPos(3^a)));
			stack.push_back(info);
		} return;}
	case 4: { 
		stack.back().nextchild = newNode(t1[0],8,tm[1],6,tm[2],5);
		if(stack.back().node->hasChild(4^a)){
			TraversalNodeInfo_ info = buildNodeInfo(tm[0],t0[1],t0[2],t1[0],tm[1],tm[2],octree->getNode(stack.back().node->getChildPos(4^a)));
			stack.push_back(info);
		} return;}
	case 5: { 
		stack.back().nextchild = newNode(t1[0],8,tm[1],7,t1[2],8);
		if(stack.back().node->hasChild(5^a)){
			TraversalNodeInfo_ info = buildNodeInfo(tm[0],t0[1],tm[2],t1[0],tm[1],t1[2],octree->getNode(stack.back().node->getChildPos(5^a)));
			stack.push_back(info);
		} return;}
	case 6: { 
		stack.back().nextchild = newNode(t1[0],8,t1[1],8,tm[2],7);
		if(stack.back().node->hasChild(6^a)){
			TraversalNodeInfo_ info = buildNodeInfo(tm[0],tm[1],t0[2],t1[0],t1[1],tm[2],octree->getNode(stack.back().node->getChildPos(6^a)));
			stack.push_back(info);
		} return;}
	case 7: { 
		stack.back().nextchild = 8;
		if(stack.back().node->hasChild(7^a)){
			TraversalNodeInfo_ info = buildNodeInfo(tm[0],tm[1],tm[2],t1[0],t1[1],t1[2],octree->getNode(stack.back().node->getChildPos(7^a)));
			stack.push_back(info);
		} return;}
	}
}

void TreeTraverser::initTraversal(){
	stepcount = 0;
	a = 0;

	original_ray = ray;

	// fixes for rays with negative direction
	if(ray.direction[0] < 0.0f){
		ray.origin[0] = octree->size[0] - ray.origin[0];
		ray.direction[0] = - ray.direction[0];
		a |= 4 ; //bitwise OR (latest bits are XYZ)
	}
	if(ray.direction[1] < 0.0f){
		ray.origin[1] = octree->size[1] - ray.origin[1];
		ray.direction[1] = - ray.direction[1];
		a |= 2 ; 
	}
	if(ray.direction[2] > 0.0f){
		ray.origin[2] = octree->size[2] - ray.origin[2];
		ray.direction[2] = - ray.direction[2];
		a |= 1 ; 
	}

	double tx0 = (octree->min[0] - ray.origin[0]) * (1.0f / ray.direction[0]);
	double tx1 = (octree->max[0] - ray.origin[0]) * (1.0f / ray.direction[0]);
	double ty0 = (octree->min[1] - ray.origin[1]) * (1.0f / ray.direction[1]);
	double ty1 = (octree->max[1] - ray.origin[1]) * (1.0f / ray.direction[1]);
	double tz0 = (octree->min[2] - ray.origin[2]) * (1.0f / ray.direction[2]);
	double tz1 = (octree->max[2] - ray.origin[2]) * (1.0f / ray.direction[2]);

//	cout << "tz0 = (" << octree->min[2] << " - " << ray.origin[2] << ")*" << 1.0f / ray.direction[2] << endl;
//	cout << "tz0 = " << tz0 << endl;
//	cout << "tz1 = (" << octree->max[2] << " - " << ray.origin[2] << ")*/" << 1.0f / ray.direction[2] << endl;
//	cout << "tz1 = " << tz1 << endl;

	//cout << "tx0: " << tx0 << ", ty0: " << ty0 << ", tz0: " << tz0 << endl;
	//cout << "tx1: " << tx1 << ", ty1: " << ty1 << ", tz1: " << tz1 << endl;

	bool condition3D = max(max(tx0, ty0), tz0) < min(min(tx1, ty1), tz1);

	if(condition3D){
		// push root node on stack
		stack.push_back(buildNodeInfo(tx0,ty0,tz0,tx1,ty1,tz1,octree->getRootNode()));
		return;
	}
	// push nothing on the stack
}

TreeTraverser::~TreeTraverser(void)
{
}