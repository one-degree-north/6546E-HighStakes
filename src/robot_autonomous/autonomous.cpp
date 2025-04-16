#include "robot_autonomous/autonomous.hpp"
#include "globals.hpp"

using namespace Robot;
using namespace Robot::Globals;

constexpr int delay_constant = 1050;

void drive_example(){

}

void turn_example(){
    // set position to x:0, y:0, heading:0
    chassis.setPose(0, 0, 0);
    // turn to face heading 90 with a very long timeout
    chassis.turnToHeading(90, 100000);
}