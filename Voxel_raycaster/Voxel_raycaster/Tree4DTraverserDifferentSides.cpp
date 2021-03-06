#include "Tree4DTraverserDifferentSides.h"
#include <cassert>

using namespace std;

int Tree4DTraverserDifferentSides::nextChildNodeToCheck_16(
	double txm, int x, double tym, int y, double tzm, int z,
	double ttm, int t) {

	if (txm < tym) 
	{
		if (txm < tzm)
		{
			if (txm < ttm)
			{
				// txm is minimum
				return x; // YZT volume
			}
		}
	}
	// tym <= txm
	// ==> tym OR tzm OR ttm is min
	if (tym < tzm)
	{
		if (tym < ttm) {
			// tym is minimum
			return y;
			// XZT volume
		}
	}
	// tzm <= tym <= txm
	//==> tzm or ttm is min
	if (tzm < ttm)
	{
		// tzm is minimum
		return z; // XYT volume;
	}

	//ttm is minimum
	return t; // XYZ volume;*/
}

int Tree4DTraverserDifferentSides::nextChildNodeToCheck_8(double txm, int x, double tym, int y, double tzm, int z)
{
	if (txm < tym) {
		if (txm < tzm)
		{ // txm minimal
			return x;
		} // YZ plane
	}

	// tym <= txm
	// ==> tym OR tzm is min
	if (tym < tzm)
	{ // tym minimal
		return y;
	} // XZ plane
	
	// tzm <= tym <= txm
	return z; // XY plane;
}

//int Tree4DTraverserDifferentSides::nextChildNodeToCheck_2(double txm, int x, double tym, int y, double tzm, int z)
//{
//}

/*
Returns the number of the child node we have to check 
after we have checked the current child node to check.
*/
int Tree4DTraverserDifferentSides::nextChildNodeToCheck_16(int currentNextChildNumber, vec4_d &t0, vec4_d &t1, vec4_d &tm)
{
	assert(currentNextChildNumber < 17);
	switch (currentNextChildNumber)
	{
	case 0:  return nextChildNodeToCheck_16(tm[0], 4, tm[1], 2, tm[2], 1, tm[3], 8);
	case 1:  return nextChildNodeToCheck_16(tm[0], 5, tm[1], 3, t1[2], 16, tm[3], 9);
	case 2:  return nextChildNodeToCheck_16(tm[0], 6, t1[1], 16, tm[2], 3, tm[3], 10);
	case 3:  return nextChildNodeToCheck_16(tm[0], 7, t1[1], 16, t1[2], 16, tm[3], 11);
	case 4:  return nextChildNodeToCheck_16(t1[0], 16, tm[1], 6, tm[2], 5, tm[3], 12);
	case 5:  return nextChildNodeToCheck_16(t1[0], 16, tm[1], 7, t1[2], 16, tm[3], 13);
	case 6:  return nextChildNodeToCheck_16(t1[0], 16, t1[1], 16, tm[2], 7, tm[3], 14);
	case 7:  return nextChildNodeToCheck_16(t1[0], 16, t1[1], 16, t1[2], 16, tm[3], 15);
	case 8:  return nextChildNodeToCheck_16(tm[0], 12, tm[1], 10, tm[2], 9, t1[3], 16);
	case 9:  return nextChildNodeToCheck_16(tm[0], 13, tm[1], 11, t1[2], 16, t1[3], 16);
	case 10: return nextChildNodeToCheck_16(tm[0], 14, t1[1], 16, tm[2], 11, t1[3], 16);
	case 11: return nextChildNodeToCheck_16(tm[0], 15, t1[1], 16, t1[2], 16, t1[3], 16);
	case 12: return nextChildNodeToCheck_16(t1[0], 16, tm[1], 14, tm[2], 13, t1[3], 16);
	case 13: return nextChildNodeToCheck_16(t1[0], 16, tm[1], 15, t1[2], 16, t1[3], 16);
	case 14: return nextChildNodeToCheck_16(t1[0], 16, t1[1], 16, tm[2], 15, t1[3], 16);
	case 15: return 16;
	}
	return 0;
}

