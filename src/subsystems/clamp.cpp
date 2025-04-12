#include "robot/clamp.hpp"
#include "globals.hpp"
#include "pros/misc.h"

using namespace Robot;
using namespace Robot::Globals;

void Clamp::run(){
    // Bound to A
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)){
        Clamp::toggle();
    }
}

Clamp::Clamp(){ ; }

void Clamp::toggle(){
    clampControl.toggle();
}