// This file contains a template for the implementation of Robo prediction
// algorithm
#include <iostream>
#include <string>
#include "PredictionAlgorithm.hpp"

struct RoboPredictor::RoboMemory
{
  // Place your RoboMemory content here
  bool previous_predict;
  bool previous_predict_correct;
  bool current_predict;
  int error_count;
  // Note that the size of this data structure can't exceed 64KiB!
};

// ==================== 2 BIT BRANCH PREDICTOR ====================
bool RoboPredictor::predictTimeOfDayOnNextPlanet(
    std::uint64_t nextPlanetID, bool spaceshipComputerPrediction)
{
  if (roboMemory_ptr->previous_predict_correct)
  {
    roboMemory_ptr->current_predict = roboMemory_ptr->previous_predict;
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
    else
    {
      roboMemory_ptr->current_predict = roboMemory_ptr->previous_predict;
    }
  }

  // ==================== DEBUG ====================
  // std::string debug;
  // if (roboMemory_ptr->current_predict)
  // {
  //   debug = "DAY";
  // }
  // else
  // {
  //   debug = "NIGHT";
  // }
  // std::cout << nextPlanetID << "  " << debug << std::endl;

  return roboMemory_ptr->current_predict;
}

void RoboPredictor::observeAndRecordTimeofdayOnNextPlanet(
    std::uint64_t nextPlanetID, bool timeOfDayOnNextPlanet)
{
  if (roboMemory_ptr->current_predict == timeOfDayOnNextPlanet)
  {
    roboMemory_ptr->previous_predict_correct = true;
  }
  else
  {
    roboMemory_ptr->previous_predict_correct = false;
  }

  roboMemory_ptr->previous_predict = roboMemory_ptr->current_predict;
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
