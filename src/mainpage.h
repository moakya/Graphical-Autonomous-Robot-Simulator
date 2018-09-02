/**
 * @copyright 2018 Osamah Anwar, All rights reserved.
 */

#ifndef SRC_MAINPAGE_H_
#define SRC_MAINPAGE_H_

/*! \mainpage Home
 *
 * \section robot_simulation Robot Simulation Iteration 3
 *
 * \subsection overview General Overview
 *
 * The purpose of the program is to simulate autonomous differential motion
 * of robots that have specific behavior to other objects in the
 * simulation. The simulation is primarily graphical. The graphics library
 * MinGfx is designed by Professor Daniel Keefe at the University of
 * Minnesota, which relies on OpenGL, and is built on top of NanoVG and
 * NanoGUI. More information for each can be found at the following links:

 * MinGfx: https://github.com/ivlab/MinGfx
 *
 * NanoVG: https://github.com/memononen/nanovg
 *
 * NanoGUI: https://github.com/wjakob/nanogui
 *
 * \section gen_user For the General User
 *
 * \subsection details_sim Details
 *
 * As stated above the main purpose of the program is to simulate
 * differential motion of robots in an arena. The simulation runs
 * indefinitely unless the failure conditions are met. The failure
 * condition being the robot starving in the arena (more information on
 * this later). The robots have a certain behavior towards other objects
 * in the arena, and react accordingly. The entities in the simulation
 * are autonomous, so their movements and operations are done completely
 * on their own without any influence from the user. There are three
 * different entities in the arena: the robots, the lights, and the food
 * objects. Each entity falls under one of two categorizes; mobile
 * entities or immobile entities. The robots and lights are mobile
 * entities, while the food objects are immobile entities. An entity can
 * only collided with an entity of the same type.
 *
 * \subsection gen_robot Robot
 *
 * The simulation revolves mainly around the robots in the arena.
 * The robots motion is based on a two wheel design, where the wheels are
 * affected by sensors attached to the robot, that react to other entities
 * in the arena. The robot has two kinds of sensors; light sensors and food
 * sensors, with each reacting to their specific counterparts in the arena.
 * The robot has a hunger status that the program uses to ensure the
 * simulation is running and active. The robot has multiple stages of
 * hunger, the first being not hungry where the robot ignores the food
 * objects and only reacts to lights. After thirty seconds the robot’s
 * status changes to hungry and it reacts to both light and food objects.
 * The final stage is activated a minute and thirty seconds after the
 * hungry condition; the starving condition where the robot ignores the
 * lights completely and only reacts to the food objects. The hunger
 * conditions are reset if the robot makes contact with food objects. If
 * two and a half minutes have elapsed since the robot became hungry the
 * simulation will end and the robot will be considered dead.  The robots
 * can have one of four behaviors towards other entities: fear behavior,
 * where the robot tries to move away from the entity, explore behavior,
 * tries to move around the arena not concerned with other entities, the
 * aggressive behavior where the robot rushes towards the entities, and the
 * love behavior where the robot will follow the entity around the arena.
 * All robots are aggressive towards food objects by default once a state
 * of hunger is starving. The robots are colored pink if they are fearful,
 * red if they are aggressive, pink if they are love, and  orange if they
 * are explore. All robots have two white circles to denote the sensors.
 *
 * \subsection gen_light Light
 *
 * The light objects move around the arena autonomously. Their
 * only purpose is to exist as stimuli for the robots in that arena. The
 * lights can collided with one another but pass through robots and food
 * objects. The lights are colored white. The lights are also based on the
 * two wheel differential motion model. The lights do not have any sensors
 * associated with them. 
 * \subsection Food
 * The food objects in the arena are immobile
 * entities, and stay in one place. The food objects are colored green,
 * they have no purpose other than acting as stimuli for the robots just
 * like the light objects.
 *
 * \subsection gen_gui Graphical User Interface
 *
 * The entire simulation takes place on a 2D
 * plane, that is what the user sees an implementation when the program is
 * running. The arena is surrounded in a white outline, which are used to
 * signify the walls of the arena. The arena also holds all the entities,
 * the robot’s are the blue round objects, with two smaller white circles
 * on top that are used to represent the sensors, the lights are colored
 * white, and finally the food objects are green. The GUI has multiple
 * elements for altering the arena condition on the fly. There are multiple
 * buttons and sliders that affect the entities and the arena in general.
 * There is a new game button that restarts the game with all entities
 * placed randomly in the arena, there is a play/pause button that pauses
 * and resumes the simulation once hit, and there is a food button that
 * enables/disables the food objects in the arena. If the food is disabled
 * the robots do not exhibit hunger, and once the food is enabled again the
 * robots hunger is turned on as well.   The sliders in the arena, are in
 * charge of controlling the count of the entities in the arena. There are
 * sliders for all four behaviors of the robots, the number of lights, the
 * number of food objects and the sensitivity of the light sensors of the
 * robots. The maximum number of entities for the robots are ten for each
 * type of robot, seven for the lights and 5 for the food objects. The
 * slider for the light sensor sensitivity has a maximum of 1200.
 *
 * \section dev_use For the Developer
 *
 * \subsection details_sim_dev Details
 *
 * The purpose of this program is to simulate differential motion of
 * robots in an arena. The program runs indefinitely unless the user
 * decides to close it. The simulation however runs indefinitely unless
 * certain failure conditions are met (will be discussed further later).
 * This program adheres to the Model View Controller model that is
 * explored below. The arena holds three different kinds of entities;
 * robots, lights and food entities. The lights and the food entities act
 * as stimuli for the robot, and are essential for the simulation, this
 * idea will be discussed further in the sections below. All the entities
 * in the arena are autonomous. The entities can be categorized into one
 * of two types depending on the state of motion; immobile entities and
 * mobile entities. The robots and lights are considered mobile entities,
 * while the food objects are immobile entities. Only entities of the
 * same type can collide with one another in the arena, meaning that
 * robots can only collide with robots, and pass through lights and food
 * entities; the same is true for lights. Food entities do not collide
 * with one another as they are immobile.
 *
 * \subsection dev_mvc Model View Controller (MVC)
 *
 * As mentioned above the program is designed to adhere to the
 * Model-View-Controller design pattern, as such there are three main classes
 * that are in charge of the managing the entire process; Arena,
 * Graphics Arena Viewer and Controller.
 *
 * \subsection dev_arena Arena
 *
 * Arena: The arena is the Model of the implementation, responsible for
 * managing all the entities and ensuring that the correct methods are
 * executed depending on the scenario. The arena contains the definitions
 * for all the entities in the simulation, as such there are methods that
 * deal with constructing and destroying the entities as well. Examples of
 * these would be:    void AddRobot(int quantity, RobotBehaviorEnum behv);
 * void AddLight(int quantity);   void AddFood(int quantity);
 *
 * The arena also contains one of the most important methods, one that
 * deals with the progress of the simulation; the AdvanceTime method that
 * ensures all the entities statuses are updated to reflect the changes.
 * The arena is also in charge of ensuring that when the simulation ends,
 * by keeping track of the status of the robots in the arena. The arena
 * could be called the heart of the entire simulation.
 *
 * \subsection dev_gui GraphicsArenaViewer
 *
 * The GraphicsArenaViewer is the View of the implementation, responsible
 * for creating a graphical representation of the arena and all it’s entities.
 * It also handles the input from the user. The class itself inherits from the
 * GraphicsApp class which is a part of the MinGfx library. Furthermore,
 * this inheritance from the MinGfx is the reason this class is able to act
 * as the View in the MVC model, this also allows different means of input
 * for the user, mainly entity sliders and buttons that affect the arena.
 * There are sliders for the number of active robots (there is a slider for
 * each type of robot), a slider for the total number of active lights in
 * the arena, the total number of food entities in the arena, and a slider for
 * the sensitivity of the robots’ light sensors. Besides the sliders,
 * there are buttons for different actions in the arena, one to start a new
 * game, one to pause/play the game, and one to enable/disable the food
 * entities in the arena. The sliders and the buttons rely on methods in
 * the controller, which in turn relies on the arena as the entities are all
 * inside the arena itself. These methods are called each time the sliders
 * and the buttons are changed. The following is an example illustrating the
 * relationship between the GraphicsArenaViewer, the Controller and the
 * Arena:
 * 
 * In GraphicsArenaViewer:
 * \verbatim
  slider->setFinalCallback(   [&](float value) {
   controller_->ChangeNumRobot((static_cast<int>(value*MAX_ROBOT)), kFear);
  });
  \endverbatim
 * In Controller:
 * \verbatim
  void ChangeNumRobot(int num, RobotBehaviorEnum behv) {
    arena_->ChangeNumRobot(num, behv); }
 \endverbatim
 * In Arena:
 * \verbatim
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
 \endverbatim
 * \subsection dev_controller Controller
 *
 * The Controller is the the last part of the MVC model. The controller as the
 * name suggests is the Controller, which acts as a in between for the
 * GraphicsArenaViewer and the Arena. The controller was also intially in
 * charge of ensuring user keyboard input was processed correctly in
 * Iteration 1 of the program.
 *
 * \subsection dev_entites Entities
 *
 * There are three different kinds of entities in the arena,
 * the robots, the lights and the food objects. The entities fall into one
 * of two categories, mobile entities and immobile entities. The robots and
 * the lights are mobile entities, while the food entities are immobile.
 * Both mobile and immobile entities inherit from a base class;
 * ArenaEntity. The ArenaEntity class contains the radius that the entity
 * will have, the position of the entity, the color, its type (either
 * robot, food, or light), it’s id, and a bool value to determine whether
 * the entity is mobile or not. ArenaImmobileEntity does not add onto the
 * implementation of ArenaEntity at all, and primarily relies on the
 * methods and the members from ArenaEntity. Where as the ArenaMobileEntity
 * class, adds on by implementing a speed member, and a SensorTouch member
 * to handle collisions. As robots, and lights are both mobile entities,
 * they take advantage of this class. The entities are discussed in further
 * detail down below.
 *
 * \subsection dev_food Food Entities
 *
 * As stated above, the food class inherits from ArenaImmobileEntity, thus it
 * does not move at all in the arena. The food entities are placed randomly at
 * the beginning of each new game. The food entities are circular shaped, and
 * are colored green. The food entities mainly exist to act as stimuli for the
 * robot, this is primarily seen when the robot is in the starving
 * condition, however, it is still somewhat apparent when the robot
 * is hungry and reacting to lights at the same time.
 *
 * \subsection dev_lights Lights
 *
 * Lights are one of the two mobile entities in the arena.
 * Lights, just like the food entities act as stimuli for the robots in the
 * arena. The lights are colored white and at the beginning of each
 * simulation the lights are placed randomly, and sized randomly. The
 * lights primarily rely on the two wheel model, where the direction of the
 * movement is controlled by altering the velocity of one of the wheels.
 * Although, the graphical representation of the simulation is two-
 * dimensional, the lights are assumed to be one level higher than the
 * other entities in the arena, and as such pass through all other entities
 * and only collide with other lights. The lights use an implementation of
 * reverse arc to back up after a collision.
 *
 * \subsection dev_robot Robots
 *
 * The robots are the focus of the entire simulation. The robots
 * are also considered as mobile entities and rely on the same two wheel
 * model as the light entities in the arena, and have a similar
 * implementation for reverse arc to ensure that the entities do not
 * collide again instantly. The robots and the food entities are considered
 * to be on the same level in the arena, below the lights and as such do
 * not collide with lights, and only collide with other robots.
 *
 * As stated above, the robots in the arena have two different stimuli in the
 * arena; the lights and the food entities. The primary means of interacting to
 * the stimuli are sensors, each robot has two kinds of sensors; food
 * sensors and light sensors. Each robot has two of each type of sensor,
 * placed at an offset angle that could be altered within the robot
 * constructor. These sensors rely on the position of their respective
 * entities and then calculate the distance between the entities and then
 * using the information calculate a reading value which is used to alter
 * the velocity of the robot depending on the behavior.
 *
 * All the robots have hunger attributes, these are managed by boolean flags
 * and timers of type double. The timers are initialized at the time of
 * the robot’s instantiation. There are three stages of hunger for a robot;
 * not hungry, hungry and starving. The robot starts off as not hungry, then
 * after around thirty seconds becomes hungry and starts looking for food while
 * still having it’s velocity impacted by the light sensor readings,
 * however at the last stage of hunger, i.e. starving which occurs at
 * around two minutes of the not being hungry, the robot completely
 * disregards the light sensor readings and acts aggressively towards food
 * entities. If the robot gets within five units of a food entity, the
 * hunger flags and timers are reset and the robot goes back to being not
 * hungry. Currently the only way to end the simulation is if one of the
 * robots in the arena starves (this condition is constantly checked by the
 * arena during every timestep update).
 *
 * The robots in the simulation have different colors to denote what behavior
 * type they have; red denotes aggressive behavior, pink is love behavior,
 * orange is explore behavior and blue is fear behavior. All robots have
 * rounded protrusions on them that are colored white, these denote the light
 * and food sensors.
 *
 * The robot’s behavior is a part of the MotionHandlerRobot member of the robot
 * class. There are four different types of behaviors; fear, love, explore
 * and aggressive. These behaviors are primarily geared towards light
 * entities in the arena. They are only active when the robot is either
 * hungry or not hungry, if the robot is starving these behaviors are
 * completely disregarded.
 *
 * These robots are based on Braitenberg vehicles, which is a concept conceived
 * by the Italian-Austrian cyberneticist Valentino Braitenberg. A Braitenberg
 * vehicle is basically an agent that can autonomously move around based on its
 * sensor inputs. It has primitive sensors (that measure some stimulus
 * at a point) that are connected wheels of the vehicle. Depending on how
 * sensors and wheels are connected, the vehicle exhibits different behaviors.
 * The connections for the sensors are either direct or crossed connections.
 * Direct means that the left sensor is connected to the left wheel and
 * vice versa for the right sensor. However, crossed connections refer to
 * when the left sensor is connected to the right wheel and vice versa for
 * the right sensor. Other than direct and crossed, the connections can
 * either be positive or negative, this affects the equations to calculate the
 * movement for each behavior.
 *
 * The fear behavior is direct positive connection for which the equation
 * to calculate velocity is:  (k * left_light_reading),
 * (k * right_light_reading)), for the left and right wheels respectively,
 * where k is an arbitrary constant. This behavior upon sensing a light
 * close to the robot, steers the robot away from the light.
 *
 * The aggressive behavior is crossed positive connection for
 * which the equation to calculate velocity is: (k * right_light_reading),
 * (k * left_light_reading)), for the left and right wheels respectively,
 * where k is an arbitrary constant. This behavior upon sensing a light
 * close to the robot, steers the robot towards the light, trying to ram
 * the light.
 *
 * The love behavior is direct negative connection for which the
 * equation to calculate velocity is: MAX_SENS - (k * left_light_reading),
 * MAX_SENS - (k * right_light_reading)), for the left and right wheels
 * respectively, where k is an arbitrary constant, and MAX_SENS is the maximum
 * sensitivity the light sensor can achieve. This behavior upon sensing a
 * light close to the robot, steers the robot towards the light, then chasing
 * the light around the arena, unless interrupted by another light in which
 * case it changes the light it chases.
 *
 * The explore behavior is crossed negative connection for which the equation
 * to calculate velocity is: MAX_SENS - (k * right_light_reading),
 * MAX_SENS - (k * left_light_reading), for the left and right wheels
 * respectively, where k is an arbitrary constant, and MAX_SENS is the maximum
 * sensitivity the light sensor can achieve. This behavior upon sensing a
 * light close to the robot, steers the robot away from the light, but not
 * as fast as the fear behavior. A few of the important method prototypes for
 * the robot class are listed below, with a short description of their
 * functionality.
 *
 * void TimestepUpdate(unsigned int dt) override;
 * A method that is called during every arena time step update, and ensures
 * that the robot’s position is up-to-date, it also ensures the robot hunger
 * flags and timers are up-to-date, and it also calls on the motion
 * handler to update the velocity.
 *
 * void UpdateHunger();
 * The method that checks whether the timers for the hunger have expired
 * and changes the boolean flags accordingly.
 *
 * \subsection dev_other_notes Other Notes
 *
 * There are multiple methods defined in Arena that are required to
 * instantiate new entities in the program. An example would be the method
 * AddRobot which instantiates a specific number of robots depending on the
 * int quantity passed in as the parameter, the function also requires a
 * RobotBehaviorEnum, so that the robot’s behavior can also be set.
 *
 * If the developer would like to create new entity sensors, for
 * example a robot sensor, the new class could have the sensor class as a
 * parent. The sensor class has different members that would be critical
 * for the new sensor to function and serve as a solid foundation to build
 * upon. These members include a pointer to the Robot itself, the color of
 * the sensor, its position and the angle it is placed at.
 *
 * Also, the ArenaEntity class acts as an interface class if the developer
 * wishes to create a new type of entity, this could be something like an
 * entity that teleports around the arena. The ArenaMobileEntity class could
 * be used for this, but it would not be proper, a new class would be the ideal
 * solution to this problem.
 */

#endif  // SRC_MAINPAGE_H_
