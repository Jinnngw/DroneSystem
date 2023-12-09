#ifndef ICAR_SUBSCRIBER_H_
#define ICAR_SUBSCRIBER_H_
#include "math/vector3.h"


class ICarSubscriber {
public:
    virtual void notify(Vector3 location) = 0;
};

#endif