#ifndef TYPEDEF_H
#define TYPEDEF_H

namespace NS_OCH {

typedef unsigned int UINT;
typedef double LINK_COST;
//LA:commented changed from uint to double--undo messedup so many things
typedef UINT LINK_CAPACITY;
//typedef double LINK_CAPACITY;
typedef double SimulationTime;

typedef enum {
	UP = 0,
	DOWN
} UpDownStatus;


};

#endif
