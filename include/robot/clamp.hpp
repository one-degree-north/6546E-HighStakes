#pragma once

namespace Robot {

/**
 * @brief The Latch class represents a latching mechanism.
 */
class Clamp {
public:
   /**
    * @brief Runs latching mechanism.
    */
   void run();

   Clamp();

   /**
    * @brief Toggles latch state.
    */
   void toggle();
};
} // namespace Robot