#include "HumanAvailable.h"
#include "Human.h"
#include "AstarStrategy.h"
#include "JumpDecorator.h"
#include "HumanLooking.h"
#include "Package.h"
#include "SimulationModel.h"


HumanAvailable::HumanAvailable(Human* human)
{
    this->human = human;
    std::cout <<"human is available now"<< std::endl;
}

void HumanAvailable::update(double dt){
 
 
// if (this->human->getModel() && this->human->getModel()->scheduledDeliveries.size() > 0) {
     
    Package* package = this->human->getModel()->scheduledDeliveries.front();
    // std::cout << package << std::endl;
    this->human->getModel()->scheduledDeliveries.pop_front();

     //check whether human get package's information
    if (package) {
      
    std::cout << "get package's information" << std::endl;
      Vector3 packagePosition = package->getPosition();
      this->human->changeState(new HumanLooking(this->human));


     // Path strategy with JumpDecorator
    IStrategy* pathStrategy = new JumpDecorator(new JumpDecorator(
      new AstarStrategy(this->human->getPosition(), packagePosition,
                        human->getModel()->getGraph())));
    
    //Travel to package
    this->human->setMovement(pathStrategy);

    //change human's state from available to looking for package
    this->human->changeState(new HumanLooking(this->human));
    
    std::cout << "Human has been set from Available to Looking" << std::endl;

    }

    else{
    
       if (human->getMovement() && !human->getMovement()->isCompleted()) 
       {
         std::cout << "get to movement" << std::endl;
         human->getMovement()->move(human, dt);
       } else {
        if (human->getMovement()) human->deleteMovement();
        std::cout << "set movement" << std::endl;
        Vector3 dest;
        dest.x = ((static_cast<double>(rand())) / RAND_MAX) * (2900) - 1400;
        dest.y = human->getPosition().y;
        dest.z = ((static_cast<double>(rand())) / RAND_MAX) * (1600) - 800;
        if (human->getModel())
        human->setMovement(new AstarStrategy(human->getPosition(), dest,
                                            human->getModel()->getGraph()));
        std::cout << "have movement" << std::endl;

      }

    }

   

}
