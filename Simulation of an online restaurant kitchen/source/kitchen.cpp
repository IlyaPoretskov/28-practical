#include <kitchen.h>
#define DEBUG 1

std::mutex mKitchen;
std::mutex mCourier;
std::mutex cou;
std::queue<Order*> qR;
std::queue<Order*> qK;

int randRange(int start, int end)
{
    std::srand(std::time(nullptr));
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
        case DCount: return "Finished!";
    }
    return "";
}

Order::Order()
{
    dish = (Dish)randRange(Pizza, Sushi);
}

bool Order::isFinish() const { return dish == DCount; }

void kitchenWait()
{
    for(;;) {
        if (!qR.empty()) {
            mKitchen.lock();
            Order *order = qR.front();
            qR.pop();
            mKitchen.unlock();
            if (order->isFinish()) {
                mCourier.lock();
                qK.push(order);
                mCourier.unlock();
                return;
            }
            DisplayInfo("The order (" + order->getTypeOrder() + ") is accepted to the kitchen\n");

            Pause(5, 15);

            DisplayInfo("The order (" + order->getTypeOrder() + ") is ready\n");
            mCourier.lock();
            qK.push(order);
            mCourier.unlock();
        } else {
            Pause(1, 1);
        }
    }
}

void courierWait()
{
    for(;;) {
        if (!qK.empty()) {
            mCourier.lock();
            Order *order = qK.front();
            qK.pop();
            mCourier.unlock();

            if (order->isFinish()) return;
            DisplayInfo("The order (" + order->getTypeOrder() + ") is accepted by the courier\n");

            Pause(30, 30);

            DisplayInfo("The order (" + order->getTypeOrder() + ") is delivered\n");

        } else {
            Pause(1, 1);
        }
    }
}

void runKitchen() {
    Order* orders[10];

    std::thread kitchen(kitchenWait);
    std::thread courier(courierWait);

    for (auto order : orders)
    {
        order = new Order();
        DisplayInfo("The order (" + order->getTypeOrder() + ") has been created\n");
        mKitchen.lock();
        qR.push(order);
        mKitchen.unlock();

        Pause(5, 10);
    }

    Order orderFinish;
    orderFinish.setFinish();
    mKitchen.lock();
    qR.push(&orderFinish);
    mKitchen.unlock();

    kitchen.join();
    courier.join();

#if !DEBUG

    for (auto order : orders) {
        delete order;
    }
#endif
}
