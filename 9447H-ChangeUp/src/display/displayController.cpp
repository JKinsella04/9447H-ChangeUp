#include "class/displayController.h"

 const char * map[] = { "4", " ", "5", " ", "6", "\n",
                    "\n", "\n",
                    "1", " ", "2", " ", "3", "" };

 Display& Display::display(){
   lv_scr_load(scr);
   lv_tabview_set_btns_pos(tabview,LV_TABVIEW_BTNS_POS_BOTTOM);
   lv_obj_set_size(tabview, 480, 250);
   lv_tabview_set_sliding(tabview, false);
   lv_theme_set_current(th);

   lv_img_set_src(background, &BlueSide);
   lv_obj_set_pos(background, 0,0);

  static lv_style_t bg_style;
  lv_style_copy(&bg_style, &lv_style_plain);
  bg_style.body.empty = 1;

  static lv_style_t style_tab;
  lv_style_copy(&style_tab, lv_tabview_get_style(tabview, LV_TABVIEW_STYLE_BTN_REL));
  // style_tab.text.font = &lv_font_dejavu_10;
  style_tab.body.padding.ver = 10;

  static lv_style_t style_arc_rel;
  lv_style_copy(&style_arc_rel, &lv_style_plain);
  style_arc_rel.line.width = 1;
  style_arc_rel.line.color = LV_COLOR_BLACK;
  // style_arc_rel.body.opa = 1;
  lv_tabview_set_style(tabview, LV_TABVIEW_STYLE_BTN_REL, &style_tab);
  lv_tabview_set_style(tabview, LV_TABVIEW_STYLE_BG, &bg_style);

  Display::create_tab1(tab1);
  Display::create_tab2(tab2);
  Display::create_tab3(tab3);
     return *this;
 }

 Display& Display::backgroundcheck(){
  if (lv_ddlist_get_selected(Preset) == 1) {
    lv_img_set_src(background, &RedSide);
    lv_obj_set_pos(background, 0,0);
  }else{
    lv_img_set_src(background, &BlueSide);
    lv_obj_set_pos(background, 0,0);
  }if(lv_tabview_get_tab_act(tabview) == 2){
    lv_img_set_src(background, &Reset);
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

 Display& Display::arcchecker(){
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

 std::vector<int> Display::loadAuton(){
   int press = lv_btnm_get_pressed(btnm);
   switch(press){
     case 0: { buttonVec.push_back(6);  }
     case 2: { buttonVec.push_back(5);  }
     case 4: { buttonVec.push_back(4);  }
     case 5: { buttonVec.push_back(1);  }
     case 7: { buttonVec.push_back(2);  }
     case 9: { buttonVec.push_back(3);  }
   }
   return buttonVec;
 }

 std::vector<int> Display::getAuton(){
   return buttonVec;
 }

 Display& Display::runAuton(){
   /* int first = buttonVec.at(1);
    switch (first){
      case 6: { LF.move(100); break;}
      case 5: { RF.move(100); break;}
      // default: { LF.move(100); break;}
    }
    */
  while(true){
   switch (currentPos) { //Where am I?
     case 0: {
       switch (firstPos) {
         case 1: {currentPos = 1;}//robot's mvmt from 0 to 1
         case 2: {currentPos = 2;}//robot's mvmt from 0 to 2
         case 3: {currentPos = 3;}//robot's mvmt from 0 to 3
         case 4: {currentPos = 4;}//robot's mvmt from 0 to 4
         case 5: {currentPos = 5;}//robot's mvmt from 0 to 5
         case 6: {currentPos = 6;}//robot's mvmt from 0 to 6
       }}
   } //switch
   switch (currentPos){
     case 1: {
       switch (secondPos) {
         case 2: {currentPos = 2;}//robot's mvmt from 1 to 2
         case 3: {currentPos = 3;}//robot's mvmt from 1 to 3
         case 4: {currentPos = 4;}//robot's mvmt from 1 to 4
         case 5: {currentPos = 5;}//robot's mvmt from 1 to 5
         case 6: {currentPos = 6;}//robot's mvmt from 1 to 6
       }}
     case 2: {
       switch (secondPos) {
         case 1: {currentPos = 1;}//robot's mvmt from 2 to 1
         case 3: {currentPos = 3;}//robot's mvmt from 2 to 3
         case 4: {currentPos = 4;}//robot's mvmt from 2 to 4
         case 5: {currentPos = 5;}//robot's mvmt from 2 to 5
         case 6: {currentPos = 6;}//robot's mvmt from 2 to 6
       }}
     case 3: {
       switch (secondPos) {
         case 1: {currentPos = 1;}//robot's mvmt from 3 to 1
         case 2: {currentPos = 2;}//robot's mvmt from 3 to 2
         case 4: {currentPos = 4;}//robot's mvmt from 3 to 4
         case 5: {currentPos = 5;}//robot's mvmt from 3 to 5
         case 6: {currentPos = 6;}//robot's mvmt from 3 to 6
       }}
     case 4: {
       switch (secondPos) {
         case 1: {currentPos = 1;}//robot's mvmt from 4 to 1
         case 2: {currentPos = 2;}//robot's mvmt from 4 to 2
         case 3: {currentPos = 3;}//robot's mvmt from 4 to 3
         case 5: {currentPos = 5;}//robot's mvmt from 4 to 5
         case 6: {currentPos = 6;}//robot's mvmt from 4 to 6
       }}
     case 5: {
       switch (secondPos) {
         case 1: {currentPos = 1;}//robot's mvmt from 5 to 1
         case 2: {currentPos = 2;}//robot's mvmt from 5 to 2
         case 3: {currentPos = 3;}//robot's mvmt from 5 to 3
         case 4: {currentPos = 4;}//robot's mvmt from 5 to 4
         case 6: {currentPos = 6;}//robot's mvmt from 5 to 6
       }}
     case 6: {
       switch (secondPos) {
         case 1: {currentPos = 1;}//robot's mvmt from 6 to 1
         case 2: {currentPos = 2;}//robot's mvmt from 6 to 2
         case 3: {currentPos = 3;}//robot's mvmt from 6 to 3
         case 4: {currentPos = 4;}//robot's mvmt from 6 to 4
         case 5: {currentPos = 5;}//robot's mvmt from 6 to 5
       }} //case 6
   }
 pros::delay(20);} //while
   return *this;
 } //function

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
  style_btn_rel.body.radius = LV_RADIUS_CIRCLE;

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

	lv_ddlist_set_options(Preset,"Blue\nRed");
	lv_obj_set_x(Preset, 10);
	lv_ddlist_set_fix_height(Preset, 80);

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

  lv_btn_set_style(robot, LV_BTN_STYLE_REL, &style_btn_rel);    /*Set the button's released style*/
  lv_btn_set_style(robot, LV_BTN_STYLE_PR, &style_btn_pr);
  lv_label_set_text(facing, "^");
  lv_obj_set_pos(robot,90,135);
  lv_obj_set_size(robot, 50,50);
  lv_page_set_scrl_fit(tab2, false, false);
}

 void Display::create_tab3(lv_obj_t * parent){}
