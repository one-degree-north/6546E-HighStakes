#include "globals.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/adi.hpp"
#include "pros/distance.hpp"
#include "pros/imu.hpp"
#include "pros/misc.h"
#include "pros/motor_group.hpp"
#include "pros/motors.hpp"
#include "pros/optical.hpp"
#include "pros/rotation.hpp"

// Defines the objects that are used by the program for each of the individual
// subsystems.

namespace Robot{
 namespace Globals{
    
    pros::Controller master(pros::E_CONTROLLER_MASTER);

    // ALL MOTOR PORTS ARE TEMP UNTIL PLUGGED

    // drivetrain
    pros::Motor LeftFront(1, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
    pros::Motor LeftMid(1, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
    pros::Motor LeftBack(1, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
    pros::Motor RightFront(1, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
    pros::Motor RightMid(1, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
    pros::Motor RightBack(1, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

    // other motors
    pros::Motor IntakeHookMotor(1, pros::v5::MotorGear::blue, pros::v5::MotorUnits::degrees);
    pros::Motor LadyBrownMotorMotor(1, pros::v5::MotorGear::red, pros::v5::MotorUnits::degrees);
    
    // pneumatics
    pros::adi::Pneumatics clampControl('A', false);
    pros::adi::Pneumatics goalSteal('B', false);

    // sensors
    pros::IMU inertial_sensor(1);
    pros::Rotation ladyBrownRotational(1);
    pros::Distance clamp_sensor(1);

    pros::Rotation lateral_sensor(1);
    pros::Rotation horizontal_sensor(1);

    // optical/color sort related
    pros::Optical colorSensor(1);

    // Pros motor groups - mostly used by lemlib
    pros::MotorGroup drive_left({LeftFront.get_port(), LeftMid.get_port(), LeftBack.get_port()});
    pros::MotorGroup drive_right({RightFront.get_port(), RightMid.get_port(), RightBack.get_port()});
    pros::MotorGroup drive_({LeftFront.get_port(), RightFront.get_port(), LeftMid.get_port(), RightMid.get_port(), LeftBack.get_port(), RightBack.get_port()});

    // Lemlib objects - Used by lemlib drive and odometry functions
    // DISTANCE UNKNOWN
    lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_sensor, 2, -2.75);
    lemlib::TrackingWheel vertical_tracking_wheel(&lateral_sensor, 2, -1);

    // Describes the lemlib objects that are used to control the autonomous
    // functions of the robot.
    // TRACK WIDTH TO BE ADDED, HORIZONTAL DRIFT TO BE ADDED
    lemlib::Drivetrain drivetrain{
        &drive_left,  // left drivetrain motors
        &drive_right, // right drivetrain motors
        12.25,        // track width
        lemlib::Omniwheel::OLD_325,
        450, // drivetrain rpm is 450
        2    // horizontal drift is 2
    };

    lemlib::OdomSensors odomRotational{
        &vertical_tracking_wheel,   // vertical tracking wheel 1
        nullptr,                    // vertical tracking wheel 2
        &horizontal_tracking_wheel, // horizontal tracking wheel 1
        nullptr,                    // we don't have a second tracking wheel, so we set it to nullptr
        &inertial_sensor            // inertial sensor
    };

    // forward/backward PID
    // lateral PID controller
    lemlib::ControllerSettings lateral_controller(6.5, // proportional gain (kP)
        0,   // integral gain (kI)
        35,  // derivative gain (kD)
        0,   // anti windup
        0.5, // small error range, in inches
        100, // small error range timeout, in milliseconds
        3,   // large error range, in inches
        500, // large error range timeout, in milliseconds
        20   // maximum acceleration (slew)
    );

    // angular PID controller
    lemlib::ControllerSettings angular_controller(2.1, // proportional gain (kP)
        0,   // integral gain (kI)
        14,  // derivative gain (kD)
        0,   // anti windup
        0.5, // small error range, in degrees
        100, // small error range timeout, in milliseconds
        2,   // large error range, in degrees
        500, // large error range timeout, in milliseconds
        0    // maximum acceleration (slew)
    );

    lemlib::ExpoDriveCurve throttle_curve(3,    // joystick deadband out of 127
    25,   // minimum output where drivetrain will move out of 127
    0.992 // expo curve gain
    );

    // input curve for steer input during driver control
    lemlib::ExpoDriveCurve steer_curve(3,   // joystick deadband out of 127
    17,  // minimum output where drivetrain will move out of 127
    1 // expo curve gain
    );

    lemlib::Chassis chassis(drivetrain, lateral_controller, angular_controller, odomRotational, &throttle_curve, &steer_curve);


} // namespace Globals
} // namespace Robot