/**
 * @file robot.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>

#include "src/arena_mobile_entity.h"
#include "src/common.h"
#include "src/motion_handler_robot.h"
#include "src/motion_behavior_differential.h"
#include "src/entity_type.h"
#include "src/food.h"
#include "src/robot_behavior.h"
#include "src/light_sensor.h"
#include "src/food_sensor.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

class LightSensor;
class FoodSensor;
class MotionHandlerRobot;
class MotionBehaviorDifferential;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class representing a robot within the arena.
 *
 * Robots are composed of a motion handler, motion behavior, and touch sensor.
 * These classes interact to maintain the pose (position and heading) of the
 * robot. At each time step, the wheel velocities are used to calculate the
 * next pose of the robot. The handler manages the pose and user requests. The
 * behavior calculates the new pose based on wheel velocities.
 *
 * Robots can be controlled through keypress, which modify wheel velocities.
 *
 * The touch sensor is activated when the robot collides with an object.
 * The heading is modified after a collision to move the robot away from the
 * other object.
 */
class Robot : public ArenaMobileEntity {
 public:
  /**
   * @brief Constructor using initialization values from params.h.
   */

  Robot();

  /**
   * @brief Reset the Robot to a newly constructed state (needed for reset
   * button to work in GUI).
   */
  void Reset() override;

  /**
   * @brief Default destructor.
   */
  ~Robot() = default;

  /**
   * @brief Default = operator overload.
   */
  Robot &operator=(const Robot &other) = default;

  /**
   * @brief Default copy constructor.
   */
  Robot(const Robot &other) = default;

  /**
   * @brief Update the Robot's position and velocity after the specified
   * duration has passed.
   *
   * @param dt The # of timesteps that have elapsed since the last update.
   */
  void TimestepUpdate(unsigned int dt) override;

  /**
   * @brief Handles the collision by setting the sensor to activated.
   */
  void HandleCollision(EntityType object_type, ArenaEntity * object = NULL);

  /**
   * @brief Get the name of the Robot for visualization and for debugging.
   */
  std::string get_name() const override { return "Robot"; }

  /**
  * @brief Command that returns the motion_handler.
  */
  MotionHandlerRobot* get_motion_handler() {return motion_handler_;}

  /**
  * @brief Command that returns the motion_behavior.
  */
  MotionBehaviorDifferential get_motion_behavior() {return motion_behavior_;}

  /**
  * @brief Command that returns the RobotBehaviorEnum.
  */
  RobotBehaviorEnum get_behavior_enum() { return behv_type_; }

  /**
  * @brief Command that sets the RobotBehaviorEnum to the param.
  *
  * @param behv RobotBehavior enum to set behv_type_ to
  */
  void set_behavior_enum(RobotBehaviorEnum behv) { behv_type_ = behv; }

  /**
  * @brief Command that sets sets the RobotBehavior depending on the 
  * behavior type.
  */
  void set_behavior_handler() { motion_handler_->CreateBehavior(behv_type_); }

  /**
  * @brief Command that returns starvation timer
  */
  double get_starving() { return starving_; }

  /**
  * @brief Command that sets the starving timer to a specified value.
  */
  void set_starving(double num) { starving_ = num; }

  /**
  * @brief Command that resets the Timers for the robot.
  */
  void ResetHunger();

  /**
  * @brief Command that returns the status of the robot.
  */
  bool get_dead() { return dead_; }

  /**
  * @brief Command that sets the robot's status.
  */
  void set_dead(bool d) { dead_ = d; }

  /**
  * @brief Command that returns a pointer to the left light sensor.
  */
  LightSensor* get_left_light_sensor() const { return left_light_sensor_; }

  /**
  * @brief Command that returns a pointer to the right light sensor.
  */
  LightSensor* get_right_light_sensor() const { return right_light_sensor_; }

  /**
  * @brief Command that returns a pointer to the left food sensor.
  */
  FoodSensor* get_left_food_sensor() const { return left_food_sensor_; }

  /**
  * @brief Command that returns a pointer to the right food sensor.
  */
  FoodSensor* get_right_food_sensor() const { return right_food_sensor_; }

  /**
  * @brief Command that starts a collision timer for the robot.
  */
  void set_collision_timer() { collision_timer_ = clock(); }

  /**
  * @brief Command that sets the collision_cond_ depending on the param.
  */
  void set_collision_cond(bool flag) { collision_cond_ = flag; }

  /**
  * @brief Command that returns a bool value of the collision_cond_.
  */
  bool get_collision_cond() { return collision_cond_; }

  /**
  * @brief Command that sets the food_flag_ depending on param.
  */
  void set_food_flag(bool flag) { food_flag_ = flag; }

  /**
  * @brief Command that returns a bool value of the food_flag_.
  */
  bool get_food_flag() { return food_flag_; }

  /**
  * @brief Command that updates the hunger flags depending on the 
  * flag that is set by the arena.
  */
  void UpdateHunger();

  /**
  * @brief Command that updates the color of the robot depending on the 
  * behavior enum.
  */
  void UpdateColor(RobotBehaviorEnum behv);

 private:
  // Manages pose and wheel velocities that change with time and collisions.
  MotionHandlerRobot *motion_handler_;
  // Calculates changes in pose based on elapsed time and wheel velocities.
  MotionBehaviorDifferential motion_behavior_;
  // Enum that holds the behaviorType
  RobotBehaviorEnum behv_type_;
  // Pointer to the left light sensor
  LightSensor *left_light_sensor_;
  // Pointer to the right light sensor
  LightSensor *right_light_sensor_;
  // Pointer to the left food sensor
  FoodSensor *left_food_sensor_;
  // Pointer to the right food sensor
  FoodSensor *right_food_sensor_;
  // value to hold the hungry timer
  double hungry_;
  // bool value to determine whether the robot is hungry
  bool is_hungry_;
  // value to hold the starving timer
  double starving_;
  // bool value to determine whether the robot is starving
  bool is_starving_;
  // value to hold the death timer
  double death_timer_;
  // bool value to determine whether the robot is dead
  bool dead_;
  // clock value for the collsion
  clock_t collision_timer_;
  // determines whether the robot has collided with anything
  bool collision_cond_;
  // determines whether the food sensors are active
  bool food_flag_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_ROBOT_H_
