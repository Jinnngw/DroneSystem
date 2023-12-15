#ifndef ICAR_SUBSCRIBER_H_
#define ICAR_SUBSCRIBER_H_
#include "math/vector3.h"
#include "Package.h"

class ICarSubscriber {
public:
   /**
   * @brief Notifies the subscriber about a package's location.
   * @param location The location of the package (type: Vector3).
   * @param package Pointer to the package.
   */
    virtual void notify(Vector3 location,Package* package) = 0;
};

#endif