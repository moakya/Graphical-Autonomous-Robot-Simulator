/**
 * @file light_sensor_test.cc
 *
 * @copyright 2017 Osamah Anwar, All rights reserved.
 */

// Google Test Framework
#include <gtest/gtest.h>
#include <cmath>

// Project code from the ../src directory
#include "../src/light_sensor.h"
#include "../src/light.h"
#include "../src/robot.h"
#include "../src/pose.h"

/*******************************************************************************
 * Test Cases
 ******************************************************************************/
#ifdef LIGHT_SENSOR_TEST

class LightSensorTest : public ::testing::Test {
 public:
  LightSensorTest() {}
 protected:
  virtual void SetUp() {
    light_close.set_pose(csci3081::Pose(1, 1));
    light_mid.set_pose(csci3081::Pose(600, 475));
    light_far.set_pose(csci3081::Pose(1190, 940));

    light_sensor_a.set_pose(csci3081::Pose(0.5, 0.5));
    light_sensor_b.set_pose(csci3081::Pose(600, 475));
    light_sensor_c.set_pose(csci3081::Pose(1190, 940));
  }
  csci3081::Light light_close, light_mid, light_far;
  csci3081::LightSensor light_sensor_a, light_sensor_b, light_sensor_c,
    light_sensor_d;
  csci3081::Robot *rptr = new csci3081::Robot();
};

// Default Constructor
TEST_F(LightSensorTest, DefaultConstructor) {
  EXPECT_EQ(light_sensor_d.get_pose().x, 0)
    << "\nFAIL DefaultConstructor: pose.x\n";
  EXPECT_EQ(light_sensor_d.get_pose().y, 0)
    << "\nFAIL DefaultConstructor: pose.y\n";
  EXPECT_EQ(light_sensor_d.get_color().r, 192)
    << "\nFAIL DefaultConstructor: color.r\n";
  EXPECT_EQ(light_sensor_d.get_color().g, 192)
    << "\nFAIL DefaultConstructor: color.g\n";
  EXPECT_EQ(light_sensor_d.get_color().b, 192)
    << "\nFAIL DefaultConstructor: color.b\n";
  EXPECT_EQ(light_sensor_d.get_robot(), nullptr)
    << "\nFAIL DefaultConstructor: robot\n";
}

// Explicit Value Constructor
TEST_F(LightSensorTest, ConstructorwithInput) {
  csci3081::LightSensor ls4(rptr, 40.0);
  EXPECT_EQ(ls4.get_color().r, 192) << "\nFAIL ConstructorwithInput: color.r\n";
  EXPECT_EQ(ls4.get_color().g, 192) << "\nFAIL ConstructorwithInput: color.g\n";
  EXPECT_EQ(ls4.get_color().b, 192) << "\nFAIL ConstructorwithInput: color.b\n";
  EXPECT_EQ(ls4.get_robot(), rptr) << "\nFAIL ConstructorwithInput: robot\n";
  EXPECT_EQ(ls4.get_heading_angle(), 40.0);
}

// Update Pose Test
TEST_F(LightSensorTest, UpdatingPose) {
  csci3081::LightSensor ls4(rptr, 40);
  ls4.Update_Pose();
  EXPECT_LE(abs(ls4.get_pose().x - rptr->get_pose().x), rptr->get_radius())
    << "\nFAIL UpdatingPose: pose.x\n";
  EXPECT_LE(abs(ls4.get_pose().y - rptr->get_pose().y), rptr->get_radius())
    << "\nFAIL UpdatingPose: pose.y\n";
}

// Reset Method Test
TEST_F(LightSensorTest, Reseting) {
  csci3081::LightSensor ls4(rptr, 40);
  ls4.Reset();
  EXPECT_LE(abs(ls4.get_pose().x - rptr->get_pose().x), rptr->get_radius())
    << "\nFAIL Reseting: pose.x\n";
  EXPECT_LE(abs(ls4.get_pose().y - rptr->get_pose().y), rptr->get_radius())
    << "\nFAIL Reseting: pose.y\n";
  EXPECT_EQ(ls4.get_reading(), 0.0) << "\nFAIL Reset: reading\n";
}

// Updating Numerator Test
TEST_F(LightSensorTest, UpdatingNumerator) {
  csci3081::LightSensor ls4(rptr, 40);
  ls4.set_numerator(50);
  EXPECT_EQ(ls4.get_numerator(), 50.0)
    << "\nFAIL UpdatingNumerator: UpdateNumerator\n";
  ls4.set_numerator(100);
  EXPECT_EQ(ls4.get_numerator(), 100.0)
    << "\nFAIL UpdatingNumerator: set_numerator\n";
}

// Calculate Distance Test
TEST_F(LightSensorTest, CalculateDistance) {
  csci3081::LightSensor ls4(rptr, 40);
  csci3081::Robot *rob = new csci3081::Robot();
  double x_coord = rob->get_pose().x;
  double y_coord = rob->get_pose().y;
  csci3081::Pose nPose(x_coord, y_coord);
  double dist = ls4.Calculate_Distance(nPose);
  EXPECT_EQ(dist, sqrt(pow(ls4.get_pose().x - x_coord, 2.0) +
    pow(ls4.get_pose().y - y_coord, 2.0)))
    << "\nFAIL CalculateDistance: distance\n";
}

