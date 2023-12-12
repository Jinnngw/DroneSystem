#include "PackageDataController.h"

PackageDataController* PackageDataController::instance = nullptr;

PackageDataController* PackageDataController::getInstance() {
  if (instance == nullptr){
    instance = new PackageDataController();
  }
  return instance;
}

void PackageDataController::populatePackageData(SimulationModel* sim) {
  
}

void PackageDataController::addPackage(Package* package){
  this->packageList.push_back(package);
}

void PackageDataController::removePackage(Package* package){
  for (int i=0;i<packageList.size();i++){
    if (packageList[i] == package){
      packageList.erase(packageList.begin() + i);
      return;
    }
  }
}

std::vector<Package*> PackageDataController::getPackageList() {
  return packageList;
}
