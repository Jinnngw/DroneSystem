#include "HumanAvailable.h"
#include "Human.h"
#include "AstarStrategy.h"
#include "JumpDecorator.h"
#include "HumanLooking.h"
#include "Package.h"
#include "SimulationModel.h"

/**
 * @brief Constructor for HumanAvailable. Sets the initial state of the human.
 * @param human Pointer to the Human object being controlled.
 */
HumanAvailable::HumanAvailable(Human* human){
    this->human = human;
}

/**
 * @brief Update function for HumanAvailable. Manages the behavior when the human is available.
 * @param dt Time step for the update.
 */
void HumanAvailable::update(double dt){
  // Get next package (null if no package)
  this->human->getNextDelivery();

  // std::cout << this->human->getPackage() << std::endl;

  // If human has a package to get to
  if (human->getPackage()){
    // Change state to Looking
    this->human->changeState(new HumanLooking(this->human));
    std::cout << "Human has switched from Available to Looking" << std::endl;
  }

  // Otherwise, go to random destination
  else {
    if (human->getMovement() && !human->getMovement()->isCompleted()){
      human->getMovement()->move(human, dt);
      human->updateSubscribers();
    }
    else{
      // Delete any previously-existing route
      if (human->getMovement()) human->deleteMovement();

      // Define new destination
      Vector3 dest;
      dest.x = ((static_cast<double>(rand())) / RAND_MAX) * (2900) - 1400;
      dest.y = human->getPosition().y;
      dest.z = ((static_cast<double>(rand())) / RAND_MAX) * (1600) - 800;

      // Notify SimulationModel that human is moving to new destination
      this->human->setDetails("dest", dest.toString());
      this->human->notifySubscribers("NewDestination");

      // If human has a simulation model (it should),
      if (human->getModel()){
        // Set the movement of the human to a route with the randomized destination
        human->setMovement(new AstarStrategy(human->getPosition(), dest,
                                            human->getModel()->getGraph()));
      }
    }
  }
}
