/**
 * @file arena_entity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ARENA_ENTITY_H_
#define SRC_ARENA_ENTITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>

#include "src/common.h"
#include "src/entity_type.h"
#include "src/params.h"
#include "src/pose.h"
#include "src/rgb_color.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A base class from which all Arena entities inherit.
 *
 * All entities know how to:
 *
 * 1. Update themselves at each timestep (i.e. in accordance with current
 * velocity and position).
 *
 * 2. Reset themselves to a newly constructed state. So that the user can
 * click the reset button to restart the game. Alternatively, the game
 * will be reset if the robot has won/lost.
 *
 * Please note that here use the upper-left coordinate, which means that the
 * origin point (0.0,0.0) is at the upper left.
 *
 * All arena entities are circular.
 *
 */
class ArenaEntity {
 public:
  /**
  * @brief ArenaEntity constructor initialized with default values from params.h
  */
  ArenaEntity() : pose_(DEFAULT_POSE), color_(DEFAULT_COLOR) {}

  /**
   * @brief Default destructor -- as defined by compiler.
   */
  virtual ~ArenaEntity() = default;

  /**
   * @brief Perform whatever updates needed for a particular entity after 1
   * timestep (updating position, changing color, etc.).
   *
   * @param[in] dt is time elapsed since the last update. Unused.
   */
  virtual void TimestepUpdate(__unused unsigned int dt) {}

  /**
   * @brief Reset entity to a newly constructed state.
   */
  virtual void Reset() {}

  /**
   * @brief Get the name of the entity for visualization and for debugging.
   *
   * @return Name of the entity. Each entity type hard codes its name
   * (e.g. "Robot").
   */
  virtual std::string get_name() const = 0;

  /**
   * @brief Get the pose of the entity.
   *
   * @return the pose of the entity.
   */
  const Pose &get_pose() const { return pose_; }

   /**
   * @brief Setter for the pose of the entity
   *
   * @param[in] pose modifies the pose of the entity
   */  
  void set_pose(const Pose &pose) { pose_ = pose; }

  /**
   * @brief Setter method for position within entity pose variable.
   */
  void set_position(const double inx, const double iny) {
    pose_.x = inx;
    pose_.y = iny;
  }

  /**
   * @brief Setter method for heading within entity pose variable.
   */
  void set_heading(const double t) {pose_.theta = t;}

  /**
   * @brief Setter for heading within pose, but change is relative to current
   * value.
   *
   * @param[in] delta by which to modify current heading. Can be positive
   * or negative.
   */
  void RelativeChangeHeading(const double delta) {
    pose_.theta += delta;
  }

  /**
   * @brief Getter for the color of the entity
   *
   * @param[out] returns the color of the entity
   */
  const RgbColor &get_color() const { return color_; }

  /**
   * @brief setter for the color of the entity
   *
   * @param[in] color sets the color of the entity
   */
  void set_color(const RgbColor &color) { color_ = color; }

  /**
   * @brief Getter for the radius of the entity
   *
   * @param[out] returns the radius of the entity
   */
  double get_radius() const { return radius_; }

  /**
   * @brief Setter for the radius of the entity
   *
   * @param[in] radius sets the radius of the entity
   */
  void set_radius(double radius) { radius_ = radius; }

  /**
   * @brief Getter for the type of the entity
   *
   * @param[out] returns the type of the entity
   */
  EntityType get_type() const { return type_; }

  /**
   * @brief Setter for the type of the entity
   *
   * @param[in] et modifies the type of the entity
   */
  void set_type(EntityType et) { type_ = et; }

  /**
   * @brief Getter for the id of the entity
   *
   * @param[out] returns the id of the entity
   */
  int get_id() const { return id_; }

  /**
   * @brief Setter for the id of the entity
   *
   * @param[in] id modifies the id_ of the entity
   */
  void set_id(int id) { id_ = id; }

  /**
   * @brief Getter method for determining if entity can move or not.
   */
  bool is_mobile(void) { return is_mobile_; }

  /**
   * @brief Setter method for indicating if entity can move or not.
   */
  void set_mobility(bool value) { is_mobile_ = value; }

  /**
  * @brief An attempt to not overlap any of the newly constructed entities.
  */
  Pose SetPoseRandomlyAux() {
    // Dividing arena into 19x14 grid. Each grid square is 50x50
    return {static_cast<double>((30 + (random() % 19) * 50)),
            static_cast<double>((30 + (random() % 14) * 50))};
  }

 private:
  double radius_{DEFAULT_RADIUS};
  Pose pose_;
  RgbColor color_;
  EntityType type_{kEntity};
  int id_{ -1};
  bool is_mobile_{false};
};

NAMESPACE_END(csci3081);

#endif  // SRC_ARENA_ENTITY_H_
