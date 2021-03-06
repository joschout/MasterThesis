#include "WorkOctreeRenderer.h"
#include "../TreeTraverser.h"

using namespace std;

WorkOctreeRenderer::WorkOctreeRenderer(void) : OctreeRenderer("work")
{
}

void WorkOctreeRenderer::Render(const RenderContext& rc, const Octree const* tree, unsigned char* texture_array) const{

	// Get the number of processors in this system
	int iCPU = omp_get_num_procs();
	omp_set_num_threads(iCPU);
	// declare variables we use in loop
	int x, index, partindex;
	TreeTraverser t;
	DataPoint v;
	double size = tree->gridlength;

#pragma omp parallel for private(x,t,v,index)
	for(int y = 0; y < rc.n_y; y++){
		partindex = y*(rc.n_y*4);
		for(x = 0; x < rc.n_x; x++) {
			index = partindex + x*4; // index in char array computation (part 2)
			t = TreeTraverser(tree,rc.getRayForPixel(x,y));
			while((!t.isTerminated())){
				if(t.getCurrentNode()->isLeaf()){
					if(t.getCurrentNode()->hasData()){
						break;
					}
				}
				t.step();
			}
			texture_array[index] = (unsigned char) int((float(t.stepcount)/(log2(size)))*255.0);
			texture_array[index+3] = (unsigned char) 1;
		}
	}
}

WorkOctreeRenderer::~WorkOctreeRenderer(void)
{
}
