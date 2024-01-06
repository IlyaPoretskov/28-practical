#include <kitchen.h>

int main()
{
    std::cout << "            <<Simulation_of_an_online_restaurant_kitchen>>\n";

    Order orders[10];
    std::thread* orderW[10];

    for (int i = 0; i < 10; i++)
    {
        orderW[i] = new std::thread(orderWait, &orders[i]);
        Pause(5, 10);
    }

    for (auto & i : orderW) {
        i->join();
    }
    for (auto & i : orderW) {
        delete i;
    }
}
