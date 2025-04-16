/*
This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this
file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "robot_autonomous/autonsToUse.hpp"
#include "robot_autonomous/selector.hpp"
#include "robot_autonomous/util.hpp"
#include "pros/apix.h"

Robot_Autonomous::AutonSelector::AutonSelector() {
  auton_count = 0;
  auton_page_current = 0;
  Autons = {};
}

Robot_Autonomous::AutonSelector::AutonSelector(std::vector<AutonsToUse> autons) {
  auton_count = autons.size();
  auton_page_current = 0;
  Autons = {};
  Autons.assign(autons.begin(), autons.end());
}

void Robot_Autonomous::AutonSelector::selected_auton_print() {
  if (auton_count == 0) return;
  for (int i = 0; i < 8; i++)
    pros::lcd::clear_line(i);
  Robot_Autonomous::screen_print("Page " + std::to_string(auton_page_current + 1) + "\n" + Autons[auton_page_current].Name);
}

void Robot_Autonomous::AutonSelector::selected_auton_call() {
  if (auton_count == 0) return;
  Autons[last_auton_page_current].auton_call();
}

void Robot_Autonomous::AutonSelector::autons_add(std::vector<AutonsToUse> autons) {
  auton_count += autons.size();
  auton_page_current = 0;
  Autons.assign(autons.begin(), autons.end());
}