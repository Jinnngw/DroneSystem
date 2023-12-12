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
    // Get the package from the singleton
    package = PackageDataController::getInstance()->getPackageList()[0];

    std::cout << package << std::endl;

    // If a package was grabbed from the stack,
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
  this->cars.push_back(observer);
}

void Human::unsubscribe(ICarSubscriber* observer){
  for (int i=0;i<this->cars.size();i++){
    if (cars[i] = observer){
      this->cars.erase(cars.begin() + i);
      break;
    }
  }
}