#pragma once

#include <Arduino.h>

namespace sensor
{
    /**
     * @brief Interface for sensor drivers.
     *
     */
    class Sensor
    {
       private:
       public:
        String sensor_name;
        bool connected;

        /**
         * @brief Construct a new Sensor object
         *
         * @param sensor_name
         */
        explicit Sensor(String sensor_name) : sensor_name(sensor_name) {}

        // default operators: https://en.cppreference.com/w/cpp/language/rule_of_three

        /**
         * @brief Destroy the Sensor object
         *
         */
        virtual ~Sensor() noexcept = default;

        /**
         * @brief Default copy constructor
         *
         */
        Sensor(const Sensor&) = default;

        /**
         * @brief Default implicit copy constructor
         *
         */
        Sensor(Sensor&&) = default;

        /**
         * @brief default copy assignment
         *
         * @return Sensor&
         */
        Sensor& operator=(const Sensor&) = default;

        /**
         * @brief default implicit copy assignment
         *
         * @return Sensor&
         */
        Sensor& operator=(Sensor&&) = default;

        /**
         * @brief Check the connection to the sensor. It will update the connected
         * variable whenever called.
         * @return true
         * @return false
         */
        virtual bool CheckConnection() = 0;

        /**
         * @brief Activate the sensor pins. The pin number should be in pin_assignment.h
         *
         */
        virtual void Attach() = 0;

        /**
         * @brief Update the sensor data upon calling.
         *
         */
        virtual void Update() = 0;

        /**
         * @brief Calibrate the sensor upon calling. It's optional
         *
         * @return true
         * @return false
         */
        virtual bool Calibrate()
        {
            return false;
        }

        /**
         * @brief Stop the sensor upon calling. It's optional
         *
         * @return true
         * @return false
         */
        virtual bool Stop()
        {
            return false;
        }

        /**
         * @brief serial print the debug related
         *
         */
        virtual void Debug() = 0;
    };
}  // namespace sensor
