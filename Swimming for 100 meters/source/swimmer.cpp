#include <swimmer.h>
#include <mutex>

std::mutex mu;

Swimmer::Swimmer(std::string inName, double inSpeed) : name(std::move(inName)), speed(inSpeed), time(100 / inSpeed)
{
    assert(speed > 0);
}

void Swimmer::sortSwimmers(Swimmer *sw[6])
{
    //bubble sort
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5 - i; j++)
        {
            if (sw[j]->time > sw[j + 1]->time)
            {
                //swapping
                Swimmer *tmp = sw[j];
                sw[j] = sw[j + 1];
                sw[j + 1] = tmp;
            }
        }
    }
}

void Swimmer::waitForSwim(const Swimmer *sw)
{
    for (int i = 1; i < sw->time / 1; ++i)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        mu.lock();
        std::cout << sw->name << " swam " << i * sw->speed << " meters\n";
        mu.unlock();
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    mu.lock();
    std::cout << sw->name << " swam 100 meters\n";
    mu.unlock();
}

std::string Swimmer::getName()
{
    return name;
}