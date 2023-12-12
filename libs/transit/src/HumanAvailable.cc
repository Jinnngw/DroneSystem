#include "HumanAvailable.h"
#include "Human.h"
#include "AstarStrategy.h"
#include "JumpDecorator.h"
#include "HumanLooking.h"
#include "Package.h"
#include "SimulationModel.h"


HumanAvailable::HumanAvailable(Human* human){
    this->human = human;
}

void HumanAvailable::update(double dt){
  // Get next package (null if no package)
  this->human->getNextDelivery();

  // If human has a package to get to
  if (human->getPackage()){
    this->human->changeState(new HumanLooking(this->human));
    std::cout << "Human has switched from Available to Looking" << std::endl;
  }

  // Otherwise, go to random destination
  else {
    if (human->getMovement() && !human->getMovement()->isCompleted()){
      human->getMovement()->move(human, dt);
    }
    else{      
      // Delete any previously-existing route
      if (human->getMovement()) human->deleteMovement();
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
    }
  }
}
