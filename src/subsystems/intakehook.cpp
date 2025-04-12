#include "robot/intakehook.hpp"
#include "globals.hpp"

#define SLOWER_VELOCITY 200
#define FASTER_VELOCITY 600

using namespace Robot;
using namespace Robot::Globals;;

IntakeHook::IntakeHook() {
    alliance_color = false;
}

void IntakeHook::run() {
// Bound to R1 and L1
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
       IntakeHookMotor.move_velocity(-FASTER_VELOCITY);
       IntakeHookMotor.move_velocity(-SLOWER_VELOCITY);
    } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        IntakeHookMotor.move_velocity(FASTER_VELOCITY);
        IntakeHookMotor.move_velocity(SLOWER_VELOCITY);
    } else {
        IntakeHookMotor.brake();
        IntakeHookMotor.brake();
    }
 }