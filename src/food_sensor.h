/**
 * @file food_sensor.h
 *
 * @copyright 2017 Osamah Anwar, All rights reserved.
 */

#ifndef SRC_FOOD_SENSOR_H_
#define SRC_FOOD_SENSOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <vector>

#include "src/sensor.h"
#include "src/common.h"
#include "src/params.h"
#include "src/pose.h"
#include "src/rgb_color.h"
#include "src/robot.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

class Robot;

class FoodSensor : public Sensor {
 public:
  /**
   * @brief Constructor using initialization values from params.h.
   */
  FoodSensor();

  /**
   * @brief Constructor using explicit values from robot.
   *
   * @param[in] r a pointer to the robot
   * @param[in] sense_angle the angle at which the sensor will be placed.
   */
  FoodSensor(Robot *r, double sense_angle);

  /**
   * @brief Reset the Sensor to a newly constructed state (needed for reset
   * button to work in GUI).
   */
  void Reset() override;

  /**
   * @brief Get data from a subject entity and then process it.
   *
   * @param ent pointer to the entity that calls the method.
   */
  void Notify(Pose pose) override;

  /**
   * @brief Update position of the sensor.
   */
  void Update_Pose();
};

NAMESPACE_END(csci3081);

#endif  // SRC_FOOD_SENSOR_H_
