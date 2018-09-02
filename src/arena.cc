/**
 * @file arena.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <algorithm>
#include <iostream>

#include "src/arena.h"
#include "src/arena_params.h"
#include "src/food.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Arena::Arena(const struct arena_params *const params)
  : x_dim_(params->x_dim),
    y_dim_(params->y_dim),
    factory_(new EntityFactory),
    entities_(),
    light_entities_(),
    robot_entities_(),
    food_entities_(),
    mobile_entities_(),
    game_status_(PAUSED) {
    AddRobot(params->n_fear_robots, kFear);
    AddRobot(params->n_aggressive_robots, kAggressive);
    AddRobot(params->n_explore_robots, kExplore);
    AddRobot(params->n_love_robots, kLove);
    AddFood(params->n_foods);
    AddLight(params->n_lights);
}

Arena::~Arena() {
  for (auto ent : entities_) {
    delete ent;
  } /* for(ent..) */
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Arena::AddRobot(int quantity, RobotBehaviorEnum behv) {
  for (int i = 0; i < quantity; i++) {
    robot_ = dynamic_cast<Robot *>(factory_->CreateEntity(kRobot));
    // set the robot's behavior type
    robot_->set_behavior_enum(behv);
    // ensure that the robot has the correct behavior member
    robot_->set_behavior_handler();
    // change the color of the robot depending on the type
    robot_->UpdateColor(behv);

    incrementRobotCount(behv);

    // ensure robot is pushed to all the vectors it belongs to
    entities_.push_back(robot_);
    robot_entities_.push_back(robot_);
    mobile_entities_.push_back(robot_);
  }
}

void Arena::AddLight(int quantity) {
  for (int i = 0; i < quantity; i++) {
    light_ = dynamic_cast<Light *>(factory_->CreateEntity(kLight));
    // ensure light is pushed to all the vectors it belongs to
    entities_.push_back(light_);
    light_entities_.push_back(light_);
    mobile_entities_.push_back(light_);
  }
}

void Arena::AddFood(int quantity) {
  for (int i = 0; i < quantity; i++) {
    food_ = dynamic_cast<Food *>(factory_->CreateEntity(kFood));
    // ensure food is pushed to all the vectors it belongs to
    entities_.push_back(food_);
    food_entities_.push_back(food_);
  }
}

void Arena::incrementRobotCount(RobotBehaviorEnum behv) {
  switch (behv) {
    case kFear: factory_->fear_robot_increment();
      break;
    case kAggressive: factory_->aggressive_robot_increment();
      break;
    case kExplore: factory_->explore_robot_increment();
      break;
    case kLove: factory_->love_robot_increment();
      break;
    default: {}
  }
}

void Arena::decrementRobotCount(RobotBehaviorEnum behv) {
  switch (behv) {
    case kFear: factory_->fear_robot_decrement();
      break;
    case kAggressive: factory_->aggressive_robot_decrement();
      break;
    case kExplore: factory_->explore_robot_decrement();
      break;
    case kLove: factory_->love_robot_decrement();
      break;
    default: {}
  }
}

void Arena::Reset() {
  for (auto ent : entities_) {
    ent->Reset();
  } /* for(ent..) */
} /* reset() */

// The primary driver of simulation movement. Called from the Controller
// but originated from the graphics viewer.
void Arena::AdvanceTime(double dt) {
  if (!(dt > 0)) {
    return;
  }
  for (size_t i = 0; i < 1; ++i) {
    UpdateEntitiesTimestep();
  } /* for(i..) */
} /* AdvanceTime() */

