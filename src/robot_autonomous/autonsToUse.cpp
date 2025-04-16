/*
This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this
file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "robot_autonomous/autonsToUse.hpp"
#include <functional>
#include <iostream>

Robot_Autonomous::AutonsToUse::AutonsToUse(){
  Name = "";
  auton_call = nullptr;
}

Robot_Autonomous::AutonsToUse::AutonsToUse(std::string nameOfAuton, std::function<void()> callback) {
  Name = nameOfAuton;
  auton_call = callback;
}