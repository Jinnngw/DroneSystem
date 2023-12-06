#ifndef PACKAGE_DATA_CONTROLLER_H_
#define PACKAGE_DATA_CONTROLLER_H_

#include <vector>

#include "Package.h"
#include "SimulationModel.h"

class PackageDataController {
 public:
  // Singleton pattern
  static PackageDataController& getInstance();

  void populatePackageData(SimulationModel* sim);

  std::vector<Package*> getPackageList();

 private:
  // Private constructor to prevent instantiation
  PackageDataController() = default;
  static PackageDataController instance;
  std::vector<Package*> packageList;
};

#endif  // PACKAGE_DATA_CONTROLLER_H_