void Arena::UpdateEntitiesTimestep() {
  /*
   * First, update the position of all entities, according to their current
   * velocities.
   */
  for (auto ent : entities_) {
    ent->TimestepUpdate(1);
  }

  // push data for light entities to robot's light sensors
  for (auto &ent1 : robot_entities_) {
    for (auto &ent2 : light_entities_) {
      ent1->get_left_light_sensor()->Notify(ent2->get_pose());
      ent1->get_right_light_sensor()->Notify(ent2->get_pose());
    }  // end inner for
    for (auto &ent2 : food_entities_) {
      ent1->get_left_food_sensor()->Notify(ent2->get_pose());
      ent1->get_right_food_sensor()->Notify(ent2->get_pose());
    }  // end inner for
  }  // end outer for

  /*
   * Check for win/loss
   */
  for (auto &ent3 : robot_entities_) {
    bool flag = dynamic_cast<Robot *>(ent3)->get_dead();
    if (flag)
      game_status_ = LOST;
  }

  /* Determine if any mobile entity is colliding with wall.
  * Adjust the position accordingly so it doesn't overlap.
  */
  for (auto &ent1 : mobile_entities_) {
    EntityType wall = GetCollisionWall(ent1);
    if (kUndefined != wall) {
      AdjustWallOverlap(ent1, wall);
      EntityType etype = ent1->get_type();
      if (etype == kRobot) {
        Robot * rob = dynamic_cast<Robot *>(ent1);
        // flip robot 180 degree
        rob->RelativeChangeHeading(+180);
        // mark robot as collided
        rob->set_collision_cond(true);
        // start collision timer for reverse arc
        rob->set_collision_timer();
        rob->HandleCollision(wall);
      } else {
        Light *obs = dynamic_cast<Light *>(ent1);
        // mark light as collided
        obs->set_collision_cond(true);
        // start collision timer for reverse arc
        obs->set_collision_timer();
        obs->HandleCollision(wall);
      }  // end else
    }  // end outer if
    /* Determine if that mobile entity is colliding with any other entity.
    * Adjust the position accordingly so they don't overlap.
    */
    for (auto &ent2 : entities_) {
      if (ent2 == ent1) { continue; }
      if (IsColliding(ent1, ent2)) {
        EntityType etype_a = ent1->get_type();
        EntityType etype_b = ent2->get_type();
        AdjustEntityOverlap(ent1, ent2);
        if (etype_a == kRobot && etype_b == kRobot) {
          Robot * rob_a = dynamic_cast<Robot *>(ent1);
          // flip robot 180 degree
          rob_a->RelativeChangeHeading(+180);
          // mark robot as collided
          rob_a->set_collision_cond(true);
          // start collision timer for reverse arc
          rob_a->set_collision_timer();
          rob_a->HandleCollision(ent2->get_type(),
            ent2);

          Robot * rob_b = dynamic_cast<Robot *>(ent2);
          // flip robot 180 degree
          rob_b->RelativeChangeHeading(+180);
          // mark robot as collided
          rob_b->set_collision_cond(true);
          // start collision timer for reverse arc
          rob_b->set_collision_timer();
          rob_b->HandleCollision(ent1->get_type(),
            ent1);
        } else if (etype_a == kLight && etype_b == kLight) {
          Light *obs_a = dynamic_cast<Light *>(ent1);
          // flip light 180 degree
          obs_a->RelativeChangeHeading(+180);
          // mark light as collided
          obs_a->set_collision_cond(true);
          // start collision timer for reverse arc
          obs_a->set_collision_timer();
          obs_a->HandleCollision(ent2->get_type(), ent2);

          Light *obs_b = dynamic_cast<Light *>(ent2);
          // flip light 180 degree
          obs_b->RelativeChangeHeading(+180);
          // mark light as collided
          obs_b->set_collision_cond(true);
          // start collision timer for reverse arc
          obs_b->set_collision_timer();
          obs_b->HandleCollision(ent1->get_type(), ent1);
        }  // end else if
      }  // end outer if
    }  // end for
  }  // end outer for
}  // UpdateEntitiesTimestep()


