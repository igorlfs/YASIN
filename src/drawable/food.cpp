#include "food.hpp"
#include <random>
#include <vector>

// https://stackoverflow.com/a/13445752
int randomNumber(const int &f, const int &c) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(f, c);
    return dist(rng);
}

using std::pair;

using namespace drawable;
Food::Food(board::Board &board, const Snake &snake) {
    this->setChar(ch);
    this->spawn(board, snake);
}
void Food::spawn(board::Board &board, const Snake &snake) {
    std::vector<std::pair<int, int>> positions;
    for (int i = 1; i <= board.getY(); ++i)
        for (int j = 1; j <= board.getX(); ++j) {
            if (!snake.isInBody((pair{i, j})) && pair{i, j} != snake.getHead())
                positions.push_back(pair{i, j});
        }
    int index = randomNumber(0, positions.size() - 1);
    this->setHead(positions[index]);
}
