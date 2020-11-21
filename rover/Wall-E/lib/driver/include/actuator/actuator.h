#pragma once

#include <Arduino.h>

namespace actuator
{
    /**
     * @brief Interface for actuator drivers.
     *
     */

    class Actuator
    {
       private:
       public:
        String actuator_name;
        bool connected;

        /**
         * @brief Construct a new Actuator object
         *
         * @param actuator_name
         */
        explicit Actuator(String actuator_name) : actuator_name(actuator_name) {}

        /**
         * @brief Destroy the Actuator object
         *
         */
        virtual ~Actuator() noexcept = default;

        /**
         * @brief Default copy constructor
         *
         */
        Actuator(const Actuator&) = default;

        /**
         * @brief Default implicit copy constructor
         *
         */
        Actuator(Actuator&&) = default;

        /**
         * @brief default copy assignment
         *
         * @return Actuator&
         */
        Actuator& operator=(const Actuator&) = default;

        /**
         * @brief default implicit copy assignment
         *
         * @return Actuator&
         */
        Actuator& operator=(Actuator&&) = default;

        /**
         * @brief Check the connection to the actuator. It will update the connected
         * variable whenever called.
         * @return true
         * @return false
         */
        virtual bool CheckConnection()
        {
            return false;
        }

        /**
         * @brief Activate the actuator pins. The pin numbers are in pin_assignment.h
         *
         */
        virtual void Attach() = 0;

        /**
         * @brief Update the motor input to Motor
         *
         */
        virtual void Update() = 0;

        /**
         * @brief Change PWM Input to the Motor
         */
        virtual void ChangeInput(int input) = 0;

        /**
         * @brief Print debug messages
         *
         */
        virtual void Debug(){};
    };
}  // namespace actuator
