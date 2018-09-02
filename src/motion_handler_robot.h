/**
 * @file motion_handler_robot.h
 *
 * @copyright 2018 3081 Staff, All rights reserved.
 */

#ifndef SRC_MOTION_HANDLER_ROBOT_H_
#define SRC_MOTION_HANDLER_ROBOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cassert>
#include <iostream>

#include "src/common.h"
#include "src/motion_handler.h"
#include "src/sensor_touch.h"
#include "src/communication.h"
#include "src/wheel_velocity.h"
#include "src/fear_behavior.h"
#include "src/love_behavior.h"
#include "src/explore_behavior.h"
#include "src/aggressive_behavior.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/

/**
 * @brief Class managing a Robot's speed and heading angle based
 * on collisions and user inputs.
 *
 * Currently, both wheels are always going at maximum speed, and
 * cannot be controlled independently.
 */
class MotionHandlerRobot : public MotionHandler {
 public:
  /**
   * @brief Default constructor.
   */
  MotionHandlerRobot();

  /**
   * @brief Explicit value contructor adds a pointer to the ent .
   */
  explicit MotionHandlerRobot(ArenaMobileEntity * ent)
    : MotionHandler(ent) {}

  /**
   * @brief Default copy constructor.
   */
  MotionHandlerRobot(const MotionHandlerRobot& other) = default;

  /**
   * @brief Default = operator overload.
   */
  MotionHandlerRobot& operator=(const MotionHandlerRobot& other) = default;

  /**
  * @brief Update the speed and the pose angle.
  */
  void UpdateVelocity() override;

  /**
  * @brief Update the speed and the pose angle according to the
  * behavior of the robot in question.
  *
  * @param[in] vel The current velocity.
  */
  void UpdateVelocity(WheelVelocity vel);

  /**
   * @brief Calculate the velocity the robot should be moving at, depending
   * on several factors, and then update it accordingly.
   *
   * @param[in] light_left The reading from the robots left light sensor.
   * @param[in] light_right The reading from the robots right light sensor.
   * @param[in] food_left The reading from the robots left food sensor.
   * @param[in] food_right The reading from the robots right light sensor.
   * @param[in] hungry The bool value that specifies whether the robot is hungry.
   * @param[in] starving The bool value that determines whether the robot is starving.
   */
  void UpdateVelocity(double light_left, double light_right,
        double food_left, double food_right, bool hungry, bool starving);

  /**
   * @brief Increase the overall speed of the entity by speed_delta.
   */
  void IncreaseSpeed() override;

  /**
   * @brief Decrease the overall speed of the entity by speed_delta.
   */
  void DecreaseSpeed() override;

  /**
   * @brief Turn the entity to the right by angle_delta (in degrees?)
   */
  void TurnRight() override;

  /**
   * @brief Turn the entity to the left by angle_delta (in degrees?)
   */
  void TurnLeft() override;

  /**
   * @brief Initializes the behv_ member depending on the param
   *
   * @param[in] behv The Enum that determines what the behavior of the
   * robot will be
   */
  void CreateBehavior(RobotBehaviorEnum behv);

  /**
   * @brief Getter for the robot behavior
   *
   * @param[out] returns the robot behavior pointer
   */
  RobotBehavior * get_behavior() { return behv_; }

  /**
   * @brief Method that ensures the number stays in a specific range
   *
   * @param[in] vel one of the velocity values from Wheel Velocity 
   *
   * @param[out] returns the number within the range if valid
   */
  double clamp_vel(double vel);

 private:
  // Manages the RobotBehavior type by using a pointer
  RobotBehavior* behv_{nullptr};
};

NAMESPACE_END(csci3081);

#endif  // SRC_MOTION_HANDLER_ROBOT_H_
