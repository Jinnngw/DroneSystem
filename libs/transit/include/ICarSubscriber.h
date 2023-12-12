#ifndef ICAR_SUBSCRIBER_H_
#define ICAR_SUBSCRIBER_H_
#include "math/vector3.h"
#include "Package.h"

class ICarSubscriber {
public:
    virtual void notify(Vector3 location,Package* package) = 0;
};

#endif