int Tree4DTraverserDifferentSides::nextChildNodeToCheck_8(int currentNextChildNumber, vec4_d &t0, vec4_d &t1, vec4_d &tm)
{
	
	/* The case of an octary node
		0 -> 0 -> 0,1
		1 -> 2 -> 2,3
		2 -> 4 -> 4,5
		3 -> 6 -> 6,7
		4 -> 8 -> 8,9
		5 -> 10 -> 10,11
		6 -> 12 -> 12,13
		7 -> 14 -> 14,15
	*/
	assert(currentNextChildNumber < 17);
	switch (currentNextChildNumber)
	{
	case 0:
	case 8:
		return nextChildNodeToCheck_8(tm[0], 4, tm[1], 2, tm[2], 1);
	case 1:
	case 9:
		return nextChildNodeToCheck_8(tm[0], 5, tm[1], 3, t1[2], 16);
	case 2:
	case 10:
		return nextChildNodeToCheck_8(tm[0], 6, t1[1], 16, tm[2], 3);
	case 3:
	case 11:
		return nextChildNodeToCheck_8(tm[0], 7, t1[1], 16, t1[2], 16);
	case 4:
	case 12:
		return nextChildNodeToCheck_8(t1[0], 16, tm[1], 6, tm[2], 5);
	case 5:
	case 13:
		return nextChildNodeToCheck_8(t1[0], 16, tm[1], 7, t1[2], 16);
	case 6:
	case 14:
		return nextChildNodeToCheck_8(t1[0], 16, t1[1], 16, tm[2], 7);
	case 7:
	case 15:
		return 16;//					    , 16,      , 16,      , 16
	}
	return 0;
}


int Tree4DTraverserDifferentSides::nextChildNodeToCheck_2(int currentNextChildNumber, vec4_d &t0, vec4_d &t1, vec4_d &tm)
{
	assert(currentNextChildNumber < 17);
	switch (currentNextChildNumber)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		return 8;
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		return 16;
	}
	return 0;
}



int Tree4DTraverserDifferentSides::nextChildNodeToCheck(int currentNextChildNumber, vec4_d &t0, vec4_d &t1, vec4_d &tm)
{

	switch(stack_TraversalInfo_about_Node4Ds.back().maxAmountOfChildren)
	{
	case TWO:     return nextChildNodeToCheck_2(currentNextChildNumber, t0, t1, tm);
	case EIGHT:   return nextChildNodeToCheck_8(currentNextChildNumber, t0, t1, tm);
	case SIXTEEN: return nextChildNodeToCheck_16(currentNextChildNumber, t0, t1, tm);

	default: return nextChildNodeToCheck_16(currentNextChildNumber, t0, t1, tm);
	}
}


TraversalInfo_About_Node4D Tree4DTraverserDifferentSides::buildNodeInfo_16(int nextChildNumber, vec4_d& t0, vec4_d& t1, vec4_d& tm, vec4_d min, vec4_d max, const Node4D* node)
{
	double& x_min = min[0];
	double& y_min = min[1];
	double& z_min = min[2];
	double& t_min = min[3];

	double& x_max = max[0];
	double& y_max = max[1];
	double& z_max = max[2];
	double& t_max = max[3];

	double x_mid = (max[0] + min[0]) / 2.0;
	double y_mid = (max[1] + min[1]) / 2.0;
	double z_mid = (max[2] + min[2]) / 2.0;
	double t_mid = (max[3] + min[3]) / 2.0;

	switch (nextChildNumber)
	{
	case 0:  return buildNodeInfo_struct(t0[0], t0[1], t0[2], t0[3], tm[0], tm[1], tm[2], tm[3],
		vec4_d(x_min, y_min, z_min, t_min), vec4_d(x_mid, y_mid, z_mid, t_mid), node, SIXTEEN);
	case 1:  return buildNodeInfo_struct(t0[0], t0[1], tm[2], t0[3], tm[0], tm[1], t1[2], tm[3],
		vec4_d(x_min, y_min, z_mid, t_min), vec4_d(x_mid, y_mid, z_max, t_mid), node, SIXTEEN);
	case 2:  return buildNodeInfo_struct(t0[0], tm[1], t0[2], t0[3], tm[0], t1[1], tm[2], tm[3],
		vec4_d(x_min, y_mid, z_min, t_min), vec4_d(x_mid, y_max, z_mid, t_mid), node, SIXTEEN);
	case 3:  return buildNodeInfo_struct(t0[0], tm[1], tm[2], t0[3], tm[0], t1[1], t1[2], tm[3],
		vec4_d(x_min, y_mid, z_mid, t_min), vec4_d(x_mid, y_max, z_max, t_mid), node, SIXTEEN);
	case 4:  return buildNodeInfo_struct(tm[0], t0[1], t0[2], t0[3], t1[0], tm[1], tm[2], tm[3],
		vec4_d(x_mid, y_min, z_min, t_min), vec4_d(x_max, y_mid, z_mid, t_mid), node, SIXTEEN);
	case 5:  return buildNodeInfo_struct(tm[0], t0[1], tm[2], t0[3], t1[0], tm[1], t1[2], tm[3],
		vec4_d(x_mid, y_min, z_mid, t_min), vec4_d(x_max, y_mid, z_max, t_mid), node, SIXTEEN);
	case 6:  return buildNodeInfo_struct(tm[0], tm[1], t0[2], t0[3], t1[0], t1[1], tm[2], tm[3],
		vec4_d(x_mid, y_mid, z_min, t_min), vec4_d(x_max, y_max, z_mid, t_mid), node, SIXTEEN);
	case 7:  return buildNodeInfo_struct(tm[0], tm[1], tm[2], t0[3], t1[0], t1[1], t1[2], tm[3],
		vec4_d(x_mid, y_mid, z_mid, t_min), vec4_d(x_max, y_max, z_max, t_mid), node, SIXTEEN);
	case 8:  return buildNodeInfo_struct(t0[0], t0[1], t0[2], tm[3], tm[0], tm[1], tm[2], t1[3],
		vec4_d(x_min, y_min, z_min, t_mid), vec4_d(x_mid, y_mid, z_mid, t_max), node, SIXTEEN);
	case 9:  return buildNodeInfo_struct(t0[0], t0[1], tm[2], tm[3], tm[0], tm[1], t1[2], t1[3],
		vec4_d(x_min, y_min, z_mid, t_mid), vec4_d(x_mid, y_mid, z_max, t_max), node, SIXTEEN);
	case 10: return buildNodeInfo_struct(t0[0], tm[1], t0[2], tm[3], tm[0], t1[1], tm[2], t1[3],
		vec4_d(x_min, y_mid, z_min, t_mid), vec4_d(x_mid, y_max, z_mid, t_max), node, SIXTEEN);
	case 11: return buildNodeInfo_struct(t0[0], tm[1], tm[2], tm[3], tm[0], t1[1], t1[2], t1[3],
		vec4_d(x_min, y_mid, z_mid, t_mid), vec4_d(x_mid, y_max, z_max, t_max), node, SIXTEEN);
	case 12: return buildNodeInfo_struct(tm[0], t0[1], t0[2], tm[3], t1[0], tm[1], tm[2], t1[3],
		vec4_d(x_mid, y_min, z_min, t_mid), vec4_d(x_max, y_mid, z_mid, t_max), node, SIXTEEN);
	case 13: return buildNodeInfo_struct(tm[0], t0[1], tm[2], tm[3], t1[0], tm[1], t1[2], t1[3],
		vec4_d(x_mid, y_min, z_mid, t_mid), vec4_d(x_max, y_mid, z_max, t_max), node, SIXTEEN);
	case 14: return buildNodeInfo_struct(tm[0], tm[1], t0[2], tm[3], t1[0], t1[1], tm[2], t1[3],
		vec4_d(x_mid, y_mid, z_min, t_mid), vec4_d(x_max, y_max, z_mid, t_max), node, SIXTEEN);
	case 15: return buildNodeInfo_struct(tm[0], tm[1], tm[2], tm[3], t1[0], t1[1], t1[2], t1[3],
		vec4_d(x_mid, y_mid, z_mid, t_mid), vec4_d(x_max, y_max, z_max, t_max), node, SIXTEEN);
	}
	return{};
}

