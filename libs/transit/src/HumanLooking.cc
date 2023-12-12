#include "HumanLooking.h"
#include "HumanAvailable.h"
#include "AstarStrategy.h"

HumanLooking::HumanLooking(Human* human){
  this->human = human;
}

void HumanLooking::update(double dt) {

  //if human has get to the package's destination
  if (human->getMovement() && !human->getMovement()->isCompleted()) {
    human->getMovement()->move(human, dt);
  } else {
    // Delete any previously-existing route
    if (human->getMovement()) human->deleteMovement();

    // Notify cars
    this->human->notifySubscribers(this->human->getPackage()->getPosition());

    // Delete package from package singleton
    PackageDataController::getInstance()->removePackage(this->human->getPackage());

    // Resetting package assigned to human instance
    this->human->setPackage(nullptr);
    
    // Define new destination
    Vector3 dest;
    dest.x = ((static_cast<double>(rand())) / RAND_MAX) * (2900) - 1400;
    dest.y = human->getPosition().y;
    dest.z = ((static_cast<double>(rand())) / RAND_MAX) * (1600) - 800;

    // If human has a simulation model (it should),
    if (human->getModel()){
      // Set the movement of the human to a route with the randomized destination
      human->setMovement(new AstarStrategy(human->getPosition(), dest,
                                          human->getModel()->getGraph()));
    }

    human->changeState(new HumanAvailable(this->human));
    std::cout << "Human has been set from Looking to Available" << std::endl;
  }
}

