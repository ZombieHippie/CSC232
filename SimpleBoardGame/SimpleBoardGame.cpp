/*
Name: Cole Lawrence
Date: February 10th, 2015
Assignment: Asn3 "Dice Race!"
Platform/IDE: Windows 8/MVSP2013
Description:
This program demonstrates two players (Jack and Jill) moving along a line (in increments of 1 to 6).
If a player lands on another player's space that player is sent back 1 to 3 spaces.
Players win by getting to or past space 20.
*/

#include <iostream>
#include <string>
#include <vector>
#include <time.h>

class Player {
	std::string name;
	int wins;
	int position;
public:
	Player(std::string p_name) :
		name(p_name),
		position(1),
		wins(0)
	{
	};
	int getPosition() const
	{
		return position;
	};
	void setPosition(int p_position)
	{
		position = p_position;
	};
	void adjustPosition(int delta)
	{
		position += delta;
	};
	int getWins() const
	{
		return wins;
	};
	int setWins() const
	{
		return wins;
	};
	void adjustWins(int delta)
	{
		wins += delta;
	};
	std::string getName() const
	{
		return name;
	}
};

class DiceRace {
private:
	std::vector<Player> players;
	Player* winner;
	int total_players;
	bool has_winner;
	int winning_space;
	int dice_sides;
	int max_penalty_spaces;
	int min_penalty_spaces;
	int rollDice()
	{
		return std::rand() % dice_sides + 1;
	};
public:
	DiceRace(std::vector<Player> &p_players) :
		players(p_players),
		total_players(p_players.size()),
		has_winner(false),
		winning_space(20),
		dice_sides(6),
		max_penalty_spaces(3),
		min_penalty_spaces(1)
	{
	};
	Player& getWinner() const
	{
		return *winner;
	};
	std::vector<Player> getPlayers() const
	{
		return players;
	};
	void resetPositions() {
		for (int i = 0; i < total_players; ++i)
		{
			Player& player = players[i];
			player.setPosition(1);
		}
		has_winner = false;
	};
	void movePlayer(Player* player_ptr)
	{
		Player& current_player = *player_ptr;
		//cout << &current_player << " - test\n";
		int spaces_to_move = rollDice();
		current_player.adjustPosition(spaces_to_move);
		int player_space = current_player.getPosition();

		if (player_space >= winning_space)
		{
			has_winner = true;
			winner = &current_player;
		}
		else
		{
			std::vector<Player*> playersTumbled;
			// Iterate through other players
			for (int i = 0; i < total_players; ++i)
			{
				Player& other_player = players[i];
				if (&other_player == player_ptr)
					continue;

				if (player_space == other_player.getPosition())
				{
					// Player lands on other player's position
					int spaces_back = rand() % (max_penalty_spaces - min_penalty_spaces + 1) + min_penalty_spaces;
					other_player.adjustPosition(-1 * spaces_back);
					playersTumbled.push_back(&other_player);
				}
			}

			// Print
			std::cout << spaces_to_move << "\t";
			for (int i = 0; i < total_players; ++i)
			{
				Player& other_player = players[i];
				std::cout << other_player.getPosition() << "\t";
			};
			for (std::vector<Player*>::iterator it = playersTumbled.begin(); it < playersTumbled.end(); it++) {
				std::cout << "Tumble " << (**it).getName() << "!\t";
			}
				
			//cout << current_player.getName() << current_player.getPosition() << "  " << &current_player << " - test\n";
			std::cout << std::endl;
		}
	};
	void play()
	{
		// Print header
		std::cout << "Roll\t";
		for (int i = 0; i < total_players; ++i)
		{
			Player& other_player = players[i];
			std::cout << other_player.getName() << "\t";
		};
		std::cout << std::endl << std::string((total_players + 1) * 8, '-') << std::endl;

		int turn_index = -1;
		while (!has_winner)
		{
			turn_index = (turn_index + 1) % total_players;
			movePlayer(&players[turn_index]);
		}
	}
};

int main() {
	std::srand(time(NULL));

	bool hasReceivedValidInput;
	int games_count;
	do
	{
		std::cout << "Input an odd number of Dice Race! games to play: ";

		std::string games_count_input;
		std::cin >> games_count_input;
		try
		{
			games_count = std::stoi(games_count_input);
			hasReceivedValidInput = games_count % 2 == 1;
			if (!hasReceivedValidInput)
				std::cout << "Please specify an odd integer."<< std::endl;
		}
		catch (std::invalid_argument)
		{
			hasReceivedValidInput = false;
			std::cout << "Invalid integer: " << games_count_input << std::endl;
		}
	} while (!hasReceivedValidInput);

	std::cout << "Going to play " << games_count << " games" << std::endl;

	DiceRace game{ std::vector<Player> {
		/*
		Player("Rob"),
		Player("Tom"),
		Player("Juliet"),
		Player("Sam"),//*/
		Player("Jack"),
		Player("Jill")
	} };
	for (int count = 0; count < games_count; ++count)
	{
		game.play();
		Player& winner = game.getWinner();

		std::cout << winner.getName() << " has won!" << std::endl << std::endl;

		winner.adjustWins(1);

		// Reset players
		game.resetPositions();
	}

	Player *grandWinner = NULL;
	std::vector<Player> &players = game.getPlayers();
	for (int i = 0; i < players.size(); ++i)
	{
		Player& player = players[i];
		int gamesWon = player.getWins();

		if (grandWinner == NULL || (*grandWinner).getWins() < gamesWon)
			grandWinner = &player;

		std::cout << player.getName() << " won " << gamesWon << (gamesWon == 1 ? " game" : " games");

		if (i == players.size() - 2)
		{
			std::cout << ", and ";
		}
		else if (i < players.size() - 1)
		{
			std::cout << ", ";
		}
	}
	std::cout << "." << std::endl << std::endl;

	std::cout << "The grand winner of the Dice Race! games is " << (*grandWinner).getName();


	std::string a;
	std::cin >> a;
	return 0;
}
