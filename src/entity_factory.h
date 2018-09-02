/**
 * @file entity_factory.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ENTITY_FACTORY_H_
#define SRC_ENTITY_FACTORY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>

#include "src/food.h"
#include "src/common.h"
#include "src/entity_type.h"
#include "src/light.h"
#include "src/params.h"
#include "src/pose.h"
#include "src/rgb_color.h"
#include "src/robot.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A factory for the instantiation of all types of arena entities.
 *
 * The factory keeps track of the number of entities of each type and overall.
 * It assigns ID's to the entity when it creates it.
 * The factory randomly places entities, and in doing so, attempts to not
 * have them overlap.
 */
class EntityFactory {
 public:
  /**
   * @brief EntityFactory constructor.
   *
   */
  EntityFactory();

  /**
   * @brief Default destructor.
   */
  virtual ~EntityFactory() = default;

  /**
  * @brief CreateEntity is primary purpose of this class.
  *
  * @param[in] etype The type to make.
  * @param[out] new dynamically created entity.
  *
  * Currently, the Arena gets the entity and places it in the appropriate data
  * structure. It might be useful to instead have the factory place on the
  * appropriate data structure so that the call to Arena is the same regardless
  * of the entity type.
  */
  ArenaEntity* CreateEntity(EntityType etype);

  /**
  * @brief Public - An attempt to not overlap any of the newly constructed entities.
  */
  Pose SetPoseRandomlyAux();

  /**
  * @brief return fear robot count
  */
  int get_fear_robot_count() { return robot_fear_count_; }

  /**
  * @brief decrement fear robot count
  */
  void fear_robot_decrement() { robot_fear_count_--; }

  /**
  * @brief increment fear robot count
  */
  void fear_robot_increment() { robot_fear_count_++; }


  /**
  * @brief return explore robot count
  */
  int get_explore_robot_count() { return robot_explore_count_; }

  /**
  * @brief decrement explore robot count
  */
  void explore_robot_decrement() { robot_explore_count_--; }

  /**
  * @brief increment explore robot count
  */
  void explore_robot_increment() { robot_explore_count_++; }


  /**
  * @brief return love robot count
  */
  int get_love_robot_count() { return robot_love_count_; }

  /**
  * @brief decrement love robot count
  */
  void love_robot_decrement() { robot_love_count_--; }

  /**
  * @brief increment love robot count
  */
  void love_robot_increment() { robot_love_count_++; }


  /**
  * @brief return aggressive robot count
  */
  int get_aggressive_robot_count() { return robot_aggressive_count_; }

  /**
  * @brief decrement aggressive robot count
  */
  void aggressive_robot_decrement() { robot_aggressive_count_--; }

  /**
  * @brief increment aggressive robot count
  */
  void aggressive_robot_increment() { robot_aggressive_count_++; }


  /**
  * @brief return light count
  */
  int get_light_count() { return light_count_; }

  /**
  * @brief decrement light count
  */
  void light_count_decrement() { light_count_--; }


  /**
  * @brief return food count
  */
  int get_food_count() { return food_count_; }

  /**
  * @brief decrement food count
  */
  void food_count_decrement() { food_count_--; }

 private:
  /**
  * @brief CreateRobot called from within CreateEntity.
  */
  Robot* CreateRobot();

  /**
  * @brief CreateLight called from within CreateEntity.
  */
  Light* CreateLight();

  /**
  * @brief CreateFood called from within CreateEntity.
  */
  Food* CreateFood();

  /**
  * @brief An attempt to not overlap any of the newly constructed entities.
  */
  Pose SetPoseRandomly();

  /* Factory tracks the number of created entities.*/
  int entity_count_{0};
  int light_count_{0};
  int food_count_{0};
  int robot_fear_count_{0};
  int robot_explore_count_{0};
  int robot_love_count_{0};
  int robot_aggressive_count_{0};
};

NAMESPACE_END(csci3081);

#endif  // SRC_ENTITY_FACTORY_H_
