/**
 * @file light_sensor_test.cc
 *
 * @copyright 2017 Osamah Anwar, All rights reserved. AF
 */

// Google Test Framework
#include <gtest/gtest.h>

// Project code from the ../src directory
#include "../src/light_sensor.h"
#include "../src/motion_handler_robot.h"
#include "../src/robot_behavior.h"
#include "../src/wheel_velocity.h"
#include "../src/fear_behavior.h"
#include "../src/love_behavior.h"
#include "../src/explore_behavior.h"
#include "../src/aggressive_behavior.h"
#include "../src/pose.h"
#include "../src/robot.h"

/*******************************************************************************
 * Test Cases
 ******************************************************************************/
#ifdef MOTION_HANDLER_TEST

class MotionHandlerTest : public ::testing::Test {
 public:
  MotionHandlerTest() {}

 protected:
  virtual void SetUp() {
    robot_fear->set_behavior_enum(csci3081::kFear);
    robot_fear->set_behavior_handler();

    robot_love->set_behavior_enum(csci3081::kLove);
    robot_love->set_behavior_handler();

    robot_explore->set_behavior_enum(csci3081::kExplore);
    robot_explore->set_behavior_handler();

    robot_aggressive->set_behavior_enum(csci3081::kAggressive);
    robot_aggressive->set_behavior_handler();

    mot_fear->CreateBehavior(csci3081::kFear);
    mot_love->CreateBehavior(csci3081::kLove);
    mot_explore->CreateBehavior(csci3081::kExplore);
    mot_aggressive->CreateBehavior(csci3081::kAggressive);
  }
  csci3081::Robot * robot_fear = new csci3081::Robot;
  csci3081::Robot * robot_love = new csci3081::Robot;
  csci3081::Robot * robot_explore = new csci3081::Robot;
  csci3081::Robot * robot_aggressive = new csci3081::Robot;

  csci3081::MotionHandlerRobot* mot_fear =
    robot_fear->get_motion_handler();

  csci3081::MotionHandlerRobot* mot_love =
    robot_love->get_motion_handler();

  csci3081::MotionHandlerRobot* mot_explore =
    robot_explore->get_motion_handler();

  csci3081::MotionHandlerRobot* mot_aggressive =
    robot_aggressive->get_motion_handler();


  double light_reading_left = 2,
    light_reading_right = 2,
    food_reading_left = 16,
    food_reading_right = 16;

  bool hungry = true,
    not_hungry = false,
    starving = true,
    not_starving = false;
};

// Test for Fear Type Construction
TEST_F(MotionHandlerTest, FearConstructionTest) {
  EXPECT_EQ(csci3081::kFear, mot_fear->get_behavior()->get_behavior_enum())
    << "\nFAIL FearConstructionTest: Behavior Type\n";
  EXPECT_EQ(10, mot_fear->get_max_speed())
    << "\nFAIL FearConstructionTest: Max Speed\n";
  EXPECT_EQ(360, mot_fear->get_max_angle())
    << "\nFAIL FearConstructionTest: Max Angle\n";
  EXPECT_EQ(1, mot_fear->get_speed_delta())
    << "\nFAIL FearConstructionTest: Speed Delta\n";
  EXPECT_EQ(1, mot_fear->get_angle_delta())
    << "\nFAIL FearConstructionTest: Angle Delta\n";
  EXPECT_EQ(0, mot_fear->get_velocity().right)
    << "\nFAIL FearConstructionTest: Wheel Velocity right\n";
  EXPECT_EQ(0, mot_fear->get_velocity().left)
    << "\nFAIL FearConstructionTest: Wheel Velocity left\n";
}

// Test for Love Type Construction
TEST_F(MotionHandlerTest, LoveConstructionTest) {
  EXPECT_EQ(csci3081::kLove, mot_love->get_behavior()->get_behavior_enum())
    << "\nFAIL LoveConstructionTest: Behavior Type\n";
  EXPECT_EQ(10, mot_love->get_max_speed())
    << "\nFAIL LoveConstructionTest: Max Speed\n";
  EXPECT_EQ(360, mot_love->get_max_angle())
    << "\nFAIL LoveConstructionTest: Max Angle\n";
  EXPECT_EQ(1, mot_love->get_speed_delta())
    << "\nFAIL LoveConstructionTest: Speed Delta\n";
  EXPECT_EQ(1, mot_love->get_angle_delta())
    << "\nFAIL LoveConstructionTest: Angle Delta\n";
  EXPECT_EQ(0, mot_love->get_velocity().right)
    << "\nFAIL LoveConstructionTest: Wheel Velocity right\n";
  EXPECT_EQ(0, mot_love->get_velocity().left)
    << "\nFAIL LoveConstructionTest: Wheel Velocity left\n";
}

