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
  bool statusSwitch = false;

  if (available) {
    getNextDelivery();
    if (!available) {
      notifySubscribers("StartedDelivery");
      statusSwitch = true;
    }
  }

  if (toPackage) {
    toPackage->move(this, dt);
    if (toPackage->isCompleted()) {
      delete toPackage;
      toPackage = nullptr;
      pickedUp = true;
      notifySubscribers("PackagePickedUp");
      statusSwitch = true;
    }
  } else if (toFinalDestination) {
    toFinalDestination->move(this, dt);
    if (toFinalDestination->isCompleted()) {
      delete toFinalDestination;
      toFinalDestination = nullptr;
      if (package && pickedUp) {
        package->setPosition(position);
        package->setDirection(direction);
        package->handOff();
      }
      package = nullptr;
      available = true;
      pickedUp = false;
      notifySubscribers("DeliveryCompleted");
      statusSwitch = true;
    }
  }

  if (!statusSwitch) {
    notifySubscribers("StatusUpdate");
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
