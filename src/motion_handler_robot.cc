/**
 * @file motion_handler_robot.cc
 *
 * @copyright 2018 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/motion_handler_robot.h"
#include "src/motion_behavior_differential.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void MotionHandlerRobot::CreateBehavior(RobotBehaviorEnum behv) {
  switch (behv) {
    case kAggressive: behv_ = new AggressiveBehavior;
      break;
    case kExplore: behv_ = new ExploreBehavior;
      break;
    case kLove: behv_ = new LoveBehavior;
      break;
    case kFear: behv_ = new FearBehavior;
      break;
    default: behv_ = new FearBehavior;
  }
}

void MotionHandlerRobot::TurnLeft() {
  double x = get_velocity().left  - get_angle_delta(),
         y = get_velocity().right + get_angle_delta();

  if (get_velocity().left  - get_angle_delta() < 0)
    x = 0;

  if (get_velocity().right + get_angle_delta() > get_max_speed())
    y = get_max_speed();

  set_velocity(x, y);
}

void MotionHandlerRobot::TurnRight() {
  double x = get_velocity().left  + get_angle_delta(),
         y = get_velocity().right - get_angle_delta();

  if (get_velocity().left  + get_angle_delta() > get_max_speed())
    x = get_max_speed();

  if (get_velocity().right - get_angle_delta() < 0)
    y = 0;

  set_velocity(x, y);
}

void MotionHandlerRobot::IncreaseSpeed() {
  set_velocity(clamp_vel(get_velocity().left + get_speed_delta()),
               clamp_vel(get_velocity().right + get_speed_delta()));
}

void MotionHandlerRobot::DecreaseSpeed() {
  set_velocity(clamp_vel(get_velocity().left  - get_speed_delta()),
               clamp_vel(get_velocity().right - get_speed_delta()));
}

void MotionHandlerRobot::UpdateVelocity() {
  if (entity_->get_touch_sensor()->get_output()) {
    entity_->RelativeChangeHeading(+180);
  }
}

void MotionHandlerRobot::UpdateVelocity(double light_left, double light_right,
            double food_left, double food_right, bool hungry, bool starving) {
  WheelVelocity vel;
  if (starving) {
    vel.set_velocity(0.4 * food_right, 0.4 * food_left);
  } else {
    vel = behv_->Movement(light_left, light_right,
        food_left, food_right, hungry);
  }
  this->set_velocity(clamp_vel(vel.left), clamp_vel(vel.right));
  if (entity_->get_touch_sensor()->get_output())
    entity_->RelativeChangeHeading(+180);
}

void MotionHandlerRobot::UpdateVelocity(WheelVelocity vel) {
  this->set_velocity(clamp_vel(vel.left), clamp_vel(vel.right));
  if (entity_->get_touch_sensor()->get_output())
    entity_->RelativeChangeHeading(+180);
}

double MotionHandlerRobot::clamp_vel(double vel) {
  double clamped = 0.0;
  if (vel > 0)
    clamped = (vel > get_max_speed()) ?
              get_max_speed() :
              vel;
  return clamped;
}

NAMESPACE_END(csci3081);
