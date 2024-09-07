#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

class Mouse{
public:

    static void cursorPosCallback(GLFWwindow* window, double _x, double _y);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void mouseWheelCallback(GLFWwindow* window, double dx, double dy);


    // getters
    static double getMouseX();
    static double getMouseY();
    
    static double getDX();
    static double getDY();

    static double getScrollDX();
    static double getScrollDY();

    static bool button(int button);
    static bool buttonChanged(int button);

    static bool buttonWentUp(int button);
    static bool buttonWentDown(int button);

private:

    static double x;
    static double y;
    
    static double lastX;
    static double lastY;
    
    static double dx;
    static double dy;

    static double scrollDX;
    static double scrollDY;

    static bool firstMouse;
    
    static bool buttons[];
    static bool buttonsChanged[];

};