/**
 * @file robot_behavior.h
 *
 * @copyright 2017 Osamah Anwar, All rights reserved.
 */

#ifndef SRC_ROBOT_BEHAVIOR_H_
#define SRC_ROBOT_BEHAVIOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"
#include "src/wheel_velocity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

enum RobotBehaviorEnum {
  kAggressive, kExplore, kLove, kFear, kNothing
};

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class representing the behavior of a robot.
 *
 * This class acts as the parent class of the other behavior classes like
 * ExploreBehavior, AggressiveBehavior, LoveBehavior, and FearBehavior.
 */
class RobotBehavior {
 public:
  /**
   * @brief Constructor for initializing the behavior.
   */
  RobotBehavior();

  /**
   * @brief Desturctor for the class and its child classes.
   */
  virtual ~RobotBehavior() = default;

  /**
   * @brief Calculate the velocity the robot should be moving at, depending
   * on several factors.
   *
   * @param light_left The reading from the robots left light sensor.
   * @param light_right The reading from the robots right light sensor.
   * @param food_left The reading from the robots left food sensor.
   * @param food_right The reading from the robots right light sensor.
   * @param hungry The bool value that specifies whether the robot is hungry.
   */
  virtual WheelVelocity Movement(double llr, double lrr, double flr,
                     double frr, bool flag) = 0;

  /**
   * @brief Getter for the robot behavior enum
   *
   * @param[out] returns the enum value of the robot behavior
   */
  RobotBehaviorEnum get_behavior_enum() { return behv_; }

 protected:
  RobotBehaviorEnum behv_{kNothing};
};

NAMESPACE_END(csci3081);

#endif  // SRC_ROBOT_BEHAVIOR_H_