// Determine if the entity is colliding with a wall.
// Always returns an entity type. If not collision, returns kUndefined.
EntityType Arena::GetCollisionWall(ArenaMobileEntity *const ent) {
  if (ent->get_pose().x + ent->get_radius() >= x_dim_) {
    return kRightWall;  // at x = x_dim_
  } else if (ent->get_pose().x - ent->get_radius() <= 0) {
    return kLeftWall;  // at x = 0
  } else if (ent->get_pose().y + ent->get_radius() >= y_dim_) {
    return kBottomWall;  // at y = y_dim
  } else if (ent->get_pose().y - ent->get_radius() <= 0) {
    return kTopWall;  // at y = 0
  } else {
    return kUndefined;
  }
} /* GetCollisionWall() */

/* The entity type indicates which wall the entity is colliding with.
* This determines which way to move the entity to set it slightly off the wall. */
void Arena::AdjustWallOverlap(ArenaMobileEntity *const ent, EntityType object) {
  Pose entity_pos = ent->get_pose();
  switch (object) {
  case (kRightWall):  // at x = x_dim_
    ent->set_position(x_dim_ - (ent->get_radius() + 5), entity_pos.y);
    break;
  case (kLeftWall):  // at x = 0
    ent->set_position(ent->get_radius() + 5, entity_pos.y);
    break;
  case (kTopWall):  // at y = 0
    ent->set_position(entity_pos.x, ent->get_radius() + 5);
    break;
  case (kBottomWall):  // at y = y_dim_
    ent->set_position(entity_pos.x, y_dim_ - (ent->get_radius() + 5));
    break;
  default:
  {}
  }
}

/* Calculates the distance between the center points to determine overlap */
bool Arena::IsColliding(
  ArenaMobileEntity * const mobile_e,
  ArenaEntity * const other_e) {
  double delta_x = other_e->get_pose().x - mobile_e->get_pose().x;
  double delta_y = other_e->get_pose().y - mobile_e->get_pose().y;
  double distance_between = sqrt(delta_x * delta_x + delta_y * delta_y);
  return
    (distance_between <= (mobile_e->get_radius() + other_e->get_radius()));
}

/* This is called when it is known that the two entities overlap.
* We determine by how much they overlap then move the mobile entity to
* the edge of the other
*/
void Arena::AdjustEntityOverlap(ArenaMobileEntity * const mobile_e,
                                ArenaEntity *const other_e) {
  EntityType etype_a = mobile_e->get_type();
  EntityType etype_b = other_e->get_type();

  // ensure that colliding entities are of the same type
  if (etype_a == etype_b)
      Collide(mobile_e, other_e);  // if so ensure they collide properly

  else if (etype_a == kRobot && etype_b == kFood)
    dynamic_cast<Robot *>(mobile_e)->ResetHunger();  // reset robot hunger
}

void Arena::Collide(ArenaMobileEntity * const mobile_e,
                                ArenaEntity *const other_e) {
  double delta_x = mobile_e->get_pose().x - other_e->get_pose().x;
  double delta_y = mobile_e->get_pose().y - other_e->get_pose().y;
  double distance_between = sqrt(delta_x * delta_x + delta_y * delta_y);
  double distance_to_move =
    mobile_e->get_radius() + other_e->get_radius() - distance_between + 3;
  double angle = atan2(delta_y, delta_x);
  mobile_e->set_position(
    mobile_e->get_pose().x + cos(angle)*distance_to_move,
    mobile_e->get_pose().y + sin(angle)*distance_to_move);
}

// Accept communication from the controller. Dispatching as appropriate.
void Arena::AcceptCommand(Communication com) {
  switch (com) {
  case (kReset): Reset();
    break;
  case (kPlay): set_game_status(PLAYING);
    break;
  case (kPause): set_game_status(PAUSED);
    break;
  case (kNone):
  default: break;
  }
} /* AcceptCommand */

void Arena::setLightReading(int num) {
  for (unsigned int i = 0; i < robot_entities_.size(); i++) {
    robot_entities_[i]->get_left_light_sensor()->set_numerator(num);
    robot_entities_[i]->get_right_light_sensor()->set_numerator(num);
  }
}

