#pragma once

namespace Robot {

/**
 * @brief The Latch class represents a latching mechanism.
 */
class GoalStealer {
public:
   /**
    * @brief Runs sweeper
    */
   void run();

   /**
    * @brief Toggles sweeper state.
    */
   void toggle();

   GoalStealer();
};
} // namespace Robot