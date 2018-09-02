/**
 * @file sensor.cc
 *
 * @copyright 2017 Osamah Anwar, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/sensor.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Sensor::Sensor() : pose_(), color_(192, 192, 192), robot_(NULL),
                   reading_(0.0), heading_angle_(0.0) {}

Sensor::~Sensor() {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
double Sensor::Calculate_Distance(Pose entPose) {
  return (sqrt(pow(pose_.x - entPose.x, 2.0) +
    pow(pose_.y - entPose.y, 2.0)));
}

void Sensor::Reset() {}

void Sensor::Notify(__unused Pose pose) {}

NAMESPACE_END(csci3081);
