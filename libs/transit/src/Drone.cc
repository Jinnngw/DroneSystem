#define _USE_MATH_DEFINES
#include "Drone.h"

#include <cmath>
#include <iostream>
#include <limits>

#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "BfsStrategy.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include "JumpDecorator.h"
#include "Package.h"
#include "SimulationModel.h"
#include "SpinDecorator.h"

Drone::Drone(JsonObject& obj) : IEntity(obj) { available = true; }

Drone::~Drone() {
  if (toPackage) delete toPackage;
  if (toFinalDestination) delete toFinalDestination;
}

void Drone::getNextDelivery() {
  if (model && model->scheduledDeliveries.size() > 0) {
    package = model->scheduledDeliveries.front();
    model->scheduledDeliveries.pop_front();

    if (package) {
      available = false;
      pickedUp = false;

      Vector3 packagePosition = package->getPosition();
      Vector3 finalDestination = package->getDestination();

      toPackage = new BeelineStrategy(position, packagePosition);

      std::string strat = package->getStrategyName();
      if (strat == "astar") {
        toFinalDestination = new JumpDecorator(new AstarStrategy(
            packagePosition, finalDestination, model->getGraph()));
      } else if (strat == "dfs") {
        toFinalDestination =
            new SpinDecorator(new JumpDecorator(new DfsStrategy(
                packagePosition, finalDestination, model->getGraph())));
      } else if (strat == "bfs") {
        toFinalDestination =
            new SpinDecorator(new SpinDecorator(new BfsStrategy(
                packagePosition, finalDestination, model->getGraph())));
      } else if (strat == "dijkstra") {
        toFinalDestination =
            new JumpDecorator(new SpinDecorator(new DijkstraStrategy(
                packagePosition, finalDestination, model->getGraph())));
      } else {
        toFinalDestination =
            new BeelineStrategy(packagePosition, finalDestination);
      }
    }
  }
}

void Drone::update(double dt) {

  if (available) {
    getNextDelivery();
    if (!available) {
      // Assign the package's name as the dest value in details of Drone
      this->setDetails("dest", this->package->getName());
      
      //Notify SimulationModel
      notifySubscribers("StartedDelivery");
      
    }
  }

  if (toPackage) {
    toPackage->move(this, dt);
    if (toPackage->isCompleted()) {
      delete toPackage;
      toPackage = nullptr;
      pickedUp = true;

      // Package has been picked up, notify SimulationModel (the observer)
      this->setDetails("dest", this->package->getName());
      notifySubscribers("PackagePickedUp");

    }
  } else if (toFinalDestination) {
    toFinalDestination->move(this, dt);
    
    if (package && pickedUp) {
        package->setPosition(position);
        package->setDirection(direction);
      }
    
    if (toFinalDestination->isCompleted()) {
      // Saving package name before it is released
      std::string destination = this->package->getName();
      
      delete toFinalDestination;
      toFinalDestination = nullptr;
      
      package->handOff();      
      package = nullptr;
      available = true;
      pickedUp = false;

      // Package has been delivered, notify SimulationModel
      this->setDetails("dest", destination);
      notifySubscribers("DeliveryCompleted");
    }
  }
}

void Drone::subscribe(IObserver* observer) { observers.push_back(observer); }

void Drone::unsubscribe(IObserver* observer) {
  observers.erase(std::remove(observers.begin(), observers.end(), observer),
                  observers.end());
}

bool Drone::notifySubscribers(std::string context) {
  if (observers.empty()) {
    std::cout << "No observers found." << std::endl;
    return false;
  }
  for (IObserver* observer : observers) {
    observer->sendNotif(this, context);
  }
  return true;
}
