#define _USE_MATH_DEFINES
#include "Drone.h"

#include <cmath>
#include <limits>
#include <iostream> 

#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "DfsStrategy.h"
#include "BfsStrategy.h"
#include "DijkstraStrategy.h"
#include "JumpDecorator.h"
#include "SpinDecorator.h"

#include "Package.h"
#include "SimulationModel.h"

Drone::Drone(JsonObject& obj) : IEntity(obj) {
  available = true;
}

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
        toFinalDestination =
          new JumpDecorator(
            new AstarStrategy(
              packagePosition,
              finalDestination,
              model->getGraph()));
      } else if (strat == "dfs") {
        toFinalDestination =
          new SpinDecorator(
            new JumpDecorator(
              new DfsStrategy(
                packagePosition,
                finalDestination,
                model->getGraph())));
      } else if (strat == "bfs") {
        toFinalDestination =
          new SpinDecorator(
            new SpinDecorator(
              new BfsStrategy(
                packagePosition,
                finalDestination,
                model->getGraph())));
      } else if (strat == "dijkstra") {
        toFinalDestination =
          new JumpDecorator(
            new SpinDecorator(
              new DijkstraStrategy(
                packagePosition,
                finalDestination,
                model->getGraph())));
      } else {
        toFinalDestination = new BeelineStrategy(
          packagePosition,
          finalDestination);
      }
    }
  }
}

void Drone::Update(double dt) {
  bool statusSwitch = false;

  if (available) {
    GetNextDelivery();
    if (!available) {
      NotifySubscribers("StartedDelivery");
      statusSwitch = true;
    }
  }

  if (toPackage) {
    toPackage->Move(this, dt);
    if (toPackage->IsCompleted()) {
      delete toPackage;
      toPackage = nullptr;
      pickedUp = true;
      NotifySubscribers("PackagePickedUp");
      statusSwitch = true;
    }
  } else if (toFinalDestination) {
    toFinalDestination->Move(this, dt);
    if (toFinalDestination->IsCompleted()) {
      delete toFinalDestination;
      toFinalDestination = nullptr;
      if (package && pickedUp) {
        package->SetPosition(position);
        package->SetDirection(direction);
        package->HandOff();
      }
      package = nullptr;
      available = true;
      pickedUp = false;
      NotifySubscribers("DeliveryCompleted");
      statusSwitch = true;
    }
  }

  if (!statusSwitch) {
    NotifySubscribers("StatusUpdate");
  }
}


void Drone::subscribe(IObserver* observer) {
  observers.push_back(observer);
}

void Drone::unsubscribe(IObserver* observer) {
  observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
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