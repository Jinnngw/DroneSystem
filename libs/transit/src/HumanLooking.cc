#include "HumanLooking.h"
#include "HumanAvailable.h"
#include "AstarStrategy.h"

HumanLooking::HumanLooking(Human* human){
  this->human = human;
}

void HumanLooking::update(double dt) {

  // Check if package still exists (may have already been stolen by another car)
  bool packageExists = false;
  std::vector<Package*> packages = PackageDataController::getInstance()->getPackageList();
  for (int i=0;i<packages.size();i++){
      if (packages.at(i) == this->human->getPackage()){
          packageExists = true;
      }
  }

  // If human has reached the package and it still exists,
  if (human->getMovement() && human->getMovement()->isCompleted() && packageExists){

    // Delete any previously-existing route
    if (human->getMovement()) human->deleteMovement();

    // Update car subscribers based on distance from human
    std::cout << this->human->getName() << " found " << this->human->getPackage()->getName() << "!" << std::endl;
    this->human->updateSubscribers();

    // Check if package still exists (may have already been stolen by another car)
    packageExists = false;
    packages = PackageDataController::getInstance()->getPackageList();
    for (int i=0;i<packages.size();i++){
        if (packages.at(i) == this->human->getPackage()){
            packageExists = true;
        }
    }

    // Notify car subscribers if package still exists
    if (packageExists){
      this->human->notifySubscribers(this->human->getPackage()->getPosition());
    }


    // Add found/already stolen package to list of found packages
    this->human->addFoundPackage(this->human->getPackage());

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

    // Change Human's state to Available
    human->changeState(new HumanAvailable(this->human));
    std::cout << "Human has been set from Looking to Available" << std::endl;
  }
  // Otherwise, if the package still exists,
  else if (packageExists){
    human->getMovement()->move(human, dt);
  }
  else{
    // Delete any previously-existing route
    if (human->getMovement()) human->deleteMovement();

    // Add found/already stolen package to list of found packages
    this->human->addFoundPackage(this->human->getPackage());

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

    // Notifying observer (SimulationModel) that car has stolen package
    if (this->human->getPackage()){
      this->human->setDetails("package", this->human->getPackage()->getName());
      this->human->notifySubscribers("FoundPackage");
    }

    // Change state
    this->human->changeState(new HumanAvailable(this->human));
    std::cout << "Human has been set from Looking to Available (package no longer exists)" << std::endl;
  }
}

