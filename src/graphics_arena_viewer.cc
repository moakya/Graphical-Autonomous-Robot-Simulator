/**
 * @file graphics_arena_viewer.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <iostream>

#include "src/graphics_arena_viewer.h"
#include "src/arena_params.h"
#include "src/rgb_color.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
GraphicsArenaViewer::GraphicsArenaViewer(
  const struct arena_params *const params,
  Arena * arena, Controller * controller) :
  GraphicsApp(
    params->x_dim + GUI_MENU_WIDTH + GUI_MENU_GAP * 2,
    params->y_dim,
    "Robot Simulation"),
  controller_(controller),
  arena_(arena) {
  auto *gui = new nanogui::FormHelper(screen());
  nanogui::ref<nanogui::Window> window =
    gui->addWindow(
      Eigen::Vector2i(10 + GUI_MENU_GAP, 10),
      "Menu");

  window->setLayout(new nanogui::GroupLayout());

  gui->addGroup("Simulation Control");
  playing_button_ =
    gui->addButton(
      "Play",
      std::bind(&GraphicsArenaViewer::OnPlayingBtnPressed, this));
  playing_button_->setFixedWidth(100);

  reset_button_ =
    gui->addButton(
      "New Game",
      std::bind(&GraphicsArenaViewer::OnResetBtnPressed, this));
  reset_button_->setFixedWidth(100);

  gui->addGroup("Arena Configuration");

  /********************ROBOT SLIDERS***************************/
  // Creating a panel impacts the layout. Widgets, sliders, buttons can be
  // assigned to either the window or the panel.
  nanogui::Widget *panel = new nanogui::Widget(window);


  new nanogui::Label(panel, "# of Fear Robots", "sans-bold");
  nanogui::Slider *slider = new nanogui::Slider(panel);
  // The starting value (range is from 0 to 1)
  // Note that below the displayed value is 10* slider value.
  slider->setValue(static_cast<float>(ROBOT_FEAR)/MAX_ROBOT);
  slider->setFixedWidth(100);

  // Display the corresponding value of the slider in this textbox
  nanogui::TextBox *textBox = new nanogui::TextBox(panel);
  textBox->setFixedSize(nanogui::Vector2i(60, 25));
  textBox->setFontSize(20);
  textBox->setValue(std::to_string(static_cast<int>(ROBOT_FEAR)));

  // This is the lambda function called while the user is moving the slider
  slider->setCallback(
    [textBox](float value) {
      textBox->setValue(std::to_string(static_cast<int>(value*MAX_ROBOT)));
    });

  slider->setFinalCallback(
    [&](float value) {
      controller_->ChangeNumRobot((static_cast<int>(value*MAX_ROBOT)), kFear);
    });

  new nanogui::Label(panel, "# of Explore Robots", "sans-bold");
  nanogui::Slider *slider2 = new nanogui::Slider(panel);
  // The starting value (range is from 0 to 1)
  // Note that below the displayed value is 10* slider value.
  slider2->setValue(static_cast<float>(ROBOT_EXPLORE)/MAX_ROBOT);
  slider2->setFixedWidth(100);

  // Display the corresponding value of the slider in this textbox
  nanogui::TextBox *textBox2 = new nanogui::TextBox(panel);
  textBox2->setFixedSize(nanogui::Vector2i(60, 25));
  textBox2->setFontSize(20);
  textBox2->setValue(std::to_string(static_cast<int>(ROBOT_EXPLORE)));

  // This is the lambda function called while the user is moving the slider
  slider2->setCallback(
    [textBox2](float value) {
      textBox2->setValue(std::to_string(static_cast<int>(value*MAX_ROBOT)));
    });

  slider2->setFinalCallback(
    [&](float value) {
      controller_->ChangeNumRobot((static_cast<int>(value*MAX_ROBOT)),
        kExplore);
    });

  new nanogui::Label(panel, "# of Aggressive Robots", "sans-bold");
  nanogui::Slider *slider3 = new nanogui::Slider(panel);
  // The starting value (range is from 0 to 1)
  // Note that below the displayed value is 10* slider value.
  slider3->setValue(static_cast<float>(ROBOT_AGGRESSIVE)/MAX_ROBOT);
  slider3->setFixedWidth(100);

  // Display the corresponding value of the slider in this textbox
  nanogui::TextBox *textBox3 = new nanogui::TextBox(panel);
  textBox3->setFixedSize(nanogui::Vector2i(60, 25));
  textBox3->setFontSize(20);
  textBox3->setValue(std::to_string(static_cast<int>(ROBOT_AGGRESSIVE)));

  // This is the lambda function called while the user is moving the slider
  slider3->setCallback(
    [textBox3](float value) {
      textBox3->setValue(std::to_string(static_cast<int>(value*MAX_ROBOT)));
    });

  slider3->setFinalCallback(
    [&](float value) {
      controller_->ChangeNumRobot((static_cast<int>(value*MAX_ROBOT)),
        kAggressive);
    });

  new nanogui::Label(panel, "# of Love Robots", "sans-bold");
  nanogui::Slider *slider4 = new nanogui::Slider(panel);

  slider4->setValue(static_cast<float>(ROBOT_LOVE)/MAX_ROBOT);
  slider4->setFixedWidth(100);

  // Display the corresponding value of the slider in this textbox
  nanogui::TextBox *textBox4 = new nanogui::TextBox(panel);
  textBox4->setFixedSize(nanogui::Vector2i(60, 25));
  textBox4->setFontSize(20);
  textBox4->setValue(std::to_string(static_cast<int>(ROBOT_LOVE)));

  // This is the lambda function called while the user is moving the slider
  slider4->setCallback(
    [textBox4](float value) {
      textBox4->setValue(std::to_string(static_cast<int>(value*MAX_ROBOT)));
    });

  slider4->setFinalCallback(
    [&](float value) {
      controller_->ChangeNumRobot((static_cast<int>(value*MAX_ROBOT)), kLove);
    });

  // LIGHTS SLIDER
  new nanogui::Label(panel, "# of Lights", "sans-bold");
  nanogui::Slider *slider5 = new nanogui::Slider(panel);
  slider5->setValue(static_cast<float>(N_LIGHTS)/MAX_NUM_LIGHTS);
  slider5->setFixedWidth(100);

  nanogui::TextBox *textBox5 = new nanogui::TextBox(panel);
  textBox5->setFixedSize(nanogui::Vector2i(60, 25));
  textBox5->setFontSize(20);
  textBox5->setValue(std::to_string(static_cast<int>(N_LIGHTS)));

  slider5->setCallback(
    [textBox5](float value) {
      textBox5->setValue(std::to_string(
        static_cast<int>(value*MAX_NUM_LIGHTS)));
    });

  slider5->setFinalCallback(
    [&](float value) {
      controller_->ChangeNumLights(static_cast<int>(value*MAX_NUM_LIGHTS));
    });

  // Lays out all the components with "15" units of inbetween spacing
  panel->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Vertical,
    nanogui::Alignment::Middle, 0, 15));

  /***********************FOOD CHANGES************************/
  new nanogui::Label(panel, "# of Food", "sans-bold");
  nanogui::Slider *slider6 = new nanogui::Slider(panel);
  slider6->setValue(static_cast<float>(N_FOOD)/MAX_FOOD);
  slider6->setFixedWidth(100);

  nanogui::TextBox *textBox6 = new nanogui::TextBox(panel);
  textBox6->setFixedSize(nanogui::Vector2i(60, 25));
  textBox6->setFontSize(20);
  textBox6->setValue(std::to_string(static_cast<int>(N_FOOD)));

  slider6->setCallback(
    [textBox6](float value) {
      textBox6->setValue(std::to_string(static_cast<int>(value*MAX_FOOD)));
    });

  slider6->setFinalCallback(
    [&](float value) {
      if (food_stat_)
        controller_->ChangeNumFood(static_cast<int>(value*MAX_FOOD));
    });

  // Lays out all the components with "15" units of inbetween spacing
  panel->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Vertical,
    nanogui::Alignment::Middle, 0, 15));

  food_button_ =
    gui->addButton(
      "Food OFF",
      std::bind(&GraphicsArenaViewer::OnFoodTogglePressed, this));
  food_button_->setFixedWidth(100);

  new nanogui::Label(panel, "Numerator value", "sans-bold");
  nanogui::Slider *slider7 = new nanogui::Slider(panel);
  slider7->setValue(static_cast<float>(MAX_NUMERATOR)/MAX_NUMERATOR);
  slider7->setFixedWidth(100);

  nanogui::TextBox *textBox7 = new nanogui::TextBox(panel);
  textBox7->setFixedSize(nanogui::Vector2i(60, 25));
  textBox7->setFontSize(20);
  textBox7->setValue(std::to_string(static_cast<int>(MAX_NUMERATOR)));

  slider7->setCallback(
    [textBox7](float value) {
      textBox7->setValue(std::to_string(
        static_cast<int>(value*MAX_NUMERATOR)));
    });

  slider7->setFinalCallback(
    [&](float value) {
      controller_->setSensorReadings(static_cast<int>(value*MAX_NUMERATOR));
    });

  screen()->performLayout();
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