// Test for Explore Type Construction
TEST_F(MotionHandlerTest, ExploreConstructionTest) {
  EXPECT_EQ(csci3081::kExplore,
    mot_explore->get_behavior()->get_behavior_enum())
    << "\nFAIL ExploreConstructionTest: Behavior Type\n";
  EXPECT_EQ(10, mot_explore->get_max_speed())
    << "\nFAIL ExploreConstructionTest: Max Speed\n";
  EXPECT_EQ(360, mot_explore->get_max_angle())
    << "\nFAIL ExploreConstructionTest: Max Angle\n";
  EXPECT_EQ(1, mot_explore->get_speed_delta())
    << "\nFAIL ExploreConstructionTest: Speed Delta\n";
  EXPECT_EQ(1, mot_explore->get_angle_delta())
    << "\nFAIL ExploreConstructionTest: Angle Delta\n";
  EXPECT_EQ(0, mot_explore->get_velocity().right)
    << "\nFAIL ExploreConstructionTest: Wheel Velocity right\n";
  EXPECT_EQ(0, mot_explore->get_velocity().left)
    << "\nFAIL ExploreConstructionTest: Wheel Velocity left\n";
}

// Test for Aggressive Type Construction
TEST_F(MotionHandlerTest, AggressiveConstructionTest) {
  EXPECT_EQ(csci3081::kAggressive,
    mot_aggressive->get_behavior()->get_behavior_enum())
    << "\nFAIL AggressiveConstructionTest: Behavior Type\n";
  EXPECT_EQ(10, mot_aggressive->get_max_speed())
    << "\nFAIL AggressiveConstructionTest: Max Speed\n";
  EXPECT_EQ(360, mot_aggressive->get_max_angle())
    << "\nFAIL AggressiveConstructionTest: Max Angle\n";
  EXPECT_EQ(1, mot_aggressive->get_speed_delta())
    << "\nFAIL AggressiveConstructionTest: Speed Delta\n";
  EXPECT_EQ(1, mot_aggressive->get_angle_delta())
    << "\nFAIL AggressiveConstructionTest: Angle Delta\n";
  EXPECT_EQ(0, mot_aggressive->get_velocity().right)
    << "\nFAIL AggressiveConstructionTest: Wheel Velocity right\n";
  EXPECT_EQ(0, mot_aggressive->get_velocity().left)
    << "\nFAIL AggressiveConstructionTest: Wheel Velocity left\n";
}

// Test for clamp_vel for both Max and Min cases
TEST_F(MotionHandlerTest, ClampVelocityTest) {
  csci3081::Robot * robot_temp = new csci3081::Robot;

  robot_fear->set_behavior_enum(csci3081::kLove);
  robot_fear->set_behavior_handler();

  csci3081::MotionHandlerRobot* mot_temp =
    robot_temp->get_motion_handler();

  csci3081::WheelVelocity vel_a(15, 120);

  mot_temp->set_velocity(vel_a);

  csci3081::WheelVelocity clamped_vel_a
    (mot_temp->clamp_vel(mot_temp->get_velocity().left),
     mot_temp->clamp_vel(mot_temp->get_velocity().right));

  EXPECT_EQ(10, clamped_vel_a.left)
    << "\nFAIL ClampVelocityTest: Max Wheel Velocity left\n";
  EXPECT_EQ(10, clamped_vel_a.right)
    << "\nFAIL ClampVelocityTest: Max Wheel Velocity right\n";

  csci3081::WheelVelocity vel_b(-2, -100);

  mot_temp->set_velocity(vel_b);

  csci3081::WheelVelocity clamped_vel_b
    (mot_temp->clamp_vel(mot_temp->get_velocity().left),
     mot_temp->clamp_vel(mot_temp->get_velocity().right));

  EXPECT_EQ(0, clamped_vel_b.left)
    << "\nFAIL ClampVelocityTest: Max Wheel Velocity left\n";
  EXPECT_EQ(0, clamped_vel_b.right)
    << "\nFAIL ClampVelocityTest: Max Wheel Velocity right\n";
}