TraversalInfo_About_Node4D Tree4DTraverserDifferentSides::buildNodeInfo_8(int nextChildNumber, vec4_d& t0, vec4_d& t1, vec4_d& tm, vec4_d min, vec4_d max, const Node4D* node)
{
	double& x_min = min[0];
	double& y_min = min[1];
	double& z_min = min[2];
	double& t_min = min[3];

	double x_mid = (max[0] + min[0]) / 2.0;
	double y_mid = (max[1] + min[1]) / 2.0;
	double z_mid = (max[2] + min[2]) / 2.0;
	//double t_mid = (max[3] + min[3]) / 2;

	double& x_max = max[0];
	double& y_max = max[1];
	double& z_max = max[2];
	double& t_max = max[3];

	AmountOfChildren maxAmountOfChildren = getMaxAmountOfChildren(node, longestDimension);

	switch(nextChildNumber)
	{
	case 0:
	case 8:
		return buildNodeInfo_struct(t0[0], t0[1], t0[2], t0[3], tm[0], tm[1], tm[2], t1[3],
				vec4_d(x_min, y_min, z_min, t_min), vec4_d(x_mid, y_mid, z_mid, t_max), node, maxAmountOfChildren);
	case 1:
	case 9:
		return buildNodeInfo_struct(t0[0], t0[1], tm[2], t0[3], tm[0], tm[1], t1[2], t1[3],
		vec4_d(x_min, y_min, z_mid, t_min), vec4_d(x_mid, y_mid, z_max, t_max), node, maxAmountOfChildren);
	case 2:
	case 10:
		return buildNodeInfo_struct(t0[0], tm[1], t0[2], t0[3], tm[0], t1[1], tm[2], t1[3],
		vec4_d(x_min, y_mid, z_min, t_min), vec4_d(x_mid, y_max, z_mid, t_max), node, maxAmountOfChildren);
	case 3:
	case 11:
		return buildNodeInfo_struct(t0[0], tm[1], tm[2], t0[3], tm[0], t1[1], t1[2], t1[3],
		vec4_d(x_min, y_mid, z_mid, t_min), vec4_d(x_mid, y_max, z_max, t_max), node, maxAmountOfChildren);
	case 4:
	case 12:
		return buildNodeInfo_struct(tm[0], t0[1], t0[2], t0[3], t1[0], tm[1], tm[2], t1[3],
		vec4_d(x_mid, y_min, z_min, t_min), vec4_d(x_max, y_mid, z_mid, t_max), node, maxAmountOfChildren);
	case 5:
	case 13:
		return buildNodeInfo_struct(tm[0], t0[1], tm[2], t0[3], t1[0], tm[1], t1[2], t1[3],
		vec4_d(x_mid, y_min, z_mid, t_min), vec4_d(x_max, y_mid, z_max, t_max), node, maxAmountOfChildren);
	case 6:
	case 14:
		return buildNodeInfo_struct(tm[0], tm[1], t0[2], t0[3], t1[0], t1[1], tm[2], t1[3],
		vec4_d(x_mid, y_mid, z_min, t_min), vec4_d(x_max, y_max, z_mid, t_max), node, maxAmountOfChildren);
	case 7:
	case 15:
		return buildNodeInfo_struct(tm[0], tm[1], tm[2], t0[3], t1[0], t1[1], t1[2], t1[3],
		vec4_d(x_mid, y_mid, z_mid, t_min), vec4_d(x_max, y_max, z_max, t_max), node, maxAmountOfChildren);
	}
	return {};
}

