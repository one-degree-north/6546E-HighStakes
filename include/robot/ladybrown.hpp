#pragma once

#include "lemlib/pid.hpp"

namespace Robot {
/**
 * @brief The LadyBrown class represents the robot lady brown subsystem.
 */
 class LadyBrown {
    public:
       // The ENUM associates with each location of the rotation sensor for the LadyBrown to move.
        enum LADYBROWN_STATE {
            BASE_STATE = 1,
            LOAD_STATE_ONE = 2,
            LOAD_STATE_TWO = 3,
            SCORE_STATE = 4,
            OFFENSE_STATE = 5
        };

        void run(bool async = true, int timeout = 1000);

        void moveToPoint(LadyBrown::LADYBROWN_STATE state, int max_error = 150, int timeout = 1000);

        LadyBrown();

        int get_target();
    
    private:
        lemlib::PID moveToPointPID;

        static LADYBROWN_STATE current_state;

        int target;

        bool isPIDRunning;
};
} // namespace Robot
