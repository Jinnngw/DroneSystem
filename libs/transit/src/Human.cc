#define _USE_MATH_DEFINES
#include "Human.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "SimulationModel.h"

#include "IHumanState.h"
#include "HumanLooking.h"
#include "HumanAvailable.h"
#include "Package.h"
#include "JumpDecorator.h"
#include "Car.h"
#include "ICarSubscriber.h"


Human::Human(JsonObject& obj) : IEntity(obj) {
  this->packages = PackageDataController::getInstance();
  // Initialize the default state
  state = new HumanAvailable(this);
}

Human::~Human() {
  delete state;
  if (movement) delete movement;
}

void Human::update(double dt) {
  state->update(dt);
}

void Human::changeState(IHumanState* newState) {
  delete state;
  state = newState;
}

IStrategy* Human::getMovement(){
  return this->movement;
}

void Human::setMovement(IStrategy* movement){
  this->movement = movement;
}

void Human::deleteMovement(){
  delete movement;
}

Package* Human::getPackage() {return package;}

SimulationModel* Human::getModel() {return model;}

std::vector<Package*> Human::getPackages() { return packages->getPackageList(); }

void Human::setPackage(Package* package){ this->package = package;}

std::vector<ICarSubscriber*> Human::getCars() { return cars; }

void Human::getNextDelivery() {

  // std::cout << model->scheduledDeliveries.size() << std::endl;

  if (model && PackageDataController::getInstance()->packageList.size() > 0) {
    // If the list of found packages is nonempty
    if (this->foundPackages.size() > 0){
      // Search through package list in singleton until new package found
      for (Package* singletonPackage : PackageDataController::getInstance()->getPackageList()){
        for (Package* foundPackage : this->foundPackages){
          if (singletonPackage != foundPackage){
            this->package = singletonPackage;
          }
        }
      }
    }
    // Otherwise, all packages are new, pick the first one
    else{
      package = PackageDataController::getInstance()->getPackageList()[0];
    }


    // If a package was grabbed from the package singleton,
    if (package) {
      // get the package's position
      Vector3 packagePosition = package->getPosition();
      std::cout << "Human " << packagePosition.x << std::endl;

      // Set the route for Human to a strategy with package location as destination
      movement =
          new JumpDecorator(
            new AstarStrategy(
              this->getPosition(),
              packagePosition,
              model->getGraph()));
    }
  }
}

void Human::subscribe(ICarSubscriber* observer){
  // Check if car is already subscribed to Human
  for (ICarSubscriber* car : cars){
    Car* temp = dynamic_cast<Car*>(car);
    if (temp->getId() == dynamic_cast<Car*>(observer)->getId()){
      return;
    }
  }

  // By this point car is not yet subscribed to Human, subscribe it
  // std::cout << "Subscribing " << dynamic_cast<Car*>(observer)->getName() << " to " << this->getName() << std::endl;
  this->cars.push_back(observer);
}

void Human::unsubscribe(ICarSubscriber* observer){
  for (int i=0;i<this->cars.size();i++){
    if (cars[i] = observer){
      this->cars.erase(cars.begin() + i);
      // std::cout << "Unsubscribing " << dynamic_cast<Car*>(observer)->getName() << " from " << this->getName() << std::endl;
      break;
    }
  }
}

void Human::notifySubscribers(Vector3 location) {
  // Notify ICarSubscribers about the found location
  for (auto car : cars) {
    car->notify(location, this->getPackage());
  }

  std::cout << this->getName() << " notified " << cars.size() << " cars" << std::endl;
}

// Updates cars subscribed to Human depending on distance from human
void Human::updateSubscribers(){
  // Get map of all entities in model
  std::map<int, IEntity*> entities = model->getEntities();
  float distThreshold = 3000;

  // Unsubscribe all cars that are too far away from human
  for (ICarSubscriber* car : cars){
    if (dynamic_cast<Car*>(car)->getPosition().dist(this->getPosition()) > distThreshold){
      this->unsubscribe(car);
    }
  }

  // Subscribe all new cars that are close enough to human
  for (int i=0;i<entities.size();i++){
    if (entities[i]->getName().at(0) == 'C' && entities[i]->getPosition().dist(this->getPosition()) <= distThreshold){
      this->subscribe(dynamic_cast<Car*>(entities[i]));
    }
  }

}

void Human::addFoundPackage(Package* package){
  this->foundPackages.push_back(package);
}