TraversalInfo_About_Node4D Tree4DTraverserDifferentSides::buildNodeInfo_2(int nextChildNumber, vec4_d& t0, vec4_d& t1, vec4_d& tm, vec4_d min, vec4_d max, const Node4D* node)
{
	double x_min = min[0];
	double y_min = min[1];
	double z_min = min[2];
	double t_min = min[3];

	//		double x_mid = (max[0] + min[0]) / 2;
	//		double y_mid = (max[1] + min[1]) / 2;
	//		double z_mid = (max[2] + min[2]) / 2;
	
	double x_max = max[0];
	double y_max = max[1];
	double z_max = max[2];
	double t_max = max[3];


	if (std::isinf(t_min) || std::isinf(t_max))
	{
		cout << "Er wordt een ongeldige operatie uitgevoerd bij het bouwen van een 2-node" << endl;
		std::cout << "Press ENTER to continue...";
		cin.get();
	}
	double t_mid = (max[3] + min[3]) / 2.0;

	AmountOfChildren maxAmountOfChildren = getMaxAmountOfChildren(node, longestDimension);

	switch (nextChildNumber)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		return buildNodeInfo_struct(
			t0[0], t0[1], t0[2], t0[3], t1[0], t1[1], t1[2], tm[3],
			vec4_d(x_min, y_min, z_min, t_min),
			vec4_d(x_max, y_max, z_max, t_mid),
			node, maxAmountOfChildren);
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		return buildNodeInfo_struct(
			t0[0], t0[1], t0[2], tm[3], t1[0], t1[1], t1[2], t1[3],
			vec4_d(x_min, y_min, z_min, t_mid),
			vec4_d(x_max, y_max, z_max, t_max), 
			node, maxAmountOfChildren);
	}
	return{};
}

TraversalInfo_About_Node4D Tree4DTraverserDifferentSides::buildNodeInfo_general(int nextChildNumber, vec4_d& t0, vec4_d& t1, vec4_d& tm, vec4_d min, vec4_d max, const Node4D* node, AmountOfChildren maxAmountOfChildrenOfParent)
{
	switch(maxAmountOfChildrenOfParent)
	{
	case TWO:
		return buildNodeInfo_2(nextChildNumber, t0, t1, tm, min, max, node);
	case EIGHT:
		return buildNodeInfo_8(nextChildNumber, t0, t1, tm, min, max, node);
	case SIXTEEN:
		return buildNodeInfo_16(nextChildNumber, t0, t1, tm, min, max, node);
	}
	return {};
}

TraversalInfo_About_Node4D Tree4DTraverserDifferentSides::buildNodeInfo_struct(
	double tx0, double ty0, double tz0, double tt0,
	double tx1, double ty1, double tz1, double tt1,
	vec4_d min, vec4_d max,
	const Node4D* node, AmountOfChildren maxAmountOfChildren)
{
	TraversalInfo_About_Node4D info;
	info.node = node;
	info.t0 = vec4_d(tx0, ty0, tz0, tt0);
	info.t1 = vec4_d(tx1, ty1, tz1, tt1);
	//into.tm =;
	info.nextChildToCheck = -1;
	info.min = min;
	info.max = max;
	info.maxAmountOfChildren = maxAmountOfChildren;
	//info.isBinary = isBinary;
	return info;
}


