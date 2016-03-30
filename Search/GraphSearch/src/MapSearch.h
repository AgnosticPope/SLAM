/******************************************************************************
Author		: Lichao Ma
Date  		: Mar 29,2016
version		: v0.1
Description :
	Map searching algorithms.
*****************************************************************************/

#ifndef MAPSEARCH_H_
#define MAPSEARCH_H_
#include <vector>

#include "Point.h"
//#include "BFS.h"

namespace SearchAlgorithms{

using namespace std;

typedef Point<unsigned int> Point_unit;

/*
 * About the map:
 *  0 means the obstacles,positive values means the cost each grid.Although
 *  in Search these values are used but to make a comparison between different
 *  algorithms,such as A*,Dijkstra shortest path,we need a map that works
 *  for all these algorithms.
 *
 *  Notice about the map coordinate:
 *  map[x][y]:
 *  0-------> y
 *  |
 *  |
 *  v
 *  x
 */
class MapSearch{
public:
	static const unsigned int Obstacle;	//positive value means the cost of each path
	static const char ObstacleSymbol;
	static const unsigned int CostMax;//Don't use UINT_MAX,watch out for OVERFLOW
	MapSearch():Start(0,0),Target(0,0),EffortCount(0){};
	virtual ~MapSearch(){};

	void setStart(const Point_unit &s){Start.x=s.x; Start.y=s.y;Start.dir=s.dir;}
	void setTarget(const Point_unit &t){Target.x=t.x; Target.y=t.y;Target.dir=t.dir;}

	int  getMinDistance(){return Route.size()-1;}
	void printRoute();
	void getRoute(vector<Point_unit > &route);
	void printRouteOnMap(const vector<vector<unsigned int> > &map);
	void printGradientOnMap(const vector<vector<unsigned int> > &map);

	virtual bool search( const vector<vector<unsigned int> > &map)  { return false;}
	virtual bool search( const vector<vector<unsigned int> > &map,
						const Point_unit &start,
						const Point_unit &target) 			{ return false;}
protected:
	Point_unit Start;
	Point_unit Target;
	unsigned int EffortCount;

	vector<Point_unit > Route;
	vector<vector<bool> > Checked;
	vector<vector<Point_unit > > Gradient;
	vector<vector<unsigned int> > CostMap;

	void generateRoute();
	void generateRoute(const vector<vector<unsigned int> > &map);
	void generateRoute(const vector<vector<vector<Point_unit > > > &Gradient);
	unsigned int abs(Point_unit &a, Point_unit &b);
	bool isLegal(const vector<vector<unsigned int> > &map,
				 const Point_unit &p);
	bool isLegal(const vector<vector<unsigned int> > &map,
				 const unsigned int* const moveCost,
				 const Point_unit &p);
	unsigned int minCost(const vector<vector<unsigned int> > &map,
						const Point_unit &p,
						Point_unit &move);

	unsigned int minCost(const vector<vector<unsigned int> > &map,
						 const unsigned int* const moveCost,
						 const Point_unit &point,
						 Point_unit &move);

	//const unsigned int NoneDirection = 4;
	static const int Move[5][2];
	static const char DirSymbol[5];

};

}

#endif /* MAPSEARCH_H_ */
