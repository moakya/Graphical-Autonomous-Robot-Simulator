/**
 * @file light_sensor.h
 *
 * @copyright 2017 Osamah Anwar, All rights reserved.
 */

#ifndef SRC_LIGHT_SENSOR_H_
#define SRC_LIGHT_SENSOR_H_

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

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class representing the light sensor for the robot.
 *
 * This class inherits from Sensor and uses an overrided methods
 * to determine the readings for the robot to use to set its velocity.
 */
class LightSensor : public Sensor {
 public:
  /**
   * @brief Constructor using initialization values from params.h.
   */
  LightSensor();

  /**
   * @brief Constructor using explicit values from robot.
   *
   * @param[in] r a pointer to the robot
   * @param[in] sense_angle the angle at which the sensor will be placed.
   */
  LightSensor(Robot *r, double sense_angle);

  /**
   * @brief Reset the Sensor to a newly constructed state (needed for reset
   * button to work in GUI).
   */
  void Reset() override;

  /**
   * @brief Get data from a subject entity and then process it.
   *
   * @param pose Pose of the entity that is passed in.
   */
  void Notify(Pose pose) override;

  /**
   * @brief Update the position of the light sensor.
   */
  void Update_Pose();
};

NAMESPACE_END(csci3081);

#endif  // SRC_LIGHT_SENSOR_H_
