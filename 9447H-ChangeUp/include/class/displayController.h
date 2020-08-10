#include "main.h"
#include "globals.h"

#include <bits/stdc++.h>
#include <vector>

LV_IMG_DECLARE(RedSide)
LV_IMG_DECLARE(Reset)
LV_IMG_DECLARE(imgstart)
LV_IMG_DECLARE(sensorpage)
LV_FONT_DECLARE(xirod);


class Display{
public:
  /*
  Does all the needed motor and sensor setup.
  Run this before anything else.
  */
  Display& setup();

  /*
  Initializes the GUI and sets up Screen and Tabs.
  */
  Display& display();

  /*
  Changes background based on Preset DropDown.
  */
  Display& backgroundcheck();

  /*
  Creates circles around selected goals.
  */
  Display& arcChecker();

  /*
  Stores wanted starting position.
  */
  Display& setStart();

  /*
  Stores first wanted position for auton.
  */
  Display& setFirst();

  /*
  Stores second wanted position for auton.
  */
  Display& setSecond();

  /*
  Stores third wanted position for auton.
  */
  Display& setThird();

  /*
  Hides all object except the objects used in the setup function.
  */
  Display& hide();

  /*
  Destroys the objects used in the setup function.
  */
  Display& destroy();

  /*
  Runs the functions to set variables for autonomous.
  */
  Display& setVars();

  /*
  Gets first stored position for auton.
  */
  int getFirst();

  /*
  Gets Current position for auton.
  */
  int getCurrent();

  /*
  Updates the variables for the sensors on the Second Tab.
  */
  void updateSensors();

  /*
  Creates objects needed for selected tab and deletes other tabs objects.
  */
  void tabSelecter();

  /*
  Creates all of tab1's objects.
  */
  void create_tab1(lv_obj_t * parent);

  /*
  Creates all of tab2's objects.
  */
  void create_tab2(lv_obj_t * parent);

  /*
  Creates all of tab3's objects.
  */
  void create_tab3(lv_obj_t * parent);

  /*
  Creates all of tab4's objects
  */
  void create_tab4(lv_obj_t * parent);

private:

  lv_obj_t * scr = lv_cont_create(NULL, NULL);

  lv_obj_t * tabview = lv_tabview_create(lv_layer_top(), NULL);
  lv_obj_t * tab1 = lv_tabview_add_tab(tabview, "Auton");
  lv_obj_t * tab2 = lv_tabview_add_tab(tabview, "Sensors");
  // lv_obj_t * tab3 = lv_tabview_add_tab(tabview, "PID");
  lv_obj_t * tab4 = lv_tabview_add_tab(tabview, "Reset");

  lv_theme_t * th = lv_theme_night_init(20, NULL);

  lv_obj_t * arc1 = lv_arc_create(lv_layer_top(), NULL);
  lv_obj_t * arc2 = lv_arc_create(lv_layer_top(), NULL);
  lv_obj_t * arc3 = lv_arc_create(lv_layer_top(), NULL);
  lv_obj_t * arc4 = lv_arc_create(lv_layer_top(), NULL);
  lv_obj_t * arc5 = lv_arc_create(lv_layer_top(), NULL);
  lv_obj_t * arc6 = lv_arc_create(lv_layer_top(), NULL);
  lv_obj_t * btn1 = lv_btn_create(tab1, NULL);
  lv_obj_t * btn2 = lv_btn_create(tab1, NULL);
  lv_obj_t * label1 = lv_label_create(btn1, NULL);
  lv_obj_t * label2 = lv_label_create(btn2, NULL);

  lv_obj_t * btnm = lv_btnm_create(tab1, NULL);

  lv_obj_t * background = lv_img_create(scr, NULL);

  lv_obj_t * lIMU= lv_label_create(tab2,NULL);
  lv_obj_t * mIMU= lv_label_create(tab2,NULL);
  lv_obj_t * rIMU= lv_label_create(tab2,NULL);
  lv_obj_t * lEncoder= lv_label_create(tab2,NULL);
  lv_obj_t * rEncoder= lv_label_create(tab2,NULL);

  lv_obj_t * progressbar = lv_bar_create(lv_layer_top(), NULL);
  lv_obj_t * nine = lv_label_create(lv_layer_top(), NULL);
  int prog = 0;


  lv_obj_t * letternumberImg = lv_img_create(lv_scr_act(), NULL);

  std::vector<int> buttonVec = {};
};
