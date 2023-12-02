#ifndef OBSERVER_H_
#define OBSERVER_H_

#include <string>

class IObserver{
    public:
        // Notify function is called by the publisher to notify SimulationModel, the concrete observer
        virtual void sendNotif(IEntity* context) = 0;
};

#endif