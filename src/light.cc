/**
 * @file light.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/light.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Light::Light() :
  motion_behavior_(this),
  collision_timer_(0),
  collision_cond_(false) {
  set_color(OBSTACLE_COLOR);
  set_pose(OBSTACLE_POSITION);
  set_radius(OBSTACLE_RADIUS);
  set_type(kLight);
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Light::TimestepUpdate(unsigned int dt) {
  motion_behavior_.UpdatePose(dt, get_velocity());

  // check if the light has collided with anything
  if (collision_cond_) {
    double secondsPassed = (clock() - collision_timer_) / CLOCKS_PER_SEC;
    if (secondsPassed < ARC_TIME) {
      set_velocity(5.0, 5.0);
      RelativeChangeHeading(-5);
    } else {
      collision_cond_ = false;
    }
  } else {
      set_velocity(3.0, 3.0);
    }
}

void Light::HandleCollision(EntityType object_type,
  ArenaEntity * object) {
  sensor_touch_->HandleCollision(object_type, object);
}

void Light::Reset() {
  set_pose(SetPoseRandomlyAux());
  set_radius(random() % (OBSTACLE_MAX_RADIUS - OBSTACLE_MIN_RADIUS + 1)
  + OBSTACLE_MIN_RADIUS);
}

NAMESPACE_END(csci3081);
