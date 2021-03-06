#ifndef GRIDPOINT_H_
#define GRIDPOINT_H_

#include "util.h"

using namespace trimesh;

class GridPoint {
public:
	float opacity;
	vec3_d color;

	GridPoint();
	GridPoint(float opacity, vec3_d color);
	bool isEmpty() const;
};

inline GridPoint::GridPoint() : opacity(0.0f), color(vec3_d(0, 0, 0)) {
}

inline GridPoint::GridPoint(float opacity, vec3_d color) : opacity(opacity), color(color) {
}

inline bool GridPoint::isEmpty() const
{
	return (opacity == 0.0f);
}

#endif /* DATAPOINT_H_ */
