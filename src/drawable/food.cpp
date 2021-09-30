#include "food.hpp"
#include <random>
#include <vector>

// https://stackoverflow.com/a/13445752
namespace std {
int randomNumber(const int &floor, const int &ceiling) {
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist(floor, ceiling);
    return dist(rng);
}
} // namespace std

using namespace drawable;
Food::Food(board::Board &board, const Snake &snake) {
    this->setChar(ch);
    this->spawn(board, snake);
}
void Food::spawn(board::Board &board, const Snake &snake) {
    std::vector<std::pair<int, int>> positions;
    for (int i = 1; i <= board.getY(); ++i)
        for (int j = 1; j <= board.getX(); ++j) {
            std::pair<int, int> pair = {i, j};
            if (!snake.isInBody(pair) && pair != snake.getHead())
                positions.push_back(pair);
        }
    int index = std::randomNumber(0, positions.size() - 1);
    this->setHead(positions[index]);
}
void Food::print(const board::Board &board) const {
    board.print(this->getHead(), this->getChar());
}
