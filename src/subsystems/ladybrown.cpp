#include "robot/ladybrown.hpp"
#include "globals.hpp"
#include "lemlib/pid.hpp"
#include "lemlib/timer.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include <cstdlib>

using namespace Robot;
using namespace Robot::Globals;

LadyBrown::LadyBrown() : moveToPointPID(2, 0, 0, 2, false){
    ladyBrownRotational.set_position(0);
    LadyBrownMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void LadyBrown::run(bool async, int timeout){
    LADYBROWN_STATE move_to;

    // Bound to R2
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)){
        if (current_state == BASE_STATE){
            move_to = LOAD_STATE_ONE;
        } else if (current_state == LOAD_STATE_ONE){
            move_to = LOAD_STATE_TWO;
        } else if (current_state == LOAD_STATE_TWO){
            move_to = SCORE_STATE;
        } else if (current_state == SCORE_STATE){
            move_to = OFFENSE_STATE;
        }
    }
    std::cout << "Moving to: " << move_to << std::endl;
    std::cout << "Current State:  " << current_state << std::endl;

    if (!async){
        moveToPoint(move_to);
    } else {
        pros::Task move([move_to, this]() {
            moveToPoint(move_to);},
            "Ladybrown Move"
        );
    }

    if (!isPIDRunning){
        current_state = move_to;
    }
}

int LadyBrown::get_target(){
    return target;
}

void LadyBrown::moveToPoint(LadyBrown::LADYBROWN_STATE state, int max_error, int timeout){
    std::cout << "state: " << current_state << std::endl;
    std::cout << "state: " << current_state << std::endl;
    constexpr double base_location = 30;
    constexpr double load_location_1 = -2550;
    constexpr double load_location_2 = -3550;
    constexpr double score_location = -10000;
    constexpr double attack_location = -15500;

    int target;

    std::cout << "state: " << state << std::endl;
    std::cout << "pid: " << isPIDRunning << std::endl;

    if (!isPIDRunning){
        std::cout << "inner pid: " << isPIDRunning << std::endl;
        LadyBrown::isPIDRunning = true;
        switch (state) {
            case LADYBROWN_STATE::BASE_STATE:
                target = base_location;
                break;
            case LADYBROWN_STATE::LOAD_STATE_ONE:
                target = load_location_1;
                break;
            case LADYBROWN_STATE::LOAD_STATE_TWO:
                target = load_location_2;
                break;
            case LADYBROWN_STATE::SCORE_STATE:
                target = score_location;
                break;
            case LADYBROWN_STATE::OFFENSE_STATE:
                target = attack_location;
                break;
        }
    }

    std::cout << "target: " << target << std::endl;

    moveToPointPID.reset();

    lemlib::Timer timer(timeout);

    while (true){
        double error = target - ladyBrownRotational.get_position();
        double motor_voltage = moveToPointPID.update(error);

        // motor_voltage = lemlib::slew(motor_voltage, LadyBrownMotor.get_voltage(), 1500);

        if (std::abs(error) < max_error || timer.isDone()) {
            LadyBrownMotor.brake();
            LadyBrown::isPIDRunning = false;
            LadyBrown::current_state = state;
            break;
        }

        LadyBrownMotor.move_voltage(motor_voltage);
        LadyBrown::isPIDRunning = true;
        pros::delay(20);
      }
}
