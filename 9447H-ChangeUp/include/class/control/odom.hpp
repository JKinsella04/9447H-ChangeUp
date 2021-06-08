#pragma once
#include "main.h"
#include "globals.hpp"

// #define circumference 8.635
#define CONVERSION 4169.079328314997
/*
Our Odometry Class was created with immense help from this article. The article has examples and pseudocode for most if not everything we have implemented here.
https://vinesmsuic.github.io/2020/09/29/robotics-purepersuit/#pure-pursuit-algorithm
*/

class Odom {
    public:

    /*
    Update global coordinates based off wheel movement and IMU heading.
    */
    static void updatePosition();


    private:

    static double global_x, global_y, distance, leftheading, rightheading, middleheading,averageheading, lValue, rValue;
    static double leftChange, rightChange, lastLPos, lastRPos;
};
