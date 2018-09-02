/**
 * @file aggressive_behavior.h
 *
 * @copyright 2017 Osamah Anwar, All rights reserved.
 */

#ifndef SRC_AGGRESSIVE_BEHAVIOR_H_
#define SRC_AGGRESSIVE_BEHAVIOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"
#include "src/robot_behavior.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class representing the aggressive behavior of a robot.
 *
 * This class inherits from RobotBehavior and uses an overrided method
 * to determine the velocity of the robot and pass it back to the robot
 * object to be used by the motion handler. 
 */
class AggressiveBehavior : public RobotBehavior {
 public:
  /**
   * @brief Constructor for initializing the behavior.
   */
  AggressiveBehavior();

  /**
   * @brief Calculate the velocity the robot should be moving at, depending
   * on several factors.
   *
   * @param[in] light_left The reading from the robots left light sensor.
   * @param[in] light_right The reading from the robots right light sensor.
   * @param[in] food_left The reading from the robots left food sensor.
   * @param[in] food_right The reading from the robots right light sensor.
   * @param[in] hungry The bool value that specifies whether the robot is hungry.
   * @param[out] returns the wheel velocity that has been calculated
   */
  WheelVelocity Movement(double light_left, double light_right,
                double food_left, double food_right, bool hungry) override;

  /**
  * @brief Command that returns the behavior type for the class.
  * @param[out] behv_ The enum type of the behavior
  */
  RobotBehaviorEnum get_behv() { return behv_; }
};

NAMESPACE_END(csci3081);

#endif  // SRC_AGGRESSIVE_BEHAVIOR_H_