int Tree4DTraverserDifferentSides::firstChildNodeToCheck(double tx0, double ty0, double tz0, double tt0,
	double txm, double tym, double tzm, double ttm)
{
	/*
	Herinner:
		
		1D -> 1 possible entry point (1 possible entry child node)
		2D -> 2 possible entry lines (3 possible entry child nodes)
		3D -> 3 possible entry planes (7 possible entry child nodes)
		4D -> 4 possible entry hyperplanes (15 possible entry child nodes)
	*/
	switch(stack_TraversalInfo_about_Node4Ds.back().maxAmountOfChildren)
	{
	case TWO: return 0;
	case EIGHT:    return firstChildNodeToCheck_8(tx0, ty0, tz0, tt0, txm, tym, tzm, ttm);
	case SIXTEEN: return firstChildNodeToCheck_16(tx0, ty0, tz0, tt0, txm, tym, tzm, ttm);
	
	default: return firstChildNodeToCheck_16(tx0, ty0, tz0, tt0, txm, tym, tzm, ttm);
	}
}


int Tree4DTraverserDifferentSides::firstChildNodeToCheck_16(
	double tx0, double ty0, double tz0, double tt0,
	double txm, double tym, double tzm, double ttm)
{
	unsigned char answer = 0;	// initialize to 00000000
								/*
								cout << "deciding first node:" << endl;
								cout << "tx0: " << tx0 << ", ty0: " << ty0 << ", tz0: " << tz0 << ", tt0: " << tt0 << endl;
								cout << "txm: " << txm << ", tym: " << tym << ", tzm: " << tzm << ", ttm: " << ttm << endl;
								*/
								//calculate the entry volume of the current voxel
								// => max(tx0, ty0, tz0, tt0)

								// select the entry plane and set bits
	if (tx0 > ty0) {
		if (tx0 > tz0) {
			if (tx0 > tt0) {
				// tx0 is maximum
				// VOLUME YZT
				// -> VOXELS 0, 1, 2, 3, 8, 9, 10, 11
				if (tym < tx0) answer |= 2;	// set bit at position 1
											// answer = answer OR 0000 0010

				if (tzm < tx0) answer |= 1;	// set bit at position 0
											// answer = answer OR 000 0001

				if (ttm < tx0) answer |= 8;
				// answer = answer OR 0000 1000
#ifdef showDebug
				cout << "tx0 is max" << endl;
				cout << "first node is " << to_string((int)answer) << endl << endl;
#endif showDebug
				return (int)answer;
			}
		}
	}
	// ty0 > tx0
	if (ty0 > tz0) {
		if (ty0 > tt0) {
			// ty0 is maximum
			// VOLUME XZT -> VOXELS  0, 1, 4, 5, 8, 9, 12, 13
			if (txm < ty0) answer |= 4;	// set bit at position 2
										// answer = answer OR 0000 0100

			if (tzm < ty0) answer |= 1;	// set bit at position 0
										// answer = answer OR 0000 0001

			if (ttm < ty0) answer |= 8;
			// answer = answer OR 0000 1000
#ifdef showDebug
			cout << "ty0 is max" << endl;
			cout << "first node is " << to_string((int)answer) << endl << endl;
#endif
			return (int)answer;
		}
	}
	//tz0 > ty0 > tx0
	if (tz0 > tt0) {
		// tz0 is maximum
		// VOLUME XYT -> VOXELS 0, 2, 4, 6, 8, 10, 12, 14
		if (txm < tz0) answer |= 4;	// set bit at position 2
									// answer = answer OR 0000 0100

		if (tym < tz0) answer |= 2;	// set bit at position 1
									// answer = answer OR 0000 0010

		if (ttm < tz0) answer |= 8;
		//answer = answer OR 0000 1000
#ifdef showDebug
		cout << "tz0 is max" << endl;
		cout << "first node is " << to_string((int)answer) << endl << endl;
#endif	
		return (int)answer;
	}


#ifdef showDebug
	cout << "tt0 is max" << endl;
	cout << "first node is " << to_string((int)answer) << endl << endl;
#endif
	// tt0 is maximum
	//VOLUME XYZ -> VOXELS 0, 1, 2, 3, 4, 5, 6, 7
	if (txm < tt0) answer |= 4;	// set bit at position 2
								// answer = answer OR 0000 0100
	if (tym < tt0) answer |= 2;	// set bit at position 1
								// answer = answer OR 0000 0010
	if (tzm < tt0) answer |= 1;

	return (int)answer;
}

