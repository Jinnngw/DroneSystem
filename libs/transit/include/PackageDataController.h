#ifndef PACKAGE_DATA_CONTROLLER_H_
#define PACKAGE_DATA_CONTROLLER_H_

#include <vector>

#include "Package.h"
#include "SimulationModel.h"

class PackageDataController {
 public:
  // Singleton pattern
  static PackageDataController* getInstance();

  void populatePackageData(SimulationModel* sim);

  void addPackage(Package* package);

  void removePackage(Package* package);

  std::vector<Package*> getPackageList();

  static PackageDataController* instance;
  std::vector<Package*> packageList;

 private:
  // Private constructor to prevent instantiation
  PackageDataController() = default;
};

#endif  // PACKAGE_DATA_CONTROLLER_H_
