#include "PackageDataController.h"

PackageDataController* PackageDataController::instance = nullptr;

PackageDataController* PackageDataController::getInstance() {
  if (instance == nullptr){
    instance = new PackageDataController();
  }
  return instance;
}

void PackageDataController::populatePackageData(SimulationModel* sim) {
  // ...
}

std::vector<Package*> PackageDataController::getPackageList() {
  return packageList;
}
