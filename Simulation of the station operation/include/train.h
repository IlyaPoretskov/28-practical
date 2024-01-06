#pragma once
#include <thread>
#include <mutex>
#include <iostream>
#include <cassert>

template <typename T>

void Swap(T** a, T** b);

class Train
{
    enum Type { A, B, C, TCount };

    int seconds;

    Type type; //A or B or C

public:

    Train(Type inType, int inSeconds);

    static void defineTrains(Train** pTrains);

    static void deleteTrains(Train** pTrains);

    static void waitForNext(Train* train);

    static void sortTrains(Train** pTrains);

    friend bool operator> (const Train& a, const Train& b);

    [[nodiscard]] int getSeconds() const;

    static char getType(int n);
};