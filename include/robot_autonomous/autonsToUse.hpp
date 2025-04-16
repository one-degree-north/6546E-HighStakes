// Taken from EZ-Template and adjusted for potentiometers

/*
This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this
file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#pragma once
#include <functional>
#include <iostream>

namespace Robot_Autonomous {
class AutonsToUse {
 public:
  AutonsToUse();
  AutonsToUse(std::string, std::function<void()>);
  std::string Name;
  std::function<void()> auton_call;

 private:
};
}  // namespace Robot_Autonomous  