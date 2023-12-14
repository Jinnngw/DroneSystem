#include "PackageDataController.h"

PackageDataController* PackageDataController::instance = nullptr;

/**
 * @brief Retrieves the singleton instance of PackageDataController.
 * @return Pointer to the singleton instance of PackageDataController.
 */
PackageDataController* PackageDataController::getInstance() {
  if (instance == nullptr){
    instance = new PackageDataController();
  }
  return instance;
}

/**
 * @brief Populates package data for the simulation model.
 * @param sim Pointer to the SimulationModel.
 */
void PackageDataController::populatePackageData(SimulationModel* sim) {
  
}

/**
 * @brief Adds a package to the controller's package list.
 * @param package Pointer to the Package to add.
 */
void PackageDataController::addPackage(Package* package){
  this->packageList.push_back(package);
}

/**
 * @brief Removes a package from the controller's package list.
 * @param package Pointer to the Package to remove.
 */
void PackageDataController::removePackage(Package* package){
  for (int i=0;i<packageList.size();i++){
    if (packageList[i] == package){
      packageList.erase(packageList.begin() + i);
      return;
    }
  }
}

/**
 * @brief Retrieves the list of packages.
 * @return Vector of pointers to Package objects.
 */
std::vector<Package*> PackageDataController::getPackageList() {
  return packageList;
}
