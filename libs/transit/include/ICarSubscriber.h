#ifndef ICAR_SUBSCRIBIBER_H_
#define ICAR_SUBSCRIBIBER_H_
#include "math/vector3.h"


class ICarSubscriber {
public:
    void notify(Vector3 location);
};

#endif