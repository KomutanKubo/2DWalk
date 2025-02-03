#include <iostream>
#include <random>
#include <cmath>
using namespace std;

struct Location{
    int x,y;
};


double randomWalk(Location start, const Location& target, int sample, int steps) {
    int successCount = 0;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 3);

    for (int i = 0; i < sample; ++i) {
        Location current = start;


        for (int j = 0; j < steps; ++j) {
            int move = dist(gen);
            if (move == 0) current.x--;   // left
            else if (move == 1) current.x++;  // right
            else if (move == 2) current.y++;  // up
            else current.y--;  //down

            if (current.x == target.x && current.y == target.y) {
                successCount++;
                break;
            }
        }
    }
    return (double)successCount / sample;
}

double standartDeviation(double successRate, int sample){
    return sqrt((successRate * (1 - successRate)) / sample);
}

int main() {
    Location start = {0, 0};
    Location target = {2, 3};
    int sample = 200000;
    int steps = 800;

    double successRate = randomWalk(start, target, sample, steps);
    double standart_deviation = standartDeviation(successRate, sample);


    double z = 1.96;
    double lowerBound = successRate - z * standart_deviation;
    double upperBound = successRate + z * standart_deviation;

    cout <<"2D random walk with " << steps << " steps and " << sample << " sample" << endl;
    cout << "START: (" << start.x << "," << start.y << ") ----> DESTINATION: (" << target.x << "," << target.y <<")" << endl;
    cout << "Success rate: " << successRate * 100 << "%" << endl;
    cout << "Standard Error: " << standart_deviation * 100 << "%" << endl;
    cout << "95% Confidence Interval: (" << lowerBound * 100 << "%, " << upperBound * 100 << "%)" << endl;
}
