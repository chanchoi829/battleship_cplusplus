#ifndef SHIP_H
#define SHIP_H

#include <string>
#include <vector>
#include <utility>

class Ship {
public:
	enum class Ship_type {
		Unknown,
		Destroyer,
		Submarine,
		Cruiser,
		Battleship,
		Carrier,
	};

	Ship();
	Ship(Ship::Ship_type s);

	void inject_damage(int row, int col);
	void get_status();
	void assign_points(std::vector<std::pair<int, int>>& points);
	bool is_hit(int row, int prev);
	void reset_recently_sunk();

	int get_letter();
	int get_hp();
	int get_length();
	bool get_recently_sunk();
	std::vector<std::pair<int, int>>& get_points();

private:
	std::vector<std::pair<int, int>> points;
	std::vector<bool> hit;
	std::string name;
	int hp, length;
	char letter;
	bool recently_sunk;
};

#endif