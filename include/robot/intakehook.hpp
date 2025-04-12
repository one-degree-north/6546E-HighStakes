#pragma once

namespace Robot{

/**
 * @brief The Intake class represents a robot intake system.
 */
 class IntakeHook{
    public:
    /**
        * @brief Runs the main function of the intake system.
        *
        * Takes optional user input to control the direction of the intake system in
        * autonomous.
        */
        void run();

        IntakeHook();

    private:
        bool elevated;

    /**
        * @brief blue is false, red is true.
        */
        bool alliance_color;

 };
} // namespace Robot