// One light close
TEST_F(LightSensorTest, NotifyOneLightVeryClose) {
  light_sensor_a.Reset_Reading();
  light_sensor_a.Notify(light_close.get_pose());
  EXPECT_GE(light_sensor_a.get_reading(), 1000)
    << "\nFAIL NotifyOneLightVeryClose\n";
}

// One light on top of sensor
TEST_F(LightSensorTest, NotifyOneLightOnTop) {
  csci3081::LightSensor ls1;
  ls1.Reset_Reading();
  ls1.set_pose(csci3081::Pose(1, 1));
  ls1.Notify(light_close.get_pose());
  EXPECT_GT(ls1.get_reading(), 10000) << "\nFAIL NotifyOneLightOnTop\n";
}

// One light mid
TEST_F(LightSensorTest, NotifyOneLightMid) {
  light_sensor_a.Reset_Reading();
  light_sensor_a.Notify(light_mid.get_pose());
  EXPECT_LT(light_sensor_a.get_reading(), 500)
    << "\nFAIL NotifyOneLightMid\n";
}

// One light Far
TEST_F(LightSensorTest, NotifyOneLightFar) {
  light_sensor_a.Reset_Reading();
  light_sensor_a.Notify(light_far.get_pose());
  EXPECT_LT(light_sensor_a.get_reading(), 1)
    << "\nFAIL NotifyOneLightMid\n";
}

// Two lights close
TEST_F(LightSensorTest, NotifyTwoLightsClose) {
  csci3081::Light n_light;
  n_light.set_pose(csci3081::Pose(3, 3));

  light_sensor_a.Reset_Reading();

  light_sensor_a.Notify(n_light.get_pose());
  light_sensor_a.Notify(light_close.get_pose());

  EXPECT_GT(light_sensor_a.get_reading(), 2000)
    << "\nFAIL NotifyTwoLightsClose\n";
}

// One Light Close & One Light Mid
TEST_F(LightSensorTest, NotifyOneCloseOneMid) {
  light_sensor_a.Reset_Reading();

  light_sensor_a.Notify(light_close.get_pose());
  light_sensor_a.Notify(light_mid.get_pose());

  EXPECT_LT(light_sensor_a.get_reading(), 2000)
    << "\nFAIL NotifyOneCloseOneMid\n";
}

// One Light Close & One Light Far
TEST_F(LightSensorTest, NotifyOneCloseOneFar) {
  light_sensor_a.Reset_Reading();

  light_sensor_a.Notify(light_close.get_pose());
  light_sensor_a.Notify(light_far.get_pose());

  EXPECT_LT(light_sensor_a.get_reading(), 1800)
    << "\nFAIL NotifyOneCloseOneFar\n";
}

// One Light Mid & One Light Far
TEST_F(LightSensorTest, NotifyOneMidOneFar) {
  light_sensor_a.Reset_Reading();

  light_sensor_a.Notify(light_mid.get_pose());
  light_sensor_a.Notify(light_far.get_pose());

  EXPECT_LT(light_sensor_a.get_reading(), 400)
    << "\nFAIL NotifyOneMidOneFar\n";
}

// Two Lights Far
TEST_F(LightSensorTest, NotifyTwoLightsFar) {
  csci3081::Light n_light;
  n_light.set_pose(csci3081::Pose(1100, 900));

  light_sensor_a.Reset_Reading();

  light_sensor_a.Notify(n_light.get_pose());
  light_sensor_a.Notify(light_far.get_pose());

  EXPECT_LT(light_sensor_a.get_reading(), 200)
    << "\nFAIL NotifyTwoLightsFar\n";
}

// Two Lights Mid
TEST_F(LightSensorTest, NotifyTwoLightsMid) {
  csci3081::Light n_light;
  n_light.set_pose(csci3081::Pose(500, 400));

  light_sensor_a.Reset_Reading();

  light_sensor_a.Notify(n_light.get_pose());
  light_sensor_a.Notify(light_mid.get_pose());

  EXPECT_LT(light_sensor_a.get_reading(), 5)
    << "\nFAIL NotifyTwoLightsMid\n";
}

// Three Lights Close
TEST_F(LightSensorTest, NotifyThreeLightsClose) {
  csci3081::Light a_light, b_light;
  a_light.set_pose(csci3081::Pose(2, 2));
  b_light.set_pose(csci3081::Pose(3, 3));

  light_sensor_a.Reset_Reading();

  light_sensor_a.Notify(a_light.get_pose());
  light_sensor_a.Notify(b_light.get_pose());
  light_sensor_a.Notify(light_close.get_pose());

  EXPECT_GT(light_sensor_a.get_reading(), 1000)
    << "\nFAIL NotifyThreeLightsClose\n";
}

// Three Lights One Close One Mid One Far
TEST_F(LightSensorTest, NotifyThreeStandard) {
  light_sensor_a.Reset_Reading();

  light_sensor_a.Notify(light_close.get_pose());
  light_sensor_a.Notify(light_mid.get_pose());
  light_sensor_a.Notify(light_far.get_pose());

  EXPECT_LT(light_sensor_a.get_reading(), 2000)
    << "\nFAIL NotifyThreeStandard\n";
}

#endif
