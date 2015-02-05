
//using namespace std;
#include <vector>
#include <string>

class GameBoard {
    std::vector<std::string> players;
    int total_players;
public:
    GameBoard (const std::vector<std::string> & p_players):
        players(p_players),
        total_players(p_players.size())
    {
    }
};

int main()
{
    std::vector<std::string> players{"jill", "bill"}; //if C++11 is not available you can use push_back()
    GameBoard b{players};
    return 0;
}