/***************************************************************
Fear Behavior Tests
***************************************************************/

// Test for Fear Type Motion when Robot is starving
TEST_F(MotionHandlerTest, FearMotionStarvingTest) {
  csci3081::WheelVelocity vel(7, 7);
  mot_fear->set_velocity(vel);
  mot_fear->UpdateVelocity(light_reading_left, light_reading_right,
    food_reading_left, food_reading_right, hungry, starving);

  EXPECT_GT(vel.left, mot_fear->get_velocity().left)
    << "\nFAIL FearMotionStarvingTest: Wheel Velocity left\n";
  EXPECT_GT(vel.right, mot_fear->get_velocity().right)
    << "\nFAIL FearMotionStarvingTest: Wheel Velocity right\n";
}

// Test for Fear Type Motion when Robot is hungry
TEST_F(MotionHandlerTest, FearMotionHungryTest) {
  csci3081::WheelVelocity vel(3, 3);
  mot_fear->set_velocity(vel);
  mot_fear->UpdateVelocity(light_reading_left, light_reading_right,
    food_reading_left, food_reading_right, hungry, not_starving);

  EXPECT_GT(mot_fear->get_velocity().left, 3)
    << "\nFAIL FearMotionHungryTest: Wheel Velocity left\n";
  EXPECT_GT(mot_fear->get_velocity().right, 3)
    << "\nFAIL FearMotionHungryTest: Wheel Velocity right\n";
}

// Test for Fear Type Motion when Robot is not hungry
TEST_F(MotionHandlerTest, FearMotionNotHungryTest) {
  csci3081::WheelVelocity vel(3, 3);
  mot_fear->set_velocity(vel);
  mot_fear->UpdateVelocity(light_reading_left, light_reading_right,
    food_reading_left, food_reading_right, not_hungry, not_starving);

  EXPECT_LT(mot_fear->get_velocity().left, 3)
    << "\nFAIL FearMotionNotHungryTest: Wheel Velocity left\n";
  EXPECT_LT(mot_fear->get_velocity().right, 3)
    << "\nFAIL FearMotionNotHungryTest: Wheel Velocity right\n";
}

/***************************************************************
Love Behavior Tests
***************************************************************/

// Test for Love Type Motion when Robot is starving
TEST_F(MotionHandlerTest, LoveMotionStarvingTest) {
  csci3081::WheelVelocity vel(7, 7);
  mot_love->set_velocity(vel);
  mot_love->UpdateVelocity(light_reading_left, light_reading_right,
    food_reading_left, food_reading_right, hungry, starving);

  EXPECT_GT(vel.left, mot_love->get_velocity().left)
    << "\nFAIL LoveMotionStarvingTest: Wheel Velocity left\n";
  EXPECT_GT(vel.right, mot_love->get_velocity().right)
    << "\nFAIL LoveMotionStarvingTest: Wheel Velocity right\n";
}

// Test for Love Type Motion when Robot is hungry
TEST_F(MotionHandlerTest, LoveMotionHungryTest) {
  csci3081::WheelVelocity vel(3, 3);
  mot_love->set_velocity(vel);
  mot_love->UpdateVelocity(light_reading_left, light_reading_right,
    food_reading_left, food_reading_right, hungry, not_starving);

  EXPECT_GT(mot_love->get_velocity().left, 3)
    << "\nFAIL LoveMotionHungryTest: Wheel Velocity left\n";
  EXPECT_GT(mot_love->get_velocity().right, 3)
    << "\nFAIL LoveMotionHungryTest: Wheel Velocity right\n";
}

// Test for Love Type Motion when Robot is not hungry
TEST_F(MotionHandlerTest, LoveMotionNotHungryTest) {
  csci3081::WheelVelocity vel(3, 3);
  mot_love->set_velocity(vel);
  mot_love->UpdateVelocity(light_reading_left, light_reading_right,
    food_reading_left, food_reading_right, not_hungry, not_starving);

  EXPECT_GT(mot_love->get_velocity().left, 3)
    << "\nFAIL LoveMotionNotHungryTest: Wheel Velocity left\n";
  EXPECT_GT(mot_love->get_velocity().right, 3)
    << "\nFAIL LoveMotionNotHungryTest: Wheel Velocity right\n";
}

/***************************************************************
Explore Behavior Tests
***************************************************************/

