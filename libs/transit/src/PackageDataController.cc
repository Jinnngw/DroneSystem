#include "PackageDataController.h"

PackageDataController PackageDataController::instance{};

PackageDataController& PackageDataController::getInstance() { return instance; }

void PackageDataController::populatePackageData(SimulationModel* sim) {
  // ...
}

std::vector<Package*> PackageDataController::getPackageList() {
  return packageList;
}
