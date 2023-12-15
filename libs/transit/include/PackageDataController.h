#ifndef PACKAGE_DATA_CONTROLLER_H_
#define PACKAGE_DATA_CONTROLLER_H_

#include <vector>

#include "Package.h"
#include "SimulationModel.h"

class PackageDataController {
 public:
  // Singleton pattern
  static PackageDataController* getInstance();

  /**
   * @brief Populates package data based on the simulation model.
   * @param sim Pointer to the SimulationModel.
   */
  void populatePackageData(SimulationModel* sim);

  /**
   * @brief Adds a package to the controller's list.
   * @param package Pointer to the package to be added.
   */
  void addPackage(Package* package);

  /**
   * @brief Removes a package from the controller's list.
   * @param package Pointer to the package to be removed.
   */
  void removePackage(Package* package);

  /**
   * @brief Gets the list of all packages.
   * @return Vector of pointers to packages.
   */
  std::vector<Package*> getPackageList();

  static PackageDataController* instance;
  std::vector<Package*> packageList;

 private:
  // Private constructor to prevent instantiation
  PackageDataController() = default;
};

#endif  // PACKAGE_DATA_CONTROLLER_H_
