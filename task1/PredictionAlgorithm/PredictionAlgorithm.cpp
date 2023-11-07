// This file contains a template for the implementation of Robo prediction
// algorithm
#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include "PredictionAlgorithm.hpp"
#include <random>
#include <time.h>
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> dis(0.0, 1.0);
struct RoboPredictor::RoboMemory
{
  // bool previous_predict;
  bool previous_predict_correct = false;
  bool current_predict = false;
  int error_count = 0;
  int previousPlanetID = 0;
  std::map<int, std::map<int, std::map<bool, int>>> planets;
};

bool RoboPredictor::predictTimeOfDayOnNextPlanet(
    std::uint64_t nextPlanetID, bool spaceshipComputerPrediction)
{
  // ==================== STATIC PREDICTION ====================
  // roboMemory_ptr->current_predict = false;                                             // Accuracy: 79.98%, Cost: 0.00/planet
  // ==================== STATIC PREDICTION ====================

  // ==================== 1 BIT BRANCH PREDICTOR ====================
  // if (!roboMemory_ptr->previous_predict_correct)                                       // Accuracy: 67.95%, Cost: 1.32/planet
  // {
  //   roboMemory_ptr->current_predict = !roboMemory_ptr->current_predict;
  // }
  // ==================== 1 BIT BRANCH PREDICTOR ====================

  // ==================== 2 BIT BRANCH PREDICTOR ====================
  // if (roboMemory_ptr->previous_predict_correct)                                        // Accuracy: 74.81%, Cost: 2.07/planet
  // {
  //   roboMemory_ptr->error_count = 0;
  // }
  // else
  // {
  //   roboMemory_ptr->error_count++;
  //   if (roboMemory_ptr->error_count >= 2)
  //   {
  //     roboMemory_ptr->current_predict = !roboMemory_ptr->current_predict;
  //     roboMemory_ptr->error_count = 0;
  //   }
  // }
  // ==================== 2 BIT BRANCH PREDICTOR ====================

  auto it_true = roboMemory_ptr->planets[nextPlanetID][roboMemory_ptr->previousPlanetID].find(true);
  auto it_false = roboMemory_ptr->planets[nextPlanetID][roboMemory_ptr->previousPlanetID].find(false);
  float true_value, false_value;
  if (it_true != roboMemory_ptr->planets[nextPlanetID][roboMemory_ptr->previousPlanetID].end())
  {
    true_value = it_true->second;
  }
  else
  {
    true_value = 0.0;
  }

  if (it_false != roboMemory_ptr->planets[nextPlanetID][roboMemory_ptr->previousPlanetID].end())
  {
    false_value = it_false->second;
  }
  else
  {
    false_value = 0.0;
  }

  if (true_value == 0 && false_value == 0)
  {
    if (roboMemory_ptr->previous_predict_correct) // Accuracy: 74.81%, Cost: 2.07/planet
    {
      roboMemory_ptr->error_count = 0;
    }
    else
    {
      roboMemory_ptr->error_count++;
      if (roboMemory_ptr->error_count >= 2)
      {
        roboMemory_ptr->current_predict = !roboMemory_ptr->current_predict;
        roboMemory_ptr->error_count = 0;
      }
    }
    return roboMemory_ptr->current_predict;
  }
  else
  {

    float random = dis(gen);
    // float random = (float)rand() / (float)RAND_MAX;
    // std::cout << random << std::endl;
    float day_ratio = true_value / (true_value + false_value);
    if (random >= day_ratio)
    {
      return false;
    }
    else
    {
      return true;
    }
  }

  // return roboMemory_ptr->current_predict;
}

void RoboPredictor::observeAndRecordTimeofdayOnNextPlanet(
    std::uint64_t nextPlanetID, bool timeOfDayOnNextPlanet)
{
  // ==================== 1&2 BIT BRANCH PREDICTOR ====================
  if (roboMemory_ptr->current_predict == timeOfDayOnNextPlanet)
  {
    roboMemory_ptr->previous_predict_correct = true;
  }
  else
  {
    roboMemory_ptr->previous_predict_correct = false;
  }
  // ==================== 1&2 BIT BRANCH PREDICTOR ====================

  roboMemory_ptr->planets[nextPlanetID][roboMemory_ptr->previousPlanetID][timeOfDayOnNextPlanet]++;
  roboMemory_ptr->previousPlanetID = nextPlanetID;
}

std::map<int, std::map<int, std::map<bool, int>>> RoboPredictor::get_planets()
{
  return roboMemory_ptr->planets;
}

//------------------------------------------------------------------------------
// Please don't modify this file below
//
// Check if RoboMemory does not exceed 64KiB
static_assert(
    sizeof(RoboPredictor::RoboMemory) <= 65536,
    "Robo's memory exceeds 65536 bytes (64KiB) in your implementation. "
    "Prediction algorithms using so much "
    "memory are ineligible. Please reduce the size of your RoboMemory struct.");

// Declare constructor/destructor for RoboPredictor
RoboPredictor::RoboPredictor()
{
  roboMemory_ptr = new RoboMemory;
}
RoboPredictor::~RoboPredictor()
{
  delete roboMemory_ptr;
}
