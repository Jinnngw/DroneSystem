#ifndef OBSERVER_H_
#define OBSERVER_H_

#include <string>

class IObserver{
    public:
        // Notify function is called by the publisher to notify SimulationModel, the concrete observer
        virtual bool sendNotif(std::string msg) = 0;
};

#endif