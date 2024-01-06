#pragma once
#include <thread>
#include <iostream>
#include <random>
#include <mutex>

void DisplayInfo(std::string s);
int randRange(int, int);
void Pause(int start, int end);
class Order
{
    enum Dish { Pizza, Soup, Steak, Salad, Sushi, DCount };
    Dish dish;
public:
    Order();
    [[nodiscard]] std::string getTypeOrder() const;
};
void orderWait(Order* order);