// Test for Explore Type Motion when Robot is starving
TEST_F(MotionHandlerTest, ExploreMotionStarvingTest) {
  csci3081::WheelVelocity vel(7, 7);
  mot_explore->set_velocity(vel);
  mot_explore->UpdateVelocity(light_reading_left, light_reading_right,
    food_reading_left, food_reading_right, hungry, starving);

  EXPECT_GT(vel.left, mot_explore->get_velocity().left)
    << "\nFAIL ExploreMotionStarvingTest: Wheel Velocity left\n";
  EXPECT_GT(vel.right, mot_explore->get_velocity().right)
    << "\nFAIL ExploreMotionStarvingTest: Wheel Velocity right\n";
}

// Test for Explore Type Motion when Robot is hungry
TEST_F(MotionHandlerTest, ExploreMotionHungryTest) {
  csci3081::WheelVelocity vel(3, 3);
  mot_explore->set_velocity(vel);
  mot_explore->UpdateVelocity(light_reading_left, light_reading_right,
    food_reading_left, food_reading_right, hungry, not_starving);

  EXPECT_GT(mot_explore->get_velocity().left, 3)
    << "\nFAIL ExploreMotionHungryTest: Wheel Velocity left\n";
  EXPECT_GT(mot_explore->get_velocity().right, 3)
    << "\nFAIL ExploreMotionHungryTest: Wheel Velocity right\n";
}

// Test for Explore Type Motion when Robot is not hungry
TEST_F(MotionHandlerTest, ExploreMotionNotHungryTest) {
  csci3081::WheelVelocity vel(3, 3);
  mot_explore->set_velocity(vel);
  mot_explore->UpdateVelocity(light_reading_left, light_reading_right,
    food_reading_left, food_reading_right, not_hungry, not_starving);

  EXPECT_GT(mot_explore->get_velocity().left, 3)
    << "\nFAIL ExploreMotionNotHungryTest: Wheel Velocity left\n";
  EXPECT_GT(mot_explore->get_velocity().right, 3)
    << "\nFAIL ExploreMotionNotHungryTest: Wheel Velocity right\n";
}

/***************************************************************
Aggressive Behavior Tests
***************************************************************/

// Test for Aggressive Type Motion when Robot is starving
TEST_F(MotionHandlerTest, AggressiveMotionStarvingTest) {
  csci3081::WheelVelocity vel(7, 7);
  mot_aggressive->set_velocity(vel);
  mot_aggressive->UpdateVelocity(light_reading_left, light_reading_right,
    food_reading_left, food_reading_right, hungry, starving);

  EXPECT_GT(vel.left, mot_aggressive->get_velocity().left)
    << "\nFAIL AggressiveMotionStarvingTest: Wheel Velocity left\n";
  EXPECT_GT(vel.right, mot_aggressive->get_velocity().right)
    << "\nFAIL AggressiveMotionStarvingTest: Wheel Velocity right\n";
}

// Test for Aggressive Type Motion when Robot is hungry
TEST_F(MotionHandlerTest, AggressiveMotionHungryTest) {
  csci3081::WheelVelocity vel(3, 3);
  mot_aggressive->set_velocity(vel);
  mot_aggressive->UpdateVelocity(light_reading_left, light_reading_right,
    food_reading_left, food_reading_right, hungry, not_starving);

  EXPECT_GT(mot_aggressive->get_velocity().left, 3)
    << "\nFAIL AggressiveMotionHungryTest: Wheel Velocity left\n";
  EXPECT_GT(mot_aggressive->get_velocity().right, 3)
    << "\nFAIL AggressiveMotionHungryTest: Wheel Velocity right\n";
}

// Test for Explore Type Motion when Robot is not hungry
TEST_F(MotionHandlerTest, AggressiveMotionNotHungryTest) {
  csci3081::WheelVelocity vel(3, 3);
  mot_aggressive->set_velocity(vel);
  mot_aggressive->UpdateVelocity(light_reading_left, light_reading_right,
    food_reading_left, food_reading_right, not_hungry, not_starving);

  EXPECT_LT(mot_aggressive->get_velocity().left, 3)
    << "\nFAIL AggressiveMotionNotHungryTest: Wheel Velocity left\n";
  EXPECT_LT(mot_aggressive->get_velocity().right, 3)
    << "\nFAIL AggressiveMotionNotHungryTest: Wheel Velocity right\n";
}

#endif
