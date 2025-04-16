#include "robot/intakehook.hpp"
#include "globals.hpp"

#define FASTER_VELOCITY 600
#define SLOWER_VELOCITY 200

using namespace Robot;
using namespace Robot::Globals;;

IntakeHook::IntakeHook() {
    alliance_color = false;
}

void IntakeHook::run() {
// Bound to R1 and L1
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
       IntakeHookMotor.move_velocity(-FASTER_VELOCITY);
    } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        IntakeHookMotor.move_velocity(FASTER_VELOCITY);
    } else {
        IntakeHookMotor.brake();\
    }
 }