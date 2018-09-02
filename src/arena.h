/**
 * @file arena.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ARENA_H_
#define SRC_ARENA_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <math.h>
#include <cmath>
#include <iostream>
#include <vector>

#include "src/common.h"
#include "src/food.h"
#include "src/light.h"
#include "src/entity_factory.h"
#include "src/robot.h"
#include "src/communication.h"
#include "src/robot_behavior.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
struct arena_params;

/**
 * @brief The main class for the simulation of a 2D world with many entities
 * running around.
 *
 * While GraphicsArenaViewer handles the graphics, Arena handles all the
 * data and all the entities (it is the model of MVC). It manages the
 * interaction among the entities in the Arena.
 *
 */

class Arena {
 public:
  /**
   * @brief Arena's constructor.
   *
   * @param params A arena_params passed down from main.cc for the
   * initialization of Arena and the entities therein.
   *
   * Initialize all private variables and entities.
   */
  explicit Arena(const struct arena_params *const params);

  /**
   * @brief Arena's destructor. `delete` all entities created.
   */
  ~Arena();

  /**
   * @brief Advance the simulation by the specified # of steps.
   *
   * @param[in] dt The # of steps to increment by. This is
   * practically unused because the arena state is advanced
   * incrementally at a fixed rate.
   *
   * If `dt == 0`, `return` immediately. Otherwise calls
   * Arena::UpdateEntitiesTimestep() once.
   */
  void AdvanceTime(double dt);

  /**
   * @brief adds the robot to the entities_ and mobile_entities_
   *
   * @param[in] quantity represents quantity of entities to add
   * @param[in] behv reflects the enum of behavior of the robot
   */
  void AddRobot(int quantity, RobotBehaviorEnum behv);

  /**
   * @brief adds the entities to the entities_
   *
   * @param[in] quantity represents the number of entities to add
   */
  void AddFood(int quantity);

  /**
   * @brief adds the lights to the entities_ 
   * and mobile_entities_
   *
   * @param[in] quantity represents the number of entities to add
   */
  void AddLight(int quantity);

  /**
   * @brief accepts commands from the controller and executes certain commands
   */
  void AcceptCommand(Communication com);

  /**
   * @brief Reset all entities in Arena.
   */
  void Reset();

  /**
   * @brief Get the Robot in Arena.
   *
   * @return A pointer to the Robot.
   */
  class Robot *robot() const { return robot_; }

  /**
   * @brief Get the Robot vector in Arena.
   *
   * @return A pointer to the Robot vector.
   */
  std::vector<class Robot *> Robot_Vector() const
      { return robot_entities_; }

  /**
   * @brief Under certain circumstance, the compiler requires that the
   * assignment operator is not defined. This `deletes` the default
   * assignment operator.
   */
  Arena &operator=(const Arena &other) = delete;

  /**
   * @brief Under certain circumstance, the compiler requires that the copy
   * constructor is not defined. This `deletes` the default copy constructor.
   */
  Arena(const Arena &other) = delete;

  /**
   * @brief Determine if two entities have collided in the Arena. Collision is
   * defined as the distance between two entities being less than the sum of
   * their radii.
   *
   * @param mobile_e This entity is definitely moving.
   * @param other_e This entity might be mobile or immobile.
   * @param[out] True if entities overlapping.
   *
   **/
  bool IsColliding(
    ArenaMobileEntity * const mobile_e, ArenaEntity * const other_e);

  /**
  * @brief Move the mobile entity to the edge of the other without overlap.
  * Without this, entities tend to get stuck inside one another.
  **/
  void AdjustEntityOverlap(ArenaMobileEntity * const mobile_e,
                           ArenaEntity *const other_e);

  /**
   * @brief Determine if a particular entity has gone out of the boundaries of
   * the simulation (i.e. has collided with any one of the walls).
   *
   * @param ent The entity to check.
   * @param [out] An entity type signifying wall (e.g. kRightWall). kUndefined
   * if no collision.
   *
   * The checked entity's position will be updated to a "back-off position" so
   * that it won't get stuck into a wall. The calculation of the "back-off
   * position" is technically not accurate, but good enough for our purpose.
   */
  EntityType GetCollisionWall(ArenaMobileEntity * const ent);

