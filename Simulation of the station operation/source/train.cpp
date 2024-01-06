#include <train.h>

std::mutex station;

Train::Train(Train::Type inType, int inSeconds) : type(inType), seconds(inSeconds)
{
    assert(type >= A && type < TCount);
    assert(seconds > 0);
}

void Train::defineTrains(Train** pTrains)
{
    for (int i = A; i < TCount; ++i)
    {
        int tmpSeconds;

        std::cout << "Train " << getType(i) << ": input the time (in seconds):\n";
        std::cin >> tmpSeconds;

        pTrains[i] = new Train((Train::Type)i, tmpSeconds);
    }
}

void Train::waitForNext(Train* train)
{
    std::this_thread::sleep_for(std::chrono::seconds(train->seconds));

    if (!station.try_lock())
    {
        std::cout << "Train " << getType(train->type) << " is waiting for the free station\n";
        station.lock();
    }
    std::cout << "Train " << getType(train->type) << " has been arrived to the station\n";
    std::cout << "Please, enter \"depart\" for train " << getType(train->type) << " departing:\n";
    std::string tmp;
    std::cin >> tmp;

    while (tmp != "depart")
    {
        std::cerr << "Wrong input, try again\n";
        std::cin >> tmp;
    }
    std::cout << "Train " << getType(train->type) << " is departed from the station\n";
    station.unlock();
}

bool operator>(const Train &a, const Train &b)
{
    return a.seconds > b.seconds;
}

void Train::sortTrains(Train** pTrains)
{
    if ((*pTrains[0]) > (*pTrains[1])) Swap(&pTrains[0], &pTrains[1]);
    if ((*pTrains[1]) > (*pTrains[2])) Swap(&pTrains[1], &pTrains[2]);
    if ((*pTrains[0]) > (*pTrains[1])) Swap(&pTrains[0], &pTrains[1]);
}

[[nodiscard]] int Train::getSeconds() const
{
    return seconds;
}

char Train::getType(int n)
{
    return ((n == A) ? 'A' : (n == B) ? 'B' : 'C');
}

void Train::deleteTrains(Train **pTrains)
{
    for (int i = 0; i < 3; i++)
    {
        delete pTrains[i];
    }
}

template <typename T>

void Swap(T** a, T** b)
{
    T* tmp = *a;
    *a = *b;
    *b = tmp;
}