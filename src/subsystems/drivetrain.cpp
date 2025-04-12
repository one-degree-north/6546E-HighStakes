#include "robot/drivetrain.hpp"
#include "globals.hpp"
#include "lemlib/chassis/chassis.hpp"

#define DEFAULT_DELAY_LENGTH 15

using namespace Robot;
using namespace Robot::Globals;

Drivetrain::DRIVE_MODE Drivetrain::driveMode = TANK_DRIVE;

bool Drivetrain::isReversed = false;

Drivetrain::Drivetrain(){}

void Drivetrain::CurvatureDrive() {
    int left = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int right = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
 
    chassis.curvature(thrustHandler(left), thrustHandler(right));
 
    pros::delay(DEFAULT_DELAY_LENGTH);
}
 
void Drivetrain::ArcadeDrive() {
    // Arcade Measurements
    int left = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int right = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
 
    chassis.arcade(thrustHandler(left), thrustHandler(right), false, 0.4);
 
    pros::delay(DEFAULT_DELAY_LENGTH);
}
 
void Drivetrain::TankDrive() {
    int left = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int right = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
 
    chassis.tank(thrustHandler(left), thrustHandler(right));
 
    pros::delay(DEFAULT_DELAY_LENGTH);
}
 
// Run the drivetrain depending on the control mode
void Drivetrain::run() {
}
 
// Cycle through each drivetrain control mode, overflows back to 0
std::string Drivetrain::toggleDrive() {
    int driveMode = (Drivetrain::driveMode + 1) % (TANK_DRIVE + 1);
    return SwitchDrive(driveMode);
}
 
int Drivetrain::thrustHandler(int thrust) {
    if (Drivetrain::isReversed) {
       // Sets each motor to its opposite direction - see globals.cpp for motor ports
       return thrust * -1;
    }
    return thrust;
}

// Switch the drivetrain control mode between arcade and tank drive with the down button(between 1 and 2)
std::string Drivetrain::SwitchDrive(int driveMode) {
    switch (driveMode) {
    case 0:
       Drivetrain::driveMode = CURVATURE_DRIVE;
       std::cout << "Curvature Drive" << std::endl;
       return "Curvature Drive";
    case 1:
       Drivetrain::driveMode = ARCADE_DRIVE;
       std::cout << "Arcade Drive" << std::endl;
       return "Arcade Drive";
    case 2:
       Drivetrain::driveMode = TANK_DRIVE;
       std::cout << "Tank Drive" << std::endl;
       return "Tank Drive";
    default:
       std::cout << "Not a valid drivetrain control mode!" << std::endl;
       return "Not a valid driveMode!";
    }
 }