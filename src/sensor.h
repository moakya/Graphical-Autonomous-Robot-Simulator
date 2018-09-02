/**
 * @file sensor.h
 *
 * @copyright 2017 Osamah Anwar, All rights reserved.
 */

#ifndef SRC_SENSOR_H_
#define SRC_SENSOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <math.h>
#include <string>
#include <vector>

#include "src/common.h"
#include "src/params.h"
#include "src/pose.h"
#include "src/rgb_color.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

class Robot;

class Sensor{
 public:
  /**
   * @brief Constructor using initialization values from params.h.
   */
  Sensor();

  /**
   * @brief Destructor for the sensor.
   */
  virtual ~Sensor();

  /**
   * @brief Default = operator overload.
   */
  Sensor &operator=(const Sensor &other) = default;

  /**
   * @brief Default copy constructor.
   */
  Sensor(const Sensor &other) = default;

  /**
   * @brief Reset the Sensor to a newly constructed state (needed for reset
   * button to work in GUI).
   */
  virtual void Reset();

  /**
  * @brief Command that returns the pose.
  */
  Pose get_pose() { return pose_; }

  /**
  * @brief Command that sets the pose.
  */
  void set_pose(Pose pose) { pose_ = pose; }

  /**
  * @brief Command that sets the reading.
  */
  void set_reading(double r) { reading_ = r; }

  /**
  * @brief Command that gets the reading.
  */
  double get_reading() { return reading_; }

  /**
  * @brief Command that gets the Robot *.
  */
  Robot* get_robot() { return robot_; }

  /**
  * @brief Command that sets the robot.
  */
  void set_robot(Robot * r) { robot_ = r; }

  /**
  * @brief Command that sets the color of the sensor.
  */
  void set_color(RgbColor col) { color_ = col; }

  /**
  * @brief Command that gets the color of the sensor.
  */
  RgbColor get_color() { return color_; }

  /**
  * @brief Command that gets the heading angle of the sensor.
  */
  double get_heading_angle() { return heading_angle_; }

  /**
  * @brief Command that sets the heading angle of the sensor.
  */
  void set_heading_angle(double ang) { heading_angle_ = ang; }

  /**
  * @brief Command that sets the sensitivity of the sensor.
  */
  void set_numerator(int num) { numerator_ = num; }

  /**
  * @brief Command that returns the sensitivity of the sensor.
  */
  int get_numerator() { return numerator_; }

  /**
  * @brief Command that calculates the distance b/w two entities.
  */
  double Calculate_Distance(Pose entPose);

  /**
  * @brief Command that Resets the Reading of the object.
  */
  void Reset_Reading() { reading_ = 0.0; }

  /**
  * @brief Command that does the calculations for the robot's movement.
  */
  virtual void Notify(__unused Pose entPose);

 protected:
  // Pose for the sensor
  Pose pose_;
  // color of the sensor
  RgbColor color_;
  // pointer ot the robot
  Robot *robot_;
  // reading that the snesor calculates
  double reading_;
  // the intial angle of the sensor
  double heading_angle_;
  // the numerator to calculate reading
  int numerator_{1200};
};

NAMESPACE_END(csci3081);

#endif  // SRC_SENSOR_H_
