/**
 * @file aggressive_behavior.cc
 *
 * @copyright 2017 Osamah Anwar, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/aggressive_behavior.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
AggressiveBehavior::AggressiveBehavior() {
  // ensure that the class reflects the correct behavior
  behv_ = kAggressive;
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
WheelVelocity AggressiveBehavior::Movement(double light_left,
             double light_right, double food_left, double food_right,
             bool hungry) {
  // identifier to store the wheel velocity
  WheelVelocity vel;

  // default values for the offsets
  double offset_a = 0;
  double offset_b = 0;

  // depending on the hunger condition change the offset values
  if (hungry) {
    offset_a = food_right;
    offset_b = food_left;
  }

  // determine the velocity
  vel.set_velocity((0.5 * offset_a) + (0.5 * light_right),
    (0.5 * offset_b) + (0.5 * light_left));

  return vel;
}

NAMESPACE_END(csci3081);
