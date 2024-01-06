#include <kitchen.h>

std::mutex kitchen;
std::mutex courier;
std::mutex cou;

int randRange(int start, int end)
{
    return std::rand() % (end - start + 1) + start;
}

void Pause(int start, int end)
{
    std::this_thread::sleep_for(std::chrono::seconds(randRange(start, end)));
}

void DisplayInfo(std::string s)
{
    cou.lock();
    std::cout << s;
    cou.unlock();
}

std::string Order::getTypeOrder() const
{
    switch (dish)
    {
        case Pizza:  return "Pizza";
        case Soup:   return  "Soup";
        case Steak:  return "Steak";
        case Salad:  return "Salad";
        case Sushi:  return "Sushi";
        case DCount: break;
    }
    return "";
}

Order::Order()
{
    dish = (Dish)randRange(Pizza, Sushi);
}

void orderWait(Order *order)
{
    DisplayInfo("The order (" + order->getTypeOrder() + ") has been created\n");

    kitchen.lock();
    DisplayInfo("The order (" + order->getTypeOrder() + ") is accepted to the kitchen\n");
    Pause(5, 15);
    DisplayInfo("The order (" + order->getTypeOrder() + ") is ready\n");
    kitchen.unlock();

    courier.lock();
    DisplayInfo("The order (" + order->getTypeOrder() + ") is accepted by the courier\n");
    Pause(30, 30);
    DisplayInfo("The order (" + order->getTypeOrder() + ") is delivered\n");
    courier.unlock();
}
