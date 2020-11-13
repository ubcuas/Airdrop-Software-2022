#pragma once

#include <Arduino.h>

namespace acuator
{
    /**
     * @brief Interface for acuator drivers.
     *
     */

    class Acuator
    {
       private:
        /**
         * @brief Disable default constructor. Will give compilation error is used.
         *
         */
        Acuator();

       public:
        String acuator_name;
        bool connected;
       
       /**
         * @brief Construct a new Sensor object
         *
         * @param acuator_name
         */
        Acuator(String sensor_name) : acuator_name(sensor_name) {}

        /**
         * @brief Destroy the Acuator object
         *
         */
        virtual ~Acuator() noexcept = default;

        /**
         * @brief Default copy constructor
         *
         */
        Acuator(const Acuator&) = default;

        /**
         * @brief Default implicit copy constructor
         *
         */
        Acuator(Acuator&&) = default;

        /**
         * @brief default copy assignment
         *
         * @return Acuator&
         */
        Acuator& operator=(const Acuator&) = default;

        /**
         * @brief default implicit copy assignment
         *
         * @return Acuator&
         */
        Acuator& operator=(Acuator&&) = default;

        /**
         * @brief Check the connection to the acuator. It will update the connected
         * variable whenever called.
         * @return true
         * @return false
         */
        virtual bool CheckConnection() = 0;

        /**
         * @brief Activate the acuator pins. The pin numbers are in pin_assignment.h
         *
         */
        virtual void Attach() = 0;

        /**
         *  @Brief Change PWM Input to the Motor
         */
        virtual void ChangeInput(int input) = 0; 
    };
}