int Tree4DTraverserDifferentSides::firstChildNodeToCheck_8(double tx0, double ty0, double tz0, double tt0, double txm, double tym, double tzm, double ttm)
{
	unsigned char answer = 0;	// initialize to 00000000

	//calculate the entry face of the current voxel
	// => max(tx0, ty0, tz0)

	// select the entry plane and set bits
	if (tx0 > ty0) {
		if (tx0 > tz0) {
			// tx0 is maximum
			// PLANE YZ -> VOXELS 0, 1, 2, 3 (in 3D) -> VOXELS 0, 2, 4, 6 (in 4D)
			if (tym < tx0) answer |= 2;	// set bit at position 1
										// answer = answer OR 0000 0010
			if (tzm < tx0) answer |= 1;	// set bit at position 0
										// answer = answer OR 000 0001
			//return static_cast<int>(answer << 1); // times 2 (=2^1)
			return answer;
		}
	}

	// ty0 > tx0
	if (ty0 > tz0) {
		// ty0 is maximum
		// PLANE XZ -> VOXELS  0, 1, 4, 5 (in 3D) -> VOXELS 0, 2, 8, 10 (in 4D)
		if (txm < ty0) answer |= 4;	// set bit at position 2
									// answer = answer OR 0000 1000
		if (tzm < ty0) answer |= 1;	// set bit at position 0
									// answer = answer OR 0000 0001
		//return static_cast<int>(answer << 1); // times 2 (=2^1)
		return answer;
	}


	//tz0 is maximum
	 // PLANE XY -> VOXELS 0, 2, 4, 6 (in 3D) -> VOXELS 0, 4, 8, 12 (in 4D)
	if (txm < tz0) answer |= 4;	// set bit at position 2
								// answer = answer OR 0000 0100
	if (tym < tz0) answer |= 2;	// set bit at position 1
								// answer = answer OR 0000 0010

	//return static_cast<int>(answer << 1); // times 2 (=2^1)
	return answer;
}

void Tree4DTraverserDifferentSides::correctRayForNegativeDirectionComponents()
{
	if (ray.direction[0] < 0.0f) {
		/*
		IF the ray direction is negative in the X coordinate
		THEN reflect the ray with respect to the middle plane of the 4D-tree
		
		*/

//		ray.origin[0] = tree4D->size[0] - ray.origin[0];
		ray.origin[0] = abs(tree4D->min[0] - tree4D->max[0]) - ray.origin[0];
		ray.direction[0] = -ray.direction[0];
		a |= 4; //bitwise OR (latest bits are XYZ)
				// a = a OR 0000 0100
	}
	if (ray.direction[1] < 0.0f) {
//		ray.origin[1] = tree4D->size[1] - ray.origin[1];
		ray.origin[1] = abs(tree4D->min[1] - tree4D->max[1]) - ray.origin[1];
		ray.direction[1] = -ray.direction[1];
		a |= 2;
		// a = a OR 0000 0010
	}
	if (ray.direction[2] > 0.0f) {
//		ray.origin[2] = tree4D->size[2] - ray.origin[2];
		ray.origin[2] = abs(tree4D->min[2] - tree4D->max[2]) - ray.origin[2];
		ray.direction[2] = -ray.direction[2];
		a |= 1;
		// a = a OR 0000 0001
	}
	if (ray.direction[3] < 0.0f){
//		ray.origin[3] = tree4D->size[3] - ray.origin[3];
		ray.origin[3] = abs(tree4D->min[3] - tree4D->max[3]) - ray.origin[3];
		ray.direction[3] = -ray.direction[3];
		a |= 8;
		// a = a OR 0000 1000
	}
}

void Tree4DTraverserDifferentSides::safelyCalculateInitialRayParameters(double& tx0, double& tx1, double& ty0, double& ty1, double& tz0, double& tz1, double& tt0, double& tt1)
{
	safelyCalculateRayParametersForDirection(0, tx0, tx1);
	safelyCalculateRayParametersForDirection(1, ty0, ty1);
	safelyCalculateRayParametersForDirection(2, tz0, tz1);
	safelyCalculateRayParametersForDirection(3, tt0, tt1);

	/*	double tx0 = (tree4D->min[0] - ray.origin[0]) * (1.0f / ray.direction[0]);
	double tx1 = (tree4D->max[0] - ray.origin[0]) * (1.0f / ray.direction[0]);
	double ty0 = (tree4D->min[1] - ray.origin[1]) * (1.0f / ray.direction[1]);
	double ty1 = (tree4D->max[1] - ray.origin[1]) * (1.0f / ray.direction[1]);
	double tz0 = (tree4D->min[2] - ray.origin[2]) * (1.0f / ray.direction[2]);
	double tz1 = (tree4D->max[2] - ray.origin[2]) * (1.0f / ray.direction[2]);
	double tt0 = (tree4D->min[3] - ray.origin[3]) * (1.0f / ray.direction[3]);
	double tt1 = (tree4D->max[3] - ray.origin[3]) * (1.0f / ray.direction[3]);*/
}

