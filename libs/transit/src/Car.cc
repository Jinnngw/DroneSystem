#include "Car.h"

#include <cmath>
#include <ctime>

#include "DijkstraStrategy.h"
#include "SimulationModel.h"
#include "ICarState.h"
#include "CarAvailable.h"

Car::Car(JsonObject& obj) : IEntity(obj) {
  std::srand(static_cast<unsigned int>(std::time(0)));
  this->state = new CarAvailable(this);
}

Car::~Car() {
  if (toNextDestination) delete toNextDestination;
}

// WARNING: big difference between getToNextDestination and getNextDestination
  // getToNextDestination will just return the current toNextDestination
  // getNextDestination will get a BRAND NEW destination and set the DijkstraStrategy accordingly
IStrategy* Car::getToNextDestination(){
  return this->toNextDestination;
}

void Car::getNextDestination() {
  if (model) {
    // Generate random destination using rand()
    double x = (std::rand() % static_cast<int>(maxX - minX + 1)) + minX;
    double y = (std::rand() % static_cast<int>(maxY - minY + 1)) + minY;
    double z = (std::rand() % static_cast<int>(maxZ - minZ + 1)) + minZ;

    destination = Vector3(x, y, z);

    this->toNextDestination =
        new DijkstraStrategy(position, destination, model->getGraph());
  }
}

void Car::setNextDestination(Vector3 dest){
  toNextDestination = new DijkstraStrategy(position, dest, model->getGraph());
}

void Car::clearNextDestination(){
  toNextDestination = nullptr;
}

void Car::deleteNextDestination(){
  delete this->toNextDestination;
}

Package* Car::getPackage(){
  return this->package;
}

void Car::setPackage(Package* package){
  this->package = package;
}

void Car::update(double dt) {
  // this->state->update(dt);
}

void Car::changeState(ICarState* state) {
  this->state = state;
}

void Car::notify(Vector3 location){
  // NOTIFICATION THINGY STUFF HERE
  std::cout << "STUFF GOES HERE" << std::endl;
}