/**
 * @file params.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_PARAMS_H_
#define SRC_PARAMS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"

/*******************************************************************************
 * Macros
 ******************************************************************************/
/*
 * @file. Constructors for classes should use reasonable default values as
 * defined here. An exception might be if the value is 0.
 */

// graphics
#define X_DIM 1200
#define Y_DIM 950
#define TEXT_BOX_WIDTH 50
#define GUI_MENU_WIDTH 180
#define GUI_MENU_GAP 10

// arena
#define N_FOOD 4
#define MAX_FOOD 5
#define N_LIGHTS 4
#define MAX_NUM_LIGHTS 7
#define ARENA_X_DIM X_DIM
#define ARENA_Y_DIM Y_DIM
#define PI 3.1459

// game status
#define WON 0
#define LOST 1
#define PLAYING 2
#define PAUSED 3

// entity
#define DEFAULT_POSE \
  { 200, 200, 0}
#define DEFAULT_COLOR \
  { 255, 255, 255 }
#define DEFAULT_RADIUS 20

// mobile entity
#define STARTING_VELOCITY 0.0
#define ARC_TIME 0.1

// robot
#define ROBOT_ANGLE_DELTA 1
#define ROBOT_SPEED_DELTA 1
#define ROBOT_COLLISION_DELTA 1
#define ROBOT_RADIUS 30
#define ROBOT_MIN_RADIUS 15
#define ROBOT_MAX_RADIUS 20
#define ROBOT_INIT_POS \
  { 500, 500 , 0}
#define ROBOT_COLOR \
  { 0, 0, 255 }
#define ROBOT_HUNGER 550.0
#define ROBOT_STARVE 2250.0
#define ROBOT_DEATH 2800.0

#define ROBOT_HEADING 270
#define ROBOT_INIT_SPEED 0
#define ROBOT_MAX_SPEED 10
#define ROBOT_MAX_ANGLE 360
#define ROBOT_FEAR 5
#define ROBOT_AGGRESSIVE 0
#define ROBOT_EXPLORE 5
#define ROBOT_LOVE 0
#define MAX_ROBOT 10

#define AGGRESSIVE_COLOR {216, 8, 8}
#define FEAR_COLOR {130, 162, 242}
#define EXPLORE_COLOR {255, 144, 0}
#define LOVE_COLOR {252, 121, 234}

// food
#define FOOD_RADIUS 20
#define FOOD_COLLISION_DELTA 1
#define FOOD_INIT_POS \
  { 400, 400 }
#define FOOD_COLOR \
  { 0, 255, 0 }

// light
#define OBSTACLE_POSITION \
  { 200, 200 }
#define OBSTACLE_RADIUS 30
#define OBSTACLE_MIN_RADIUS 10
#define OBSTACLE_MAX_RADIUS 50
#define OBSTACLE_COLOR \
  { 255, 255, 255 }

// sensor
#define MAX_SENS 20.0
#define MAX_NUMERATOR 1200

#endif  // SRC_PARAMS_H_
