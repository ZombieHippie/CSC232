/*
Name: Cole Lawrence
Date: January 27th, 2015
Assignment: Asn2 "Dice Race!"
Platform/IDE: Windows 8/Dev-C++

Description:
2-4 sentence summary of what the program does.
*/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <time.h>

using namespace std;

class Player {
		string name;
		int position;
	public:
		Player (string p_name):
			name(p_name),
			position(1)
		{
		};
		int move (int diff) {
			this->position = diff + position;
			return position;
		};
		int get_position () { return position; };
		string get_name () { return name; }
};

class GameBoard {
	private:
		vector<Player> players;
		int total_players;
		int turn_index;
		bool has_winner;
		int winning_space;
	public:
		GameBoard (vector<Player> & p_players):
			players(p_players),
			total_players(p_players.size()),
			turn_index(0),
			has_winner(false),
			winning_space(20)
		{
		};
		bool get_has_winner () { return has_winner; };
		Player get_last_player () { return players[turn_index]; };
		void move_next_player () {
			Player current_player = players[turn_index];
			//cout << &current_player << " - test\n";
			int player_space = current_player.move(1);
			if (player_space >= winning_space) {
				has_winner = true;
			} else {
				cout << current_player.get_name() << current_player.get_position() << "  " << &current_player << " - test\n";
			}
			turn_index = (turn_index + 1) % total_players;
		}
};

int main () {
	srand(time(NULL));
	
	vector<Player> players {
		Player("Jack"),
		Player("Jill")
	};
	
	cout << &players[0];
	cout << &players[1];
	
	GameBoard game{players};
	
	while (game.get_has_winner() != true) {
		game.move_next_player();
	}
	
	Player winner = game.get_last_player();

	cout << winner.get_name() << " has won!\n";

	//delete[] &players;
	//delete &game;
	return 0;
}
