#include "class/displayController.h"

 const char * map[] = { "4", " ", "5", " ", "6", "\n",
                    "\n", "\n",
                    "1", " ", "2", " ", "3", "" };

 Display& Display::setup(){
   lv_obj_set_hidden(nine, true);
   static lv_style_t bar_style;
   lv_style_copy(&bar_style, &lv_style_plain);
   bar_style.body.border.color = LV_COLOR_BLACK;
   bar_style.body.border.opa = 1;
   bar_style.body.main_color = LV_COLOR_BLACK;
   bar_style.body.grad_color = LV_COLOR_BLACK;
   bar_style.body.radius =  LV_RADIUS_CIRCLE;
   lv_theme_set_current(th);
   lv_vdb_t * vdb = lv_vdb_get();
   memset(vdb->buf, 0x00, sizeof(lv_color_t) * LV_VDB_SIZE);
   lv_obj_set_style(lv_scr_act(), &lv_style_transp);
   lv_img_set_src(letternumberImg, &imgstart);
   lv_obj_align(letternumberImg, NULL,LV_ALIGN_CENTER,0,0);

   hide();
   lv_obj_set_size(progressbar, 400, 20);
   lv_obj_align(progressbar, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -10);
   lv_obj_set_style(progressbar, &bar_style);
   L_IMU.reset();
   M_IMU.reset();
   R_IMU.reset();
   // pros::delay(2000);
   REncoder.reset();
   LEncoder.reset();
   MEncoder.reset();
    // pros::delay(1000);
   while(prog < 100){
    prog ++;
    lv_bar_set_value(progressbar, prog);
    if(prog == 100){*isSetup = true; break;}
    pros::delay(50);
   }

   return *this;
 }

 Display& Display::display(){
   lv_scr_load(scr);
   lv_tabview_set_btns_pos(tabview,LV_TABVIEW_BTNS_POS_BOTTOM);
   lv_obj_set_size(tabview, 480, 250);
   lv_tabview_set_sliding(tabview, false);

  static lv_style_t bg_style;
  lv_style_copy(&bg_style, &lv_style_plain);
  bg_style.body.empty = 1;

  static lv_style_t style_tab;
  lv_style_copy(&style_tab, lv_tabview_get_style(tabview, LV_TABVIEW_STYLE_BTN_REL));
  // style_tab.text.font = &asman;
  style_tab.body.padding.ver = 10;

  static lv_style_t style_arc_rel;
  lv_style_copy(&style_arc_rel, &lv_style_plain);
  style_arc_rel.line.width = 1;
  style_arc_rel.line.color = LV_COLOR_BLACK;
  // style_arc_rel.body.opa = 1;
  lv_tabview_set_style(tabview, LV_TABVIEW_STYLE_BTN_REL, &style_tab);
  lv_tabview_set_style(tabview, LV_TABVIEW_STYLE_BG, &bg_style);

  create_tab1(tab1);
  create_tab2(tab2);
  // create_tab3(tab3);
  create_tab4(tab4);
     return *this;
 }

 Display& Display::backgroundcheck(){
  if(lv_tabview_get_tab_act(tabview) == 2){
    lv_img_set_src(background, &Reset);
    lv_obj_set_pos(background, 0,0);
  }else if(lv_tabview_get_tab_act(tabview) == 1){
    lv_img_set_src(background, &sensorpage);
    lv_obj_set_pos(background, 0,0);
  }else{
    lv_img_set_src(background, &RedSide);
    lv_obj_set_pos(background, 0,0);
  }if(lv_tabview_get_tab_act(tabview) != 0){
    lv_obj_set_hidden(arc1, true);
    lv_obj_set_hidden(arc2, true);
    lv_obj_set_hidden(arc3, true);
    lv_obj_set_hidden(arc4, true);
    lv_obj_set_hidden(arc5, true);
    lv_obj_set_hidden(arc6, true);
  }
return *this;
 }

 Display& Display::arcChecker(){
  int currentpr = lv_btnm_get_pressed(btnm); //Gets which Button was pressed

 switch (currentpr){ //Creates arc based on which button was pressed, creating a different arc at a different position.

   case 0: {
      lv_obj_set_hidden(arc1, false);
     lv_arc_set_angles(arc1, 0,360);
     static lv_style_t style_arc1_rel;
     lv_style_copy(&style_arc1_rel, &lv_style_plain);
     style_arc1_rel.line.color = LV_COLOR_LIME;
     style_arc1_rel.line.width = 3;
     lv_arc_set_style(arc1, LV_ARC_STYLE_MAIN, &style_arc1_rel);
     lv_obj_set_x(arc1, 100);
     lv_obj_set_y(arc1, -9);
     lv_obj_set_size(arc1, 30, 25);
     break;
   }
   case 2:{
      lv_obj_set_hidden(arc2, false);
     lv_arc_set_angles(arc2, 0,360);
     static lv_style_t style_arc2_rel;
     lv_style_copy(&style_arc2_rel, &lv_style_plain);
     style_arc2_rel.line.color = LV_COLOR_LIME;
     style_arc2_rel.line.width = 3;
     lv_arc_set_style(arc2, LV_ARC_STYLE_MAIN, &style_arc2_rel);
     lv_obj_set_x(arc2, 275);
     lv_obj_set_y(arc2, -9);
     lv_obj_set_size(arc2, 30, 25);
     break;
   }
   case 4: {
      lv_obj_set_hidden(arc3, false);
     lv_arc_set_angles(arc3, 0,360);
     static lv_style_t style_arc3_rel;
     lv_style_copy(&style_arc3_rel, &lv_style_plain);
     style_arc3_rel.line.color = LV_COLOR_LIME;
     style_arc3_rel.line.width = 3;
     lv_arc_set_style(arc3, LV_ARC_STYLE_MAIN, &style_arc3_rel);
     lv_obj_set_x(arc3, 445);
     lv_obj_set_y(arc3, -9);
     lv_obj_set_size(arc3, 30, 25);
     break;
   }
   case 5: {
      lv_obj_set_hidden(arc4, false);
     lv_arc_set_angles(arc4, 0,360);
     static lv_style_t style_arc4_rel;
     lv_style_copy(&style_arc4_rel, &lv_style_plain);
     style_arc4_rel.line.color = LV_COLOR_LIME;
     style_arc4_rel.line.width = 3;
     lv_arc_set_style(arc4, LV_ARC_STYLE_MAIN, &style_arc4_rel);
     lv_obj_set_x(arc4, 100);
     lv_obj_set_y(arc4, 160);
     lv_obj_set_size(arc4, 30, 25);
     break;
   }
   case 7: {
      lv_obj_set_hidden(arc5, false);
     lv_arc_set_angles(arc5, 0,360);
     static lv_style_t style_arc5_rel;
     lv_style_copy(&style_arc5_rel, &lv_style_plain);
     style_arc5_rel.line.color = LV_COLOR_LIME;
     style_arc5_rel.line.width = 3;
     lv_arc_set_style(arc5, LV_ARC_STYLE_MAIN, &style_arc5_rel);
     lv_obj_set_x(arc5, 275);
     lv_obj_set_y(arc5, 160);
     lv_obj_set_size(arc5, 30, 25);
     break;
   }
   case 9: {
      lv_obj_set_hidden(arc6, false);
     lv_arc_set_angles(arc6, 0,360);
     static lv_style_t style_arc6_rel;
     lv_style_copy(&style_arc6_rel, &lv_style_plain);
     style_arc6_rel.line.color = LV_COLOR_LIME;
     style_arc6_rel.line.width = 3;
     lv_arc_set_style(arc6, LV_ARC_STYLE_MAIN, &style_arc6_rel);
     lv_obj_set_x(arc6, 445);
     lv_obj_set_y(arc6, 160);
     lv_obj_set_size(arc6, 30, 25);
     break;
   }
  }
return *this;
  }

 Display& Display::setStart(){
   if(lv_btn_get_state(btn1) ==1) {startPos = 1;}
   if(lv_btn_get_state(btn2) ==1) {startPos = 2;}
   return *this;
 }

 Display& Display::setFirst(){
    int press = lv_btnm_get_pressed(btnm);
    switch(press) {
      case 0: { firstPos = 6;  break;}
      case 2: { firstPos = 5;  break;}
      case 4: { firstPos = 4;  break;}
      case 5: { firstPos = 1;  break;}
      case 7: { firstPos = 2;  break;}
      case 9: { firstPos = 3;  break;}
    }
    return *this;
  }

 Display& Display::setSecond(){
   int press = lv_btnm_get_pressed(btnm);
   switch(press) {
     case 0: { secondPos = 6;  break;}
     case 2: { secondPos = 5;  break;}
     case 4: { secondPos = 4;  break;}
     case 5: { secondPos = 1;  break;}
     case 7: { secondPos = 2;  break;}
     case 9: { secondPos = 3;  break;}
   }
   return *this;
 }

 Display& Display::setThird(){
   int press = lv_btnm_get_pressed(btnm);
   switch(press) {
     case 0: { thirdPos = 6;  break;}
     case 2: { thirdPos = 5;  break;}
     case 4: { thirdPos = 4;  break;}
     case 5: { thirdPos = 1;  break;}
     case 7: { thirdPos = 2;  break;}
     case 9: { thirdPos = 3;  break;}
   }
   return *this;
 }

 Display& Display::hide(){
   lv_obj_set_hidden(arc1, true);
   lv_obj_set_hidden(arc2, true);
   lv_obj_set_hidden(arc3, true);
   lv_obj_set_hidden(arc4, true);
   lv_obj_set_hidden(arc5, true);
   lv_obj_set_hidden(arc6, true);
   lv_obj_set_hidden(tabview, true);
   lv_obj_set_hidden(btnm, true);
   lv_obj_set_hidden(btn1, true);
   lv_obj_set_hidden(btn2, true);
   return *this;
 }

 Display& Display::destroy(){
   lv_obj_set_hidden(arc1, false);
   lv_obj_set_hidden(arc2, false);
   lv_obj_set_hidden(arc3, false);
   lv_obj_set_hidden(arc4, false);
   lv_obj_set_hidden(arc5, false);
   lv_obj_set_hidden(arc6, false);
   lv_obj_set_hidden(tabview, false);
   lv_obj_set_hidden(btnm, false);
   lv_obj_set_hidden(btn1, false);
   lv_obj_set_hidden(btn2, false);
   lv_obj_del(progressbar);
   lv_obj_del(nine);
   lv_obj_del(letternumberImg);
   delete isSetup;
   return *this;
 }

 Display& Display::setVars(){
   if(lv_tabview_get_tab_act(tabview) == 0){
   while(startPos == 0){ setStart(); arcChecker(); pros::delay(20);}
   while(firstPos == 0 && startPos !=0){ setFirst(); arcChecker(); pros::delay(20);}
   pros::delay(500);
   while(secondPos == 0 && firstPos != 0){ setSecond();arcChecker(); pros::delay(20);}
   pros::delay(500);
   while(thirdPos == 0 && secondPos != 0 && firstPos != 0){ setThird(); arcChecker(); pros::delay(20);}
 pros::delay(20);}
 return *this;
 }

 int Display::getFirst(){
   return firstPos;
 }

 int Display::getCurrent(){
   return currentPos;
 }

 void Display::updateSensors(){
   static lv_style_t style_text;
   lv_style_copy(&style_text, &lv_style_pretty);
   style_text.text.color = LV_COLOR_WHITE;
   style_text.text.font = &xirod;
   lv_label_set_style(lIMU, &style_text);
   lv_label_set_style(mIMU, &style_text);
   lv_label_set_style(rIMU, &style_text);
   lv_label_set_style(lEncoder, &style_text);
   lv_label_set_style(rEncoder, &style_text);

   int LimuPos = L_IMU.get_heading();
   int MimuPos = M_IMU.get_heading();
   int RimuPos = R_IMU.get_heading();
   int Lencoder = LEncoder.get_value();
   int Rencoder = REncoder.get_value();

   std::string Ltext = std::to_string(LimuPos);
   lv_label_set_text(lIMU, Ltext.c_str());
   lv_obj_set_pos(lIMU, 80, 80);

   std::string Mtext = std::to_string(MimuPos);
   lv_label_set_text(mIMU, Mtext.c_str());
   lv_obj_set_pos(mIMU, 200, 80);

   std::string Rtext = std::to_string(RimuPos);
   lv_label_set_text(rIMU, Rtext.c_str());
   lv_obj_set_pos(rIMU, 320, 80);

   std::string REtext = std::to_string(Rencoder);
   lv_label_set_text(rEncoder, REtext.c_str());
   lv_obj_set_pos(rEncoder, 220, 115);

   std::string LEtext = std::to_string(Lencoder);
   lv_label_set_text(lEncoder, LEtext.c_str());
   lv_obj_set_pos(lEncoder, 80, 115);
 }

 void Display::create_tab1(lv_obj_t * parent){
  static lv_style_t style_btn_rel;                        /*A variable to store the released style*/
  lv_style_copy(&style_btn_rel, &lv_style_plain);         /*Initialize from a built-in style*/
  style_btn_rel.body.border.color = lv_color_hex3(0x333333);
  style_btn_rel.body.border.width = 1;
  style_btn_rel.body.main_color = lv_color_hex3(0x333333);
  style_btn_rel.body.grad_color = lv_color_hex3(0x333333);
  style_btn_rel.text.color = lv_color_hex3(0xDEF);
  style_btn_rel.body.radius = LV_RADIUS_CIRCLE;

  static lv_style_t style_btn_pr;                         /*A variable to store the pressed style*/
  lv_style_copy(&style_btn_pr, &style_btn_rel);           /*Initialize from the released style*/
  style_btn_pr.body.border.color = lv_color_hex3(0x585858);
  style_btn_pr.body.main_color = lv_color_hex3(0xC24365);
  style_btn_pr.body.grad_color = lv_color_hex3(0x000000);
  style_btn_pr.body.shadow.width = 2;
  style_btn_pr.text.color = lv_color_hex3(0xBCD);
  style_btn_pr.body.radius = LV_RADIUS_CIRCLE;

  static lv_style_t style_goal_rel;
  lv_style_copy(&style_goal_rel, &lv_style_transp);
  style_goal_rel.body.empty = true;
  style_goal_rel.text.opa = 1;
  style_goal_rel.text.color = LV_COLOR_MAKE(0x70, 0xFF, 0x70);

  static lv_style_t style_goal_pr;
  lv_style_copy(&style_goal_pr, &lv_style_transp);
  style_goal_rel.body.empty = true;
  style_goal_rel.text.opa = 1;
  style_goal_rel.text.color = LV_COLOR_MAKE(0x70, 0xFF, 0x70);

  lv_obj_set_x(btn1, 5);
  lv_obj_set_y(btn1, 80);
  lv_obj_set_size(btn1, 75, 40);

  lv_obj_set_x(btn2, 5);
  lv_obj_set_y(btn2, 130);
  lv_obj_set_size(btn2, 75, 40);

  lv_label_set_text(label1, "1");
	lv_label_set_text(label2, "2");

	// lv_ddlist_set_options(Preset,"Blue\nRed");
	// lv_obj_set_x(Preset, 10);
	// lv_ddlist_set_fix_height(Preset, 80);

	lv_btnm_set_map(btnm, map);
	lv_btnm_set_toggle(btnm, false,0);
	lv_obj_set_x(btnm, 95);
	lv_obj_set_y(btnm, -5);
	lv_obj_set_size(btnm, 380, 180); //380,185

  lv_btn_set_style(btn1, LV_BTN_STYLE_REL, &style_btn_rel);    /*Set the button's released style*/
  lv_btn_set_style(btn1, LV_BTN_STYLE_PR, &style_btn_pr);      /*Set the button's pressed style*/

  lv_btn_set_style(btn2, LV_BTN_STYLE_REL, &style_btn_rel);    /*Set the button's released style*/
  lv_btn_set_style(btn2, LV_BTN_STYLE_PR, &style_btn_pr);

  lv_btnm_set_style(btnm, LV_BTN_STYLE_REL, &style_goal_rel);
  lv_btnm_set_style(btnm, LV_BTN_STYLE_PR, &style_goal_pr);

  lv_obj_set_hidden(arc1, true);
  lv_obj_set_hidden(arc2, true);
  lv_obj_set_hidden(arc3, true);
  lv_obj_set_hidden(arc4, true);
  lv_obj_set_hidden(arc5, true);
  lv_obj_set_hidden(arc6, true);

}

 void Display::create_tab2(lv_obj_t * parent){
   static lv_style_t style_btn_rel;                        /*A variable to store the released style*/
   lv_style_copy(&style_btn_rel, &lv_style_plain);         /*Initialize from a built-in style*/
   style_btn_rel.body.border.color = lv_color_hex3(0x333333);
   style_btn_rel.body.border.width = 1;
   style_btn_rel.body.main_color = lv_color_hex3(0x333333);
   style_btn_rel.body.grad_color = lv_color_hex3(0x333333);
   style_btn_rel.text.color = lv_color_hex3(0xDEF);
   style_btn_rel.body.radius = LV_RADIUS_CIRCLE;

   static lv_style_t style_btn_pr;                         /*A variable to store the pressed style*/
   lv_style_copy(&style_btn_pr, &style_btn_rel);           /*Initialize from the released style*/
   style_btn_pr.body.border.color = lv_color_hex3(0x585858);
   style_btn_pr.body.main_color = lv_color_hex3(0xC24365);
   style_btn_pr.body.grad_color = lv_color_hex3(0x000000);
   style_btn_pr.body.shadow.width = 2;
   style_btn_pr.text.color = lv_color_hex3(0xBCD);
   style_btn_rel.body.radius = LV_RADIUS_CIRCLE;



  // lv_btn_set_style(robot, LV_BTN_STYLE_REL, &style_btn_rel);    /*Set the button's released style*/
  // lv_btn_set_style(robot, LV_BTN_STYLE_PR, &style_btn_pr);
  // lv_label_set_text(facing, "^");
  // lv_obj_set_pos(robot,90,135);
  // lv_obj_set_size(robot, 50,50);
  // lv_page_set_scrl_fit(tab2, false, false);
}

 void Display::create_tab3(lv_obj_t * parent){

  }

 void Display::create_tab4(lv_obj_t * parent){
    lv_obj_t * btnImu = lv_btn_create(tab4, NULL);
    lv_obj_t * btnVis = lv_btn_create(tab4, NULL);
    lv_obj_t * btnOdom = lv_btn_create(tab4, NULL);
    lv_obj_t * btnChassis = lv_btn_create(tab4, NULL);
    lv_obj_t * lblImu = lv_label_create(btnImu, NULL);
    lv_obj_t * lblOdom = lv_label_create(btnOdom, NULL);
    lv_obj_t * lblVis = lv_label_create(btnVis, NULL);
    lv_obj_t * lblChassis = lv_label_create(btnChassis, NULL);

    static lv_style_t style_btn_rel;                        /*A variable to store the released style*/
    lv_style_copy(&style_btn_rel, &lv_style_plain);         /*Initialize from a built-in style*/
    style_btn_rel.body.border.color = lv_color_hex3(0x333333);
    style_btn_rel.body.border.width = 1;
    style_btn_rel.body.main_color = lv_color_hex3(0x333333);
    style_btn_rel.body.grad_color = lv_color_hex3(0x333333);
    style_btn_rel.text.color = lv_color_hex3(0xDEF);
    style_btn_rel.body.radius = LV_RADIUS_CIRCLE;

    static lv_style_t style_btn_pr;                         /*A variable to store the pressed style*/
    lv_style_copy(&style_btn_pr, &style_btn_rel);           /*Initialize from the released style*/
    style_btn_pr.body.border.color = lv_color_hex3(0x585858);
    style_btn_pr.body.main_color = lv_color_hex3(0xC24365);
    style_btn_pr.body.grad_color = lv_color_hex3(0x000000);
    style_btn_pr.body.shadow.width = 2;
    style_btn_pr.text.color = lv_color_hex3(0xBCD);
    style_btn_rel.body.radius = LV_RADIUS_CIRCLE;

    lv_btn_set_style(btnImu, LV_BTN_STYLE_REL, &style_btn_rel);
    lv_btn_set_style(btnImu, LV_BTN_STYLE_PR, &style_btn_pr);
    lv_btn_set_style(btnVis, LV_BTN_STYLE_REL, &style_btn_rel);
    lv_btn_set_style(btnVis, LV_BTN_STYLE_PR, &style_btn_pr);
    lv_btn_set_style(btnOdom, LV_BTN_STYLE_REL, &style_btn_rel);
    lv_btn_set_style(btnOdom, LV_BTN_STYLE_PR, &style_btn_pr);
    lv_btn_set_style(btnChassis, LV_BTN_STYLE_REL, &style_btn_rel);
    lv_btn_set_style(btnChassis, LV_BTN_STYLE_PR, &style_btn_pr);

    lv_obj_set_pos(btnImu, 10,10);  //Not actual positions
    lv_obj_set_size(btnImu, 150, 30);
    lv_obj_set_pos(btnOdom, 10,50);
    lv_obj_set_size(btnOdom,150, 30);
    lv_obj_set_pos(btnVis, 10,90);
    lv_obj_set_size(btnVis, 150, 30);
    lv_obj_set_pos(btnChassis, 10,130);
    lv_obj_set_size(btnChassis, 150, 30);
    lv_label_set_text(lblImu, "Reset Inertial");
    lv_label_set_text(lblOdom, "Reset Odom");
    lv_label_set_text(lblVis, "Reset Vision");
    lv_label_set_text(lblChassis, "Reset Chassis");

    if(lv_btn_get_state(btnImu)== LV_BTN_STATE_PR){
      L_IMU.reset();
      M_IMU.reset();
      R_IMU.reset();
    }
    if(lv_btn_get_state(btnVis)== LV_BTN_STATE_PR) {
      //Reset Vision Sensor
    }
    if(lv_btn_get_state(btnOdom)== LV_BTN_STATE_PR) {
      REncoder.reset();
      LEncoder.reset();
      MEncoder.reset();
    }
    if(lv_btn_get_state(btnChassis)== LV_BTN_STATE_PR) {
      LF.tare_position();
      LB.tare_position();
      RF.tare_position();
      RB.tare_position();
    }
    // if(lv_tabview_get_tab_act(tabview) != 3){
    //   lv_obj_del(btnImu);
    //   lv_obj_del(btnVis);
    //   lv_obj_del(btnOdom);
    //   lv_obj_del(btnChassis);
    // }
  }
