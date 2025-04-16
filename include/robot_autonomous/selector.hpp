/*
This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this
file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#pragma once
#include <tuple>

#include "robot_autonomous/autonsToUse.hpp"

using namespace std;

namespace Robot_Autonomous {
class AutonSelector {
 public:
  std::vector<Robot_Autonomous::AutonsToUse> Autons;
  int auton_page_current;
  int auton_count;
  int last_auton_page_current;
  AutonSelector();
  AutonSelector(std::vector<Robot_Autonomous::AutonsToUse> autons);
  void selected_auton_call();
  void selected_auton_print();
  void autons_add(std::vector<Robot_Autonomous::AutonsToUse> autons);
};
}  // namespace Robot_Autonomous