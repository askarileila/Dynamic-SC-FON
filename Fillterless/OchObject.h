#ifndef OCHOBJECT_H
#define OCHOBJECT_H

//LA: to stop priting extra stuff
//#define DEBUGB
//#define DEBUGBB
//#define DEBUGLA //LA:to debugging DVNF related funcs


namespace NS_OCH {

#include <iostream>

class OchObject {
public:
	OchObject();
	virtual ~OchObject();

	// for debugging
	virtual const char* toString() const;
	virtual void dump(ostream& out) const;
};

};	// namespace
#endif
