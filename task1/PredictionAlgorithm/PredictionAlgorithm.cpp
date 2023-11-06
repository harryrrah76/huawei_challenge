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

bool RoboPredictor::predictTimeOfDayOnNextPlanet(
    std::uint64_t nextPlanetID, bool spaceshipComputerPrediction)
{
  // Robo can consult data structures in its memory while predicting.
  // Example: access Robo's memory with roboMemory_ptr-><your RoboMemory
  // content>
  // Robo can perform computations using any data in its memory during
  // prediction. It is important not to exceed the computation cost threshold
  // while making predictions and updating RoboMemory. The computation cost of
  // prediction and updating RoboMemory is calculated by the playground
  // automatically and printed together with accuracy at the end of the
  // evaluation (see main.cpp for more details).
  // Simple prediction policy: follow the spaceship computer's suggestions
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

  std::string debug;
  if (roboMemory_ptr->current_predict)
  {
    debug = "DAY";
  }
  else
  {
    debug = "NIGHT";
  }

  // std::cout << nextPlanetID << "  " << debug << std::endl;

  return roboMemory_ptr->current_predict;
}

void RoboPredictor::observeAndRecordTimeofdayOnNextPlanet(
    std::uint64_t nextPlanetID, bool timeOfDayOnNextPlanet)
{
  // Robo can consult/update data structures in its memory
  // Example: access Robo's memory with roboMemory_ptr-><your RoboMemory
  // content>
  if (roboMemory_ptr->current_predict == timeOfDayOnNextPlanet)
  {
    roboMemory_ptr->previous_predict_correct = true;
  }
  else
  {
    roboMemory_ptr->previous_predict_correct = false;
  }

  roboMemory_ptr->previous_predict = roboMemory_ptr->current_predict;

  // It is important not to exceed the computation cost threshold while making
  // predictions and updating RoboMemory. The computation cost of prediction and
  // updating RoboMemory is calculated by the playground automatically and
  // printed together with accuracy at the end of the evaluation (see main.cpp
  // for more details).

  // Simple prediction policy: do nothing
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
