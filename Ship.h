#ifndef SHIP_H
#define SHIP_H

#include <string>
#include <vector>
#include <utility>

class Ship {
public:
	Ship();
	Ship(const std::string& name_);

	void inject_damage(int row, int col);
	void get_status();
	void assign_points(std::vector<std::pair<int, int>>& points);
	bool is_hit(int row, int prev);

	int get_letter()
	{return letter;}
	int get_hp()
	{return hp;}

private:
	std::vector<std::pair<int, int>> points;
	std::vector<bool> hit;
	std::string name;
	int hp, length;
	char letter;
};

#endif