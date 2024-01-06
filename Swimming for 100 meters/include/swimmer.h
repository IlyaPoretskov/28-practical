#pragma once
#include <iostream>
#include <cassert>
#include <utility>
#include <thread>

class Swimmer
{
    std::string name;
    double speed, time;

public:

    Swimmer(std::string inName, double inSpeed);

    std::string getName();

    static void waitForSwim(const Swimmer *sw);

    static void sortSwimmers(Swimmer *sw[6]);
};