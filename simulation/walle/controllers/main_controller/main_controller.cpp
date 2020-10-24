// File:          main_controller.cpp
// Date:
// Description:
// Author:
// Modifications:

// You may need to add webots include files such as
// <webots/DistanceSensor.hpp>, <webots/Motor.hpp>, etc.
// and/or to add some other includes
#include <webots/Keyboard.hpp>
#include <webots/Motor.hpp>
#include <webots/Robot.hpp>
#include <webots/Supervisor.hpp>

// All the webots classes are defined in the "webots" namespace
using namespace webots;
using namespace std;
class Driver : public Supervisor
{
   public:
    Driver();
    void run();

   private:
    static void displayHelp();
    int timeStep;
    Keyboard *keyboard;
    double leftSpeed;
    double rightSpeed;
    Motor *leftMotor;
    Motor *rightMotor;
};

Driver::Driver()
{
    timeStep = 16;

    leftSpeed  = 0.0;
    rightSpeed = 0.0;

    leftMotor  = getMotor("left motor");
    rightMotor = getMotor("right motor");
    leftMotor->setPosition(INFINITY);
    rightMotor->setPosition(INFINITY);
    leftMotor->setVelocity(0.0);
    rightMotor->setVelocity(0.0);

    keyboard = getKeyboard();
    keyboard->enable(timeStep);
}

void Driver::run()
{
    displayHelp();

    // main loop
    while (step(timeStep) != -1)
    {
        switch (k)
        {
            case 'W':
                cout << "forward" << endl;
                leftSpeed += 0.1;
                rightSpeed += 0.1;
                break;
            case 'A':
                cout << "left" << endl;
                leftSpeed += 0.1;
                rightSpeed -= 0.1;
                break;
            case 'D':
                cout << "right" << endl;
                leftSpeed -= 0.1;
                rightSpeed += 0.1;
                break;
            case 'S':
                cout << "back" << endl;
                leftSpeed -= 0.1;
                rightSpeed -= 0.1;
                break;
            case 'Q':
                cout << "stop" << endl;
                leftSpeed  = 0;
                rightSpeed = 0;
                break;
            default:
                break;
        }
        leftMotor->setVelocity(leftSpeed);
        rightMotor->setVelocity(rightSpeed);
    }
}

void Driver::displayHelp()
{
    string s(
        "Commands (One key at a time):\n"
        " W for Forward\n"
        " A for Left Turn\n"
        " D for Right Turn\n"
        " S for Backward\n"
        " Q for Full Stop");
    cout << s << endl;
}

// This is the main program of your controller.
// It creates an instance of your Robot instance, launches its
// function(s) and destroys it at the end of the execution.
// Note that only one instance of Robot should be created in
// a controller program.
// The arguments of the main function can be specified by the
// "controllerArgs" field of the Robot node
int main(int argc, char **argv)
{
    Driver *controller = new Driver();
    controller->run();
    delete controller;
    return 0;
}
