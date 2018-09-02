/**
 * @file robot.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/robot.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Robot::Robot() :
  motion_handler_(new MotionHandlerRobot(this)),
  motion_behavior_(this),
  behv_type_(kNothing),
  left_light_sensor_(new LightSensor(this, -40.0)),
  right_light_sensor_(new LightSensor(this, +40.0)),
  left_food_sensor_(new FoodSensor(this, -40.0)),
  right_food_sensor_(new FoodSensor(this, +40.0)),
  hungry_(ROBOT_HUNGER),
  is_hungry_(false),
  starving_(ROBOT_STARVE),
  is_starving_(false),
  death_timer_(ROBOT_DEATH),
  dead_(false),
  collision_timer_(0),
  collision_cond_(false),
  food_flag_(true) {
  set_type(kRobot);
  set_color(ROBOT_COLOR);
  set_pose(SetPoseRandomlyAux());
  set_radius(random() % (ROBOT_MAX_RADIUS -
    ROBOT_MIN_RADIUS + 1) + ROBOT_MIN_RADIUS);
}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Robot::TimestepUpdate(unsigned int dt) {
  // update sensor positions
  left_light_sensor_->Update_Pose();
  right_light_sensor_->Update_Pose();
  left_food_sensor_->Update_Pose();
  right_food_sensor_->Update_Pose();

  UpdateHunger();

  // check if the robot has collided with something
  if (collision_cond_) {
    WheelVelocity vel_a(7.0, 7.0);
    double secondsPassed = (clock() - collision_timer_) / CLOCKS_PER_SEC;
    if (secondsPassed < ARC_TIME) {
      motion_handler_->UpdateVelocity(vel_a);  // change velocity
      RelativeChangeHeading(4);
    } else {
      collision_cond_ = false;  // reset the flag
    }
  }

  // update the velocity of the robot
  motion_handler_->UpdateVelocity(left_light_sensor_->get_reading(),
    right_light_sensor_->get_reading(), left_food_sensor_->get_reading(),
    right_food_sensor_->get_reading(), is_hungry_, is_starving_);

  // Update robot position
  motion_behavior_.UpdatePose(dt, motion_handler_->get_velocity());

  // Reset Sensors for next cycle
  left_light_sensor_->Reset();
  right_light_sensor_->Reset();
  left_food_sensor_->Reset();
  right_food_sensor_->Reset();
  sensor_touch_->Reset();
}

void Robot::ResetHunger() {
  hungry_ = ROBOT_HUNGER;
  is_hungry_ = false;
  starving_ = ROBOT_STARVE,
  is_starving_ = false,
  death_timer_ = ROBOT_DEATH;
}

void Robot::UpdateHunger() {
  if (food_flag_) {
    // ensure robot's death status
    if (!dead_) {
      death_timer_--;  // decrement the timer
      if (death_timer_ <= 0)
        dead_ = true;
    }

    // change the flag if the roobt is starving
    if (!is_starving_) {
      starving_--;  // decrement the timer
      if (starving_ <= 0)
        is_starving_ = true;
    }

    // change the flag if the robot is hungry
    if (!is_hungry_) {
      hungry_--;  // decrement the timer
      if (hungry_ <= 0)
        is_hungry_ = true;
    }
  }  // end outer most it
}

void Robot::Reset() {
  motion_handler_->set_velocity(0.0, 0.0);
  set_pose(SetPoseRandomlyAux());
  set_radius(random() % (ROBOT_MAX_RADIUS -
    ROBOT_MIN_RADIUS + 1) + ROBOT_MIN_RADIUS);
  motion_handler_->set_max_speed(ROBOT_MAX_SPEED);
  motion_handler_->set_max_angle(ROBOT_MAX_ANGLE);
  sensor_touch_->Reset();
  left_light_sensor_->Reset();
  right_light_sensor_->Reset();
  left_food_sensor_->Reset();
  right_food_sensor_->Reset();
  ResetHunger();
  dead_ = false;
  collision_cond_ = false;
}

void Robot::HandleCollision(EntityType object_type, ArenaEntity * object) {
  sensor_touch_->HandleCollision(object_type, object);
}

void Robot::UpdateColor(RobotBehaviorEnum behv) {
  switch (behv) {
    case kFear: set_color(FEAR_COLOR);
      break;
    case kAggressive: set_color(AGGRESSIVE_COLOR);
      break;
    case kLove: set_color(LOVE_COLOR);
      break;
    case kExplore: set_color(EXPLORE_COLOR);
      break;
    default: set_color(ROBOT_COLOR);
  }
}

NAMESPACE_END(csci3081);