  /**
  * @brief Move the entity to the edge of the wall without overlap.
  * Without this, entities tend to get stuck in walls.
  **/
  void AdjustWallOverlap(ArenaMobileEntity * const ent, EntityType wall);


  /**
   * @brief Update all entities for a single timestep.
   *
   * First calls each entity's TimestepUpdate method to update their speed,
   * heading angle, and position. Then check for collisions between entities
   * or between an entity and a wall.
   */
  void UpdateEntitiesTimestep();

  /**
   * @brief Get the ArenaEntities vector in Arena.
   *
   * @return A pointer to the ArenaEntities vector.
   */
  std::vector<class ArenaEntity *> get_entities() const { return entities_; }

  /**
   * @brief Get the X dimension of the arena.
   *
   * @return the X dimesnion of the arena.
   */
  double get_x_dim() { return x_dim_; }

  /**
   * @brief Get the Y dimension of the arena.
   *
   * @return the Y dimesnion of the arena.
   */
  double get_y_dim() { return y_dim_; }

  /**
   * @brief Get the game status.
   *
   * @return the game status value.
   */
  int get_game_status() const { return game_status_; }

  /**
   * @brief Set the game status.
   *
   * @param status the game status to be changed to.
   */
  void set_game_status(int status) { game_status_ = status; }

  /**
   * @brief Handle the collision for certain objects correctly
   *
   * @param mobile_e one of the mobile entities that collided
   * @param other_e the other entity the object collided with
   */
  void Collide(ArenaMobileEntity * const mobile_e,
                           ArenaEntity *const other_e);

  /**
   * @brief Determines whether there are lights to add or remove
   *
   * @param num the number passed by the GUI to change lights to
   */
  void ChangeNumLights(int num);

  /**
   * @brief Removes one light from the arena, and destroys it
   */
  void RemoveLight();

  /**
   * @brief Changes the numerator of the light sensor equation to num
   *
   * @param num the new numerator value
   */
  void setLightReading(int num);

  /**
   * @brief increments the count of a specific robot with a behvaior
   *
   * @param[in] behv the behavior of the robot to increment the count
   */
  void incrementRobotCount(RobotBehaviorEnum behv);

  /**
   * @brief decrements the count of a specific robot with a behvaior
   *
   * @param[in] behv the behavior of the robot to decrement the count
   */
  void decrementRobotCount(RobotBehaviorEnum behv);

  /**
   * @brief Determines whether there are food to add or remove
   *
   * @param num the number passed by the GUI to change food to
   */
  void ChangeNumFood(int num);

  /**
   * @brief Removes one food from the arena, and destroys it
   */
  void RemoveFood();

  /**
   * @brief Changes the robot's food_flag_ to param
   *
   * @param[in] flag bool value to change robot's food_flag_ to
   */
  void FlipRobotHunger(bool flag);

  /**
   * @brief Determines whether there are robots to add or remove
   *
   * @param num the number passed by the GUI to change robots to
   */
  void ChangeNumRobot(int num, RobotBehaviorEnum behv);

  /**
   * @brief Removes one robot from the arena, and destroys it
   */
  void RemoveRobot(RobotBehaviorEnum behv);

 private:
  // Dimensions of graphics window inside which entities must operate
  double x_dim_;
  double y_dim_;

  // Used to create all entities within the arena
  EntityFactory *factory_;

  // Robot is special. It's also stored in the entity vectors.
  Robot *robot_{nullptr};

  // Light is special. It's also stored in the entity vectors.
  Light *light_{nullptr};

  Food *food_{nullptr};

  // All entities mobile and immobile.
  std::vector<class ArenaEntity *> entities_;

  // Light entities vector
  std::vector<class Light *> light_entities_;

  // Robot entities vector
  std::vector<class Robot *> robot_entities_;

  // Food entities vector
  std::vector<class Food *> food_entities_;

  // A subset of the entities -- only those that can move (only Robot for now).
  std::vector<class ArenaMobileEntity *> mobile_entities_;

  // win/lose/playing state
  int game_status_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_ARENA_H_
