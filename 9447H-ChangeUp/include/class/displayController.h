#include "main.h"
#include "globals.h"

LV_IMG_DECLARE(BlueSide);
LV_IMG_DECLARE(RedSide);
LV_IMG_DECLARE(Reset);
LV_IMG_DECLARE(test);

class Display{
public:
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
  Display& arcchecker();

private:
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

  lv_obj_t * scr = lv_cont_create(NULL, NULL);

  lv_obj_t * tabview = lv_tabview_create(lv_layer_top(), NULL);
  lv_obj_t * tab1 = lv_tabview_add_tab(tabview, "Autons");
  lv_obj_t * tab2 = lv_tabview_add_tab(tabview, "Sensors");
  lv_obj_t * tab3 = lv_tabview_add_tab(tabview, "Reset");

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
  lv_obj_t * Preset = lv_ddlist_create(tab1, NULL);

  lv_obj_t * btnm = lv_btnm_create(tab1, NULL);

  lv_obj_t * background = lv_img_create(scr, NULL);

  lv_obj_t * robot = lv_btn_create(tab2, NULL);
  lv_obj_t * facing = lv_label_create(robot, NULL);
  lv_obj_t * label= lv_label_create(tab2,NULL);
};
