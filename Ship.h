#ifndef SHIP_H
#define SHIP_H

#include <string>
#include <vector>

class Ship {
public:
	Ship(const std::string& name_);

	void inject_damage();
	void get_status();

	int get_letter()
	{return letter;}
	int get_hp()
	{return hp;}

private:
	std::vector<int> points;
	std::string name;
	int hp, length;
	char letter;
};

#endif