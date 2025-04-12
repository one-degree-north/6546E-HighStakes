#include "robot/goalstealer.hpp"
#include "globals.hpp"

using namespace Robot;
using namespace Robot::Globals;

void GoalStealer::run() {
   if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
      goalSteal.toggle();
   }
}

GoalStealer::GoalStealer(){ ; }

void GoalStealer::toggle(){ 
    goalSteal.toggle();
}