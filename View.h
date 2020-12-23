#ifndef VIEW_H
#define VIEW_H

#include <vector>

class View {
public:

	void draw_computer_board();
	void draw_player_board();

private:

	std::vector<std::vector<char>> computer_board, player_board;
};

#endif
