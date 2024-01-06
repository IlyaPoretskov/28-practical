#include <swimmer.h>

int main()
{
    std::cout << "         <<Swimming dor 100 meters>>\n";

    Swimmer* swimmers[6];

    for (int i = 1; i < 7; ++i)
    {
        std::string name;
        double speed;

        std::cout << "Swimmer №" << i << ", input name and speed:\n";
        std::cin >> name >> speed;

        swimmers[i - 1] = new Swimmer(name, speed);
    }

    std::thread wait0(Swimmer::waitForSwim, swimmers[0]);
    std::thread wait1(Swimmer::waitForSwim, swimmers[1]);
    std::thread wait2(Swimmer::waitForSwim, swimmers[2]);
    std::thread wait3(Swimmer::waitForSwim, swimmers[3]);
    std::thread wait4(Swimmer::waitForSwim, swimmers[4]);
    std::thread wait5(Swimmer::waitForSwim, swimmers[5]);

    wait0.join();
    wait1.join();
    wait2.join();
    wait3.join();
    wait4.join();
    wait5.join();

    std::cout << "\n\nStatistics:\n";
    Swimmer::sortSwimmers(swimmers);

    for (int i = 1; i < 7; ++i)
        std::cout << i << " place: " << swimmers[i - 1]->getName() << std::endl;

    for (auto &swimmer: swimmers)
        delete swimmer;
}