// This is the primary driver for state change in the arena.
// It will be called at each iteration of nanogui::mainloop()
void GraphicsArenaViewer::UpdateSimulation(double dt) {
  if (arena_->get_game_status() == PLAYING)
    controller_->AdvanceTime(dt);
}

/*******************************************************************************
 * Handlers for User Keyboard and Mouse Events
 ******************************************************************************/
/** OnPlayingBtnPressed is called when the user presses down on the
  * playing button in the viewer.
  */
void GraphicsArenaViewer::OnPlayingBtnPressed() {
  if (arena_->get_game_status() == PLAYING) {
    controller_->AcceptCommunication(kPause);
    playing_button_->setCaption("Play");
  } else {
    controller_->AcceptCommunication(kPlay);
    playing_button_->setCaption("Pause");
  }
}

/** OnResetBtnPressed is called when the user presses down on the
  * New Game button in the viewer.
  */
void GraphicsArenaViewer::OnResetBtnPressed() {
  playing_button_->setCaption("Play");
  controller_->AcceptCommunication(kNewGame);
  arena_->set_game_status(PAUSED);
}

void GraphicsArenaViewer::OnFoodTogglePressed() {
  // disable food
  if (food_stat_ == true) {
    food_stat_ = false;
    controller_->ChangeNumFood(0);
    controller_->FlipRobotHunger(false);
    food_button_->setCaption("Food ON");
  } else {  // turn on food, and set to default from params
    food_stat_ = true;
    controller_->ChangeNumFood(N_FOOD);
    controller_->FlipRobotHunger(true);
    food_button_->setCaption("Food OFF");
  }
}

