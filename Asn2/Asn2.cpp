/*
Name: Cole Lawrence
Date: January 27th, 2015
Assignment: Asn2 "Dice Race!"
Platform/IDE: Windows 8/Dev-C++

Description:
This program demonstrates two players (Jack and Jill) moving along a line (in increments of 1 to 6).
If a player lands on another player's space that player is sent back 1 to 3 spaces.
Players win by getting to or past space 20.
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
			position = diff + position;
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
		int dice_sides;
		int max_penalty_spaces;
		int min_penalty_spaces;
		int roll_dice () { return rand() % dice_sides + 1; };
	public:
		GameBoard (vector<Player> & p_players):
			players(p_players),
			total_players(p_players.size()),
			turn_index(-1),
			has_winner(false),
			winning_space(20),
			dice_sides(6),
			max_penalty_spaces(3),
			min_penalty_spaces(1)
		{
		};
		bool get_has_winner () { return has_winner; };
		Player get_last_player () { return players[turn_index]; };
		void move_next_player () {
			turn_index = (turn_index + 1) % total_players;
			Player& current_player = players[turn_index];
			//cout << &current_player << " - test\n";
			int spaces_to_move = roll_dice();
			int player_space = current_player.move(spaces_to_move);
			cout << current_player.get_name() << " moved forward " << spaces_to_move << " spaces to space: " << player_space << ".\n";
			if (player_space >= winning_space) {
				has_winner = true;
			} else {
				// Iterate through other players
				for (int i = 1; i < total_players; ++i) {
					Player& other_player = players[(turn_index + i) % total_players];
					if (player_space == other_player.get_position()) {
						// Player lands on other player's position
						int spaces_back = rand() % (max_penalty_spaces - min_penalty_spaces + 1) + min_penalty_spaces;
						other_player.move(-1 * spaces_back);
						cout << current_player.get_name() << " landed on " << other_player.get_name() << "'s space, causing ";
						cout << other_player.get_name() << " to take a tumble and move backwards " << spaces_back << " spaces.\n";
					}
				}
				//cout << current_player.get_name() << current_player.get_position() << "  " << &current_player << " - test\n";
			}
		}
};

int main () {
	srand(time(NULL));
	
	vector<Player> players {
		/*
		Player("Rob"),
		Player("Tom"),
		Player("Juliet"),
		Player("Sam"),//*/
		Player("Jack"),
		Player("Jill")
	};
	
	
	GameBoard game{players};
	
	while (game.get_has_winner() != true) {
		game.move_next_player();
	}

	cout << game.get_last_player().get_name() << " has won!\n";

	return 0;
}
