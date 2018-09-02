/**
 * @file light.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_LIGHT_H_
#define SRC_LIGHT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>

#include "src/arena_mobile_entity.h"
#include "src/common.h"
#include "src/entity_type.h"
#include "src/pose.h"
#include "src/wheel_velocity.h"
#include "src/motion_handler.h"
#include "src/motion_behavior_differential.h"


/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class representing an immobile light within the Arena.
 *
 * Since lights are immobile, the Light class is very simple.
 */
class Light : public ArenaMobileEntity {
 public:
  /**
   * @brief Constructor.
   */
  Light();

  /**
   * @brief Get the name of the Light for visualization purposes, and to
   * aid in debugging.
   */
  std::string get_name() const override { return "Light"; }

  /**
   * @brief Handles the collision by setting the sensor to activated.
   */
  void HandleCollision(EntityType object_type, ArenaEntity * object = NULL);

  /**
   * @brief Update the light's position after the specified
   * duration has passed.
   *
   * @param dt The # of timesteps that have elapsed since the last update.
   */
  void TimestepUpdate(unsigned int dt) override;

  /**
  * @brief Command that returns the velocity.
  */
  WheelVelocity get_velocity() const { return velocity_; }

  /**
  * @brief Command that sets the velocity.
  */
  void set_velocity(double vl, double vr) {
    velocity_.left = vl;
    velocity_.right = vr;
  }

  /**
  * @brief Command that returns the motion_behavior.
  */
  MotionBehaviorDifferential get_motion_behavior() {return motion_behavior_;}

  /**
   * @brief Reset the Light using the initialization parameters received
   * by the constructor.
   */
  void Reset() override;

  /**
   * @brief Sets the collision timer on collision for reverse arc.
   */
  void set_collision_timer() { collision_timer_ = clock(); }

  /**
   * @brief Set the collision_cond_.
   *
   * @param flag bool value to set collisin_cond_ to
   */
  void set_collision_cond(bool flag) { collision_cond_ = flag; }

  /**
   * @brief Return the collision_cond_
   */
  bool get_collision_cond() { return collision_cond_; }

 private:
  WheelVelocity velocity_{3.0, 3.0};
  MotionBehaviorDifferential motion_behavior_;
  clock_t collision_timer_;
  bool collision_cond_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_LIGHT_H_
