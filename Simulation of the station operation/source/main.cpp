#include <train.h>

Train* trains[3];

int main()
{
    std::cout << "            <<Simulation of the station operation>>" << std::endl;
    Train::defineTrains(trains);
    //Train::sortTrains(trains);

    std::thread wait0(Train::waitForNext, trains[0]);
    std::thread wait1(Train::waitForNext, trains[1]);
    std::thread wait2(Train::waitForNext, trains[2]);

    wait0.join();
    wait1.join();
    wait2.join();

    Train::deleteTrains(trains);
    system("pause");
    return 0;
}