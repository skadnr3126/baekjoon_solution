#include <iostream>
#include <vector>
#include <queue>
#include <set>
int board[100][100];
int dir_x[] = { 1,0,-1,0 };
int dir_y[] = { 0,1,0,-1 };
int r_c;
std::queue<std::pair<int, int>> sneak;
std::set<std::pair<int, int>> sneak_body;

bool is_collision(int head_row, int head_col) {
	if (sneak_body.count({ head_row, head_col })) { //if 1 then collision
		return true;
	}
	if (head_row >= r_c || head_row < 0 || head_col >= r_c || head_col < 0) { //head is over the limit
		return true;
	}
	return false;
}

bool move_end(int& sneak_row, int& sneak_col, int dir) {
	
	sneak_row = sneak_row + dir_y[dir];
	sneak_col = sneak_col + dir_x[dir];
	//std::cout << sneak_row << " " << sneak_col << std::endl;
	if (is_collision(sneak_row , sneak_col)) {
		return true;
	}

	sneak.push(std::make_pair(sneak_row, sneak_col));
	sneak_body.insert({ sneak_row, sneak_col });
	//std::cout << sneak_row << " " << sneak_col << std::endl;
	if (board[sneak_row][sneak_col] != 2) {//����ƴҶ�
		sneak_body.erase(sneak.front());
		sneak.pop();
	}
	else {
		board[sneak_row][sneak_col] = 0;
	}
	
	return false;
}

int main() {
	int apple_count, redir_count, i;
	int apple_row, apple_col;
	int sneak_row = 0, sneak_col = 0;
	int second;
	char rotation_dir;
	int end_time = 0;

	std::cin >> r_c >> apple_count;

	for (i = 0; i < apple_count; i++) {
		std::cin >> apple_row >> apple_col;
		board[apple_row - 1][apple_col - 1] = 2;
	}

	int dir = 0;
	board[0][0] = 1;
	sneak.push({ sneak_row ,sneak_col });
	sneak_body.insert({ sneak_row ,sneak_col });

	std::cin >> redir_count;
	std::vector<std::pair<int, char>> p_time_dir;
	int count = 0;
	for (i = 0; i < redir_count; ++i) {
		std::cin >> second >> rotation_dir;
		p_time_dir.push_back(std::make_pair(second, rotation_dir));
	}

	while (1) {
		end_time++;
		if (move_end(sneak_row, sneak_col, dir)) {
			std::cout << end_time;
			return 0;
		}

		if (count < p_time_dir.size()) {
			if (end_time == p_time_dir[count].first) {
				dir = (p_time_dir[count].second == 'L') ? (dir + 4 - 1) % 4 : (dir + 1) % 4;
				//std::cout << "changed dir" << dir << std::endl;
				count++;
			}
		}

	}
}