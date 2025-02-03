#include <iostream>
#include <random>
using namespace std;

struct Location{
    int x,y;
};


double randomWalk(Location start, const Location& target, int sample, int sets) {
    int successCount = 0;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 3);

    for (int i = 0; i < sample; ++i) {
        Location current = start;


        for (int j = 0; j < sets; ++j) {
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

int main() {
    Location start = {0, 0};
    Location target = {2, 3};
    int sample = 100000;
    int sets = 100;

    double successRate = randomWalk(start, target, sample, sets);
    cout << "Success rate: " << successRate * 100 << "%" << endl;
    return 0;
}
