#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

// analog input button values                   //      PS      |       XBOX    |   SWITCH
#define GLFW_JOYSTICK_BTN_LEFT 0                //  Square      |   X           |   Y
#define GLFW_JOYSTICK_BTN_DOWN 1                //  X           |   A           |   B
#define GLFW_JOYSTICK_BTN_RIGHT 2               //  Circle      |   B           |   A
#define GLFW_JOYSTICK_BTN_UP 3                  //  Triangle    |   Y           |   X
#define GLFW_JOYSTICK_SHOULDER_LEFT 4           //  L1          |   LB          |   L
#define GLFW_JOYSTICK_SHOULDER_RIGHT 5          //  R1          |   RB          |   R
#define GLFW_JOYSTICK_TRIGGER_LEFT 6            //  L2          |   LT          |   ZL
#define GLFW_JOYSTICK_TRIGGER_RIGHT 7           //  R2          |   RT          |   ZR
#define GLFW_JOYSTICK_SELECT 8                  //  Share       |   Address     |   Minus
#define GLFW_JOYSTICK_START 9                   //  Options     |   Menu        |   Plus
#define GLFW_JOYSTICK_LEFT_STICK 10             //  L3          |   LS          |   Left
#define GLFW_JOYSTICK_RIGHT_STICK 11            //  R3          |   RS          |   Right
#define GLFW_JOYSTICK_HOME 12                   //  Home        |   Home        |   Home
#define GLFW_JOYSTICK_CLICK 13                  //  Touch pad   |   n/a         |   n/a
#define GLFW_JOYSTICK_DPAD_UP 14                //  Dpad up     |   Dpad up     |   Dpad up
#define GLFW_JOYSTICK_DPAD_RIGHT 15             //  Dpad right  |   Dpad right  |   Dpad right   
#define GLFW_JOYSTICK_DPAD_DOWN 16              //  Dpad down   |   Dpad down   |   Dpad down
#define GLFW_JOYSTICK_DPAD_LEFT 17              //  Dpad left   |   Dpad left   |   Dpad left
 
// axes
#define GLFW_JOYSTICK_AXES_LEFT_STICK_X     0
#define GLFW_JOYSTICK_AXES_LEFT_STICK_Y     1
#define GLFW_JOYSTICK_AXES_RIGHT_STICK_X    2
#define GLFW_JOYSTICK_AXES_LEFT_TRIGGER     3
#define GLFW_JOYSTICK_AXES_RIGHT_TRIGGER    4
#define GLFW_JOYSTICK_AXES_RIGHT_STICK_Y    5


class Joystick {
public:
    Joystick(int i);
    ~Joystick();

    // Similar to GLFW's Poll Events, but for the Joystick
    void update();

    // getters
    float axesState(int axis);
    unsigned char buttonState(int button);
    
    int getAxesCount();
    int getButtonCount();

    bool isPresent();
    const char* getName();

    static int getId(int i);


private:
    int present;

    int id;

    const char* name;

    int axesCount;
    const float* axes;

    int buttonCount;
    const unsigned char* buttons;
};