void Arena::ChangeNumLights(int num) {
  int num_lights = factory_->get_light_count();
  if (num > num_lights) {
    int diff = num - num_lights;
    AddLight(diff);
  } else if (num < num_lights) {
    int diff = num_lights - num;
    for (int i = 0; i < diff; i++)
      RemoveLight();
  } else {}
}

void Arena::RemoveLight() {
  Light *l_ptr = light_entities_[0];
  light_entities_.erase(light_entities_.begin());

  for (unsigned int i = 0; i < entities_.size(); i++)
    if (entities_[i] == l_ptr) {
      entities_.erase(entities_.begin() + i);
      break;
    }  // end if

  for (unsigned int i = 0; i < mobile_entities_.size(); i++)
    if (mobile_entities_[i] == l_ptr) {
      mobile_entities_.erase(mobile_entities_.begin() + i);
      break;
    }  // end if

  factory_->light_count_decrement();  // decrement the light

  delete(l_ptr);
}

void Arena::ChangeNumFood(int num) {
  int num_food = factory_->get_food_count();
  if (num > num_food) {
    FlipRobotHunger(true);
    int diff = num - num_food;
    AddFood(diff);
  } else if (num < num_food) {
    int diff = num_food - num;
    if (diff == num_food)
      FlipRobotHunger(false);
    for (int i = 0; i < diff; i++)
      RemoveFood();
  } else {}
}

void Arena::RemoveFood() {
  Food *f_ptr = food_entities_[0];
  food_entities_.erase(food_entities_.begin());

  for (unsigned int i = 0; i < entities_.size(); i++)
    if (entities_[i] == f_ptr) {
      entities_.erase(entities_.begin() + i);
      break;
    }  // end if

  factory_->food_count_decrement();  // decrement the light

  delete(f_ptr);
}

void Arena::FlipRobotHunger(bool flag) {
  if (flag == false) {
    for (unsigned int i = 0; i < robot_entities_.size(); i++) {
      robot_entities_[i]->set_food_flag(false);
      robot_entities_[i]->ResetHunger();
    }
  } else {
    for (unsigned int i = 0; i < robot_entities_.size(); i++) {
      robot_entities_[i]->set_food_flag(true);
      robot_entities_[i]->ResetHunger();
    }
  }
}

void Arena::ChangeNumRobot(int num, RobotBehaviorEnum behv) {
  int type_count;

  switch (behv) {
    case kFear: type_count = factory_->get_fear_robot_count();
      break;
    case kAggressive: type_count = factory_->get_aggressive_robot_count();
      break;
    case kLove: type_count = factory_->get_love_robot_count();
      break;
    case kExplore: type_count = factory_->get_explore_robot_count();
      break;
    default: type_count = 0;
  }

  if (num > type_count) {
    int diff = num - type_count;
    AddRobot(diff, behv);
  } else if (num < type_count) {
    int diff = type_count - num;
    for (int i = 0; i < diff; i++)
      RemoveRobot(behv);
  }
}

void Arena::RemoveRobot(RobotBehaviorEnum behv) {
  Robot *rob;

  bool flag = false;

  for (unsigned int i = 0; i < robot_entities_.size(); i++)
    if (robot_entities_[i]->get_behavior_enum() == behv) {
      rob = robot_entities_[i];
      robot_entities_.erase(robot_entities_.begin() + i);
      flag = true;
      break;
    }

  if (flag) {
    for (unsigned int j = 0; j < entities_.size(); j++)
      if (entities_[j] == rob) {
        entities_.erase(entities_.begin() + j);
        break;
      }  // end if

    for (unsigned int k = 0; k < mobile_entities_.size(); k++)
      if (mobile_entities_[k] == rob) {
        mobile_entities_.erase(mobile_entities_.begin() + k);
        break;
      }  // end if

    delete(rob->get_left_light_sensor());
    delete(rob->get_right_light_sensor());

    delete(rob->get_left_food_sensor());
    delete(rob->get_right_food_sensor());

    delete(rob->get_motion_handler());

    delete(rob);

    decrementRobotCount(behv);
  }
}

NAMESPACE_END(csci3081);
