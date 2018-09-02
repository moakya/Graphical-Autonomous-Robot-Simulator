/**
 * @file food_sensor.cc
 *
 * @copyright 2017 Osamah Anwar, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/food_sensor.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
FoodSensor::FoodSensor() {}

FoodSensor::FoodSensor(Robot *r, double sense_angle) {
  robot_ = r;
  heading_angle_ = sense_angle;
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void FoodSensor::Reset() {
  Update_Pose();
  set_reading(0.0);
}

void FoodSensor::Notify(Pose pose) {
  reading_ += numerator_ / (pow(Calculate_Distance(pose), 1.08));
  if (Calculate_Distance(pose) <= 5)
    robot_->ResetHunger();
}

void FoodSensor::Update_Pose() {
  double x = robot_->get_pose().x + robot_->get_radius() *
    cos(PI * (robot_->get_pose().theta + heading_angle_) / 180);
  double y = robot_->get_pose().y + robot_->get_radius() *
    sin(PI * (robot_->get_pose().theta + heading_angle_) / 180);
  Pose nPose(x, y);
  this->set_pose(nPose);
}

NAMESPACE_END(csci3081);