/** OnSpecialKeyDown is called when the user presses down on one of the
  * special keys (e.g. the arrow keys).
  */
void GraphicsArenaViewer::OnSpecialKeyDown(int key,
    __unused int scancode, __unused int modifiers) {
  Communication key_value = kNone;
  switch (key) {
  case GLFW_KEY_UP: key_value = kKeyUp;
    break;
  case GLFW_KEY_DOWN: key_value = kKeyDown;
    break;
  case GLFW_KEY_LEFT: key_value = kKeyLeft;
    break;
  case GLFW_KEY_RIGHT: key_value = kKeyRight;
    break;
  default: {}
  }
  controller_->AcceptCommunication(key_value);
}

/*******************************************************************************
 * Drawing of Entities in Arena
 ******************************************************************************/
void GraphicsArenaViewer::DrawRobot(NVGcontext *ctx,
                  const std::vector<class Robot *> robot_vec) {
  for (unsigned int i = 0; i < robot_vec.size(); i++) {
    // translate and rotate all graphics calls that follow so that they are
    // centered, at the position and heading of this robot
    nvgSave(ctx);
    nvgTranslate(ctx,
                 static_cast<float>(robot_vec[i]->get_pose().x),
                 static_cast<float>(robot_vec[i]->get_pose().y));
    nvgRotate(ctx,
              static_cast<float>(robot_vec[i]->get_pose().theta *
                M_PI / 180.0));

    // robot's circle
    nvgBeginPath(ctx);
    nvgCircle(ctx, 0.0, 0.0, static_cast<float>(robot_vec[i]->get_radius()));
    nvgFillColor(ctx,
                 nvgRGBA(robot_vec[i]->get_color().r,
                  robot_vec[i]->get_color().g,
                  robot_vec[i]->get_color().b, 255));
    nvgFill(ctx);
    nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
    nvgStroke(ctx);

    // robot id text label
    nvgFontSize(ctx, 20.0f);
    nvgSave(ctx);
    nvgRotate(ctx, static_cast<float>(M_PI / 2.0));
    nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
    nvgRestore(ctx);
    nvgRestore(ctx);

    nvgSave(ctx);
    nvgBeginPath(ctx);
    nvgTranslate(ctx,
     static_cast<float>(robot_vec[i]->get_left_light_sensor()->get_pose().x),
     static_cast<float>(robot_vec[i]->get_left_light_sensor()->get_pose().y));
    nvgCircle(ctx, 0.0, 0.0, 4.0);
    nvgFillColor(ctx,
           nvgRGBA(robot_vec[i]->get_left_light_sensor()->get_color().r,
              robot_vec[i]->get_left_light_sensor()->get_color().g,
                  robot_vec[i]->get_left_light_sensor()->get_color().b, 255));
    nvgFill(ctx);
    nvgStrokeColor(ctx, nvgRGBA(100, 100, 100, 255));
    nvgStroke(ctx);
    nvgRestore(ctx);

    nvgSave(ctx);
    nvgBeginPath(ctx);
    nvgTranslate(ctx,
     static_cast<float>(robot_vec[i]->get_right_light_sensor()->get_pose().x),
     static_cast<float>(robot_vec[i]->get_right_light_sensor()->get_pose().y));
    nvgCircle(ctx, 0.0, 0.0, 4.0);
    nvgFillColor(ctx,
           nvgRGBA(robot_vec[i]->get_right_light_sensor()->get_color().r,
              robot_vec[i]->get_right_light_sensor()->get_color().g,
                robot_vec[i]->get_right_light_sensor()->get_color().b, 255));
    nvgFill(ctx);
    nvgStrokeColor(ctx, nvgRGBA(100, 100, 100, 255));
    nvgStroke(ctx);
    nvgRestore(ctx);
  }
}