// perform PUSH, POP or ADVANCE
void Tree4DTraverserDifferentSides::step() {
	stepcount++;
	// if the stack is empty, we're done
	if (stack_TraversalInfo_about_Node4Ds.empty())
	{
		return;
	}

	// define some aliases to make code readable
	vec4_d& t0 = stack_TraversalInfo_about_Node4Ds.back().t0;
	vec4_d& t1 = stack_TraversalInfo_about_Node4Ds.back().t1;
	vec4_d& tm = stack_TraversalInfo_about_Node4Ds.back().tm;

	//POP
	// if we're in a terminal node or if we visited all children of that node (next child = 16), 
	// or if the t1 values have become negative, pop the current node from the stack
	if (stack_TraversalInfo_about_Node4Ds.back().nextChildToCheck == 16 || stack_TraversalInfo_about_Node4Ds.back().node->isLeaf()) {

#ifdef showDebug
		cout << "POP" << endl;
		if (stack_TraversalInfo_about_Node4Ds.back().nextChildToCheck == 16)
		{
			cout << "reason: nextchild == 16" << endl;
		}
		if (stack_TraversalInfo_about_Node4Ds.back().node->isLeaf())
		{
			cout << "reason: node is Leaf" << endl;
		}
		cout << endl;
#endif		
		stack_TraversalInfo_about_Node4Ds.pop_back();
		return;
	}

	// PUSH
	// we haven't looked at any child in this voxel yet: pick the first and push down
	if (stack_TraversalInfo_about_Node4Ds.back().nextChildToCheck == -1) {
		// calculate midpoint and save it in stack
#ifdef showDebug
		cout << "PUSH" << endl;
#endif

		//tm = 0.5f*(t0 + t1);
		tm = calculateMidpoint(t0, t1);
		// calculate first node
		stack_TraversalInfo_about_Node4Ds.back().nextChildToCheck
			= firstChildNodeToCheck(
				t0[0], t0[1], t0[2], t0[3],
				tm[0], tm[1], tm[2], tm[3]);
	}


	// ADVANCE
	// let's look at the next child in this voxel
	int nextChildNumber = getCurrentNodeInfo().nextChildToCheck;
	//number of the next child we will look into
#ifdef showDebug
	cout << "ADVANCE" << endl;
	cout << "next child: " << nextChildNumber << endl << endl;
#endif
	//assert(nextChildNumber < 7);
#ifdef showDebug
	if (nextChildNumber >8 && nextChildNumber != 16)
	{
		cout << nextChildNumber << endl;
	}
#endif

	/*
	set the next child to check of the current node
	to the childnode we need to check after we have checked the current child node to check
	*/
	stack_TraversalInfo_about_Node4Ds.back().nextChildToCheck = nextChildNodeToCheck(nextChildNumber, t0, t1, tm);
	if (getCurrentNode()->hasChild(nextChildNumber ^ a)) {

		const Node4D* nextChildNode
			= tree4D->getNode(
				getCurrentNode()->getChildPos(nextChildNumber ^ a));

		AmountOfChildren maxAmountOfChildrenOfCurrentNode = getMaxAmountOfChildren(getCurrentNode(), longestDimension);
		
		TraversalInfo_About_Node4D info_about_nextChildNode
			= buildNodeInfo_general(nextChildNumber, t0, t1, tm, getCurrentNodeInfo().min, getCurrentNodeInfo().max, nextChildNode, maxAmountOfChildrenOfCurrentNode);
		stack_TraversalInfo_about_Node4Ds.push_back(info_about_nextChildNode);
	}
}


void Tree4DTraverserDifferentSides::inititializeBeforeTraversal() {
	stepcount = 0;
	a = 0;

	original_ray = ray;

	if (tree4D->gridsize_T > tree4D->gridsize_S)// T > S
	{
		longestDimension = TIME;
	}else// T <= S
	{
		longestDimension = SPACE;
	}


	// fixes for rays with negative direction
	correctRayForNegativeDirectionComponents();
	
	//This line should be all, what you need to add to your code.
	static_assert(std::numeric_limits<double>::is_iec559, "IEEE 754 required");
	
	//Safe calculation of the ray parameters (check division by zero, use of inifinty)
	double tx0, tx1, ty0, ty1, tz0, tz1, tt0, tt1;
	safelyCalculateInitialRayParameters(tx0, tx1, ty0, ty1, tz0, tz1, tt0, tt1);
	
	// tc_min = max(max(tx0, ty0), tz0)
	// tc_max = min(min(tx1, ty1), tz1)
	//bool condition3D = max(max(tx0, ty0), tz0) < min(min(tx1, ty1), tz1);
	bool condition4D = max(max(max(tx0, ty0), tz0), tt0) < min(min(min(tx1, ty1), tz1), tt1);
	if (condition4D) {
		hasBeenHitByRay = true;

		// push root node on stack
		const Node4D* root = tree4D->getRootNode();

		AmountOfChildren maxAmountOfChildren = getMaxAmountOfChildren(root, longestDimension);

		TraversalInfo_About_Node4D info_about_root 
			= buildNodeInfo_struct(tx0, ty0, tz0, tt0, tx1, ty1, tz1, tt1, tree4D->min, tree4D->max, root, maxAmountOfChildren);
		stack_TraversalInfo_about_Node4Ds.push_back(info_about_root);
	}
	// ELSE push nothing on the stack
}

