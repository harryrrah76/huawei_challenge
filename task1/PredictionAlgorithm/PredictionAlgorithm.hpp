/*
 * This file must declare the following structures and methods.
 * Please don't modify this file.
 */

#include <cstdint>
#include <set>
#include <map>

struct RoboPredictor {
  struct RoboMemory;
  RoboMemory* roboMemory_ptr;

  bool predictTimeOfDayOnNextPlanet(std::uint64_t nextPlanetID,
                                    bool spaceshipComuterPrediction);

  void observeAndRecordTimeofdayOnNextPlanet(std::uint64_t nextPlanetID,
                                             bool timeOfDayOnNextPlanet);

  std::map<int, std::map<int, std::map<bool, int>>> get_planets();

  //---------------------------------------------------------------------
  // Since the struct RoboMemory is implicitly defined in .cpp
  // we need to move the declarations of constructor/destructor 
  // to .cpp too
  RoboPredictor();
  ~RoboPredictor();
};
