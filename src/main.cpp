#include "main.h"
#include "globals.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include <ostream>

using namespace Robot;
using namespace Robot::Globals;

/**
 * @file main.cpp
 * @brief This file contains the main code for the robot's operation.
 */

/**
 * @brief Structure that holds instances of all robot subsystems.
 */
struct RobotSubsystems {
	Robot::Drivetrain drivetrain;
	Robot::IntakeHook intakeHook;
	Robot::LadyBrown ladybrown;
	Robot::Clamp clamp;
	Robot::GoalStealer goalStealer;
} subsystem;

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::delay(500);

	pros::lcd::initialize();

	// Auton Selector
	Robot_Autonomous::sd::auton_selector.autons_add({
		{"Drive\n\nDrive forward and come back", drive_example},
		{"Red 1\n\nProgram 1", drive_example},
		{"Red 1\n\nProgram 2", drive_example},
		{"Red 1\n\nProgram 3", drive_example},
		{"Red 1\n\nProgram 4", drive_example},
		{"Red 2\n\nProgram 1", drive_example},
		{"Red 2\n\nProgram 2", drive_example},
		{"Red 2\n\nProgram 3", drive_example},
		{"Red 2\n\nProgram 4", drive_example},
		{"Blue 1\n\nProgram 1", drive_example},
		{"Blue 1\n\nProgram 2", drive_example},
		{"Blue 1\n\nProgram 3", drive_example},
		{"Blue 1\n\nProgram 4", drive_example},
		{"Blue 2\n\nProgram 1", drive_example},
		{"Blue 2\n\nProgram 2", drive_example},
		{"Blue 2\n\nProgram 3", drive_example},
		{"Blue 2\n\nProgram 4", drive_example},
	});

	// initalizing chassis and auton selector
	chassis.calibrate(true);
	chassis.setPose(0, 0, 0);
	Robot_Autonomous::sd::initialize();

	std::cout << "Team Position: " << teamPosition.get_angle() << std::endl;
	std::cout << "Auton Position: " << autonPosition.get_angle() << std::endl;

	Robot_Autonomous::sd::potentiometerAutonSet();

	master.rumble(".");
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
	chassis.setPose(0, 0, 0, false);
	
	Robot_Autonomous::sd::auton_selector.selected_auton_call();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::motor_brake_mode_e_t driver_preference_brake = MOTOR_BRAKE_COAST;
	chassis.setBrakeMode(driver_preference_brake);

	while (true) {

		Robot_Autonomous::sd::potentiometerAutonSet();

		// Calls to event handling functions.
		// Bound to Up
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
			autonomous();
		}

		// Bound to X
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
			pros::Task move([&]() { subsystem.ladybrown.moveToPoint(LadyBrown::OFFENSE_STATE); }, "LadyBrownMove");
		}

		subsystem.drivetrain.run();

		// Bound to A to run
		subsystem.clamp.run();
		subsystem.ladybrown.run();
		subsystem.goalStealer.run();

		// Bound to L1, R1 to run
		subsystem.intakeHook.run();

		pros::delay(10); // Small delay to reduce CPU usage

	}
}