void Tree4DTraverserDifferentSides::safelyCalculateRayParametersForDirection(int coord, double& t0, double& t1)
{
	double denominator = ray.direction[coord];
	double numerator_0 = tree4D->min[coord] - ray.origin[coord];
	double numerator_1 = tree4D->max[coord] - ray.origin[coord];

	if (denominator == 0.0f) {
		//OPGEPAST

		//numerator_0;
		if (numerator_0 > 0)
		{
			t0 = std::numeric_limits<double>::infinity();
		}
		else
		{
			if (numerator_0 < 0)
			{
				t0 = -1 * std::numeric_limits<double>::infinity();
			}
			else // numerator_0 == 0.0f
				 // tree4D->min[coord] = ray.origin[coord];
			{
				t0 = -1 * std::numeric_limits<double>::infinity();
				/*			if(numerator_1 > 0)
				{
				t0 = -1 * std::numeric_limits<double>::infinity();
				}else
				{
				t0 = std::numeric_limits<double>::infinity();
				}*/
			}
		}

		// numerator_1
		if (numerator_1 > 0)
		{
			t1 = std::numeric_limits<double>::infinity();
		}
		else
		{
			if (numerator_1 < 0)
			{
				t1 = -1 * std::numeric_limits<double>::infinity();
			}
			else // numerator_0 == 0.0f
				 // tree4D->min[coord] = ray.origin[coord];
			{
				t1 = -1 * std::numeric_limits<double>::infinity();
				/*				if(numerator_0 < 0)
				{
				t1 = std::numeric_limits<double>::infinity();
				}else
				{

				}*/
			}
		}
	}
	else // denominator != 0.0f
	{
		t0 = numerator_0 / denominator;
		t1 = numerator_1 / denominator;
	}
}

//double calculateMidpoint(double& t0, double& t1)
//{
//	double tm;
//	if (std::isinf(t0) && std::isinf(t1)
//		&& t0< 0 && t1> 0)
//	{
//
//		double mid_coord = (stack_TraversalInfo_about_Node4Ds.back().min[coord] + stack_TraversalInfo_about_Node4Ds.back().max[coord]) / 2.0;
//		if (ray.origin[coord] < mid_coord)
//		{
//			tm= std::numeric_limits<double>::infinity();
//		}
//		else
//		{
//			tm = -1 * std::numeric_limits<double>::infinity();
//		}
//	}
//	else
//	{
//		tm = 0.5f*(t0+ t1[coord]);
//	}
//
//}


vec4_d Tree4DTraverserDifferentSides::calculateMidpoint(vec4_d& t0, vec4_d& t1)
{
	vec4_d tm;

	for (int coord = 0; coord < 4; coord++) {
		//Check for each of the axis
		if (std::isinf(t0[coord]) && std::isinf(t1[coord])
			&& t0[coord] < 0 && t1[coord] > 0)
		{

			double mid_coord = (stack_TraversalInfo_about_Node4Ds.back().min[coord] + stack_TraversalInfo_about_Node4Ds.back().max[coord]) / 2.0;
			if (ray.origin[coord] < mid_coord)
			{
				tm[coord] = std::numeric_limits<double>::infinity();
			}
			else
			{
				tm[coord] = -1.0 * std::numeric_limits<double>::infinity();
			}
		}
		else
		{
			tm[coord] = 0.5 *(t0[coord] + t1[coord]);
		}
	}
#ifdef showDebug
	cout << "f: calculateMidpoint" << endl;
	cout << "   t0: " << t0 << endl;
	cout << "   t1: " << t1 << endl;
	cout << "   tm: " << tm << endl;
#endif
	return tm;
}

Tree4DTraverserDifferentSides::~Tree4DTraverserDifferentSides(void)
{
}

//AmountOfChildren Tree4DTraverserDifferentSides::getMaxAmountOfChildren(const Node4D *node) const
//{
//
//	AmountOfChildren maxAmountOfChildren = SIXTEEN;
//	switch(longestDimension)
//	{
//	case SPACE:
//		if(node->isOctaryNode())
//		{
//			maxAmountOfChildren = EIGHT;
//			return maxAmountOfChildren;
//		}
//	case TIME:
//		if(node->isBinaryNode())
//		{
//			maxAmountOfChildren = TWO;
//			return maxAmountOfChildren;
//		}
//	}
//	return maxAmountOfChildren;i
//}
//
//AmountOfChildren Tree4DTraverserDifferentSides::getMaxAmountOfChildren(const Node4D *node,  const LongestDimension &longest_dimention)
//{
//
//	AmountOfChildren maxAmountOfChildren = SIXTEEN;
//	switch (longest_dimention)
//	{
//	case SPACE:
//		if (node->isOctaryNode())
//		{
//			maxAmountOfChildren = EIGHT;
//			return maxAmountOfChildren;
//		}
//	case TIME:
//		if (node->isBinaryNode())
//		{
//			maxAmountOfChildren = TWO;
//			return maxAmountOfChildren;
//		}
//	}
//	return maxAmountOfChildren;
//}