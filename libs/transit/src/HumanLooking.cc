#include "HumanLooking.h"
#include "HumanAvailable.h"
#include "AstarStrategy.h"

HumanLooking::HumanLooking(Human* human){
  this->human = human;
  std::cout << "Human Looking state instantiated" << std::endl;
}

void HumanLooking::update(double dt) {
  std::cout << "IN Update() for HumanLooking" << std::endl;

  // Check if package still exists (may have already been stolen by another car)
  bool packageExists = false;
  std::vector<Package*> packages = PackageDataController::getInstance()->getPackageList();
  for (int i=0;i<packages.size();i++){
      if (packages.at(i) == this->human->getPackage()){
          packageExists = true;
      }
  }

  std::cout << "HERE 1" << std::endl;

  // If human has reached the package and it still exists,
  if (human->getMovement() && human->getMovement()->isCompleted() && packageExists){

    std::cout << "HERE 2" << std::endl;

    // Delete any previously-existing route
    if (human->getMovement()) human->deleteMovement();

    std::cout << "HERE 3" << std::endl;

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

    std::cout << "HERE 4" << std::endl;

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

    // Change state
    this->human->changeState(new HumanAvailable(this->human));
    std::cout << "Human has been set from Looking to Available (package no longer exists)" << std::endl;
  }

  // //if human has not yet gotten to the package's destination
  // if (human->getMovement() && !human->getMovement()->isCompleted() && packageExists) {
  //   human->getMovement()->move(human, dt);
  // }
  // else if (packageExists) {
  //   // Delete any previously-existing route
  //   if (human->getMovement()) human->deleteMovement();

  //   // Notify cars
  //   std::cout << this->human->getName() << "found package!" << std::endl;
  //   this->human->updateSubscribers();
  //   this->human->notifySubscribers(this->human->getPackage()->getPosition());

  //   // Delete package from package singleton
  //   PackageDataController::getInstance()->removePackage(this->human->getPackage());

  //   // Resetting package assigned to human instance
  //   this->human->setPackage(nullptr);
    
  //   // Define new destination
  //   Vector3 dest;
  //   dest.x = ((static_cast<double>(rand())) / RAND_MAX) * (2900) - 1400;
  //   dest.y = human->getPosition().y;
  //   dest.z = ((static_cast<double>(rand())) / RAND_MAX) * (1600) - 800;

  //   // If human has a simulation model (it should),
  //   if (human->getModel()){
  //     // Set the movement of the human to a route with the randomized destination
  //     human->setMovement(new AstarStrategy(human->getPosition(), dest,
  //                                         human->getModel()->getGraph()));
  //   }

  //   human->changeState(new HumanAvailable(this->human));
  //   // std::cout << "Human has been set from Looking to Available" << std::endl;
  // }
  // else{
  //   this->human->changeState(new HumanAvailable(this->human));
  // }
}