void GraphicsArenaViewer::DrawArena(NVGcontext *ctx) {
  nvgBeginPath(ctx);
  // Creates new rectangle shaped sub-path.
  nvgRect(ctx, 0, 0, arena_->get_x_dim(), arena_->get_y_dim());
  nvgStrokeColor(ctx, nvgRGBA(255, 255, 255, 255));
  nvgStroke(ctx);
}

void GraphicsArenaViewer::DrawEntity(NVGcontext *ctx,
                                     const ArenaEntity *const entity) {
  // light's circle
  nvgBeginPath(ctx);
  nvgCircle(ctx,
            static_cast<float>(entity->get_pose().x),
            static_cast<float>(entity->get_pose().y),
            static_cast<float>(entity->get_radius()));
  nvgFillColor(ctx,
               nvgRGBA(entity->get_color().r, entity->get_color().g,
                       entity->get_color().b, 255));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  // light id text label
  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  if (entity->get_type() != kRobot)
    nvgText(ctx,
            static_cast<float>(entity->get_pose().x),
            static_cast<float>(entity->get_pose().y),
            entity->get_name().c_str(), nullptr);
}

void GraphicsArenaViewer::DrawUsingNanoVG(NVGcontext *ctx) {
  // initialize text rendering settings
  nvgFontSize(ctx, 18.0f);
  nvgFontFace(ctx, "sans-bold");
  nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
  DrawArena(ctx);
  std::vector<ArenaEntity *> entities = arena_->get_entities();
  for (auto &entity : entities) {
    DrawEntity(ctx, entity);
  } /* for(i..) */
  DrawRobot(ctx, arena_->Robot_Vector());

  if (arena_->get_game_status() == WON) {
    nvgFontSize(ctx, 100.0f);
    nvgText(ctx,
            static_cast<float>(X_DIM / 2),
            static_cast<float>(Y_DIM / 2.2),
            "That's a W! :)", nullptr);
    nvgText(ctx,
            static_cast<float>(X_DIM / 2),
            static_cast<float>(Y_DIM / 1.5),
            "\"New Game\" to restart.", nullptr);
  } else if (arena_->get_game_status() == LOST) {
    nvgFontSize(ctx, 100.0f);
    nvgText(ctx,
            static_cast<float>(X_DIM / 2),
            static_cast<float>(Y_DIM / 2.2),
            "One of the Robot's Starved to Death! :/", nullptr);
    nvgText(ctx,
            static_cast<float>(X_DIM / 2),
            static_cast<float>(Y_DIM / 1.5),
            "\"New Game\" to restart.", nullptr);
  }
}

NAMESPACE_END(csci3081);
