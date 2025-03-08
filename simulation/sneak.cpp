#include <iostream>
#include <vector>
int board[100][100];
int dir_x[] = { 1,0,-1,0 }; 
int dir_y[] = { 0,1,0,-1 }; //좌표계에서는 밑으로가면 마이너스이지만, 배열에서는 플러스로 구현될 수 있다.
int r_c;
std::vector<std::pair<int,int>> sneak; //(행렬 가지고 있는 스네이크 vectir)

bool move_end(int& sneak_row ,int& sneak_col,int dir) {
	sneak_row = sneak_row + dir_y[dir];
	sneak_col = sneak_col + dir_x[dir];
	//std::cout << sneak_row << " " << sneak_col << std::endl;
	for (std::pair<int, int> i : sneak) {
		if (i.first == sneak_row  && i.second == sneak_col) {
			//std::cout << "self_block" << std::endl;
			return true;
		}
	}
	if (sneak_row >= r_c || sneak_row < 0 || sneak_col >= r_c || sneak_col < 0) {
		//std::cout << "block by limit" << std::endl;
		return true;
	}

	sneak.push_back(std::make_pair(sneak_row , sneak_col));

	//std::cout << sneak_row << " " << sneak_col << std::endl;
	if (board[sneak_row][sneak_col] != 2) {//사과아닐때
		sneak.assign(sneak.begin() + 1, sneak.end());
	}
	else {
		board[sneak_row][sneak_col] = 0;
	}
	return false;
}

int main() {
	int apple_count, redir_count,i;
	int apple_row, apple_col;
	int sneak_row = 0, sneak_col = 0;
	int second;
	char rotation_dir;
	int end_time = 0;

	std::cin >> r_c >> apple_count;
	
	for (i = 0; i < apple_count; i++) {
		std::cin >> apple_row >> apple_col;
		board[apple_row-1][apple_col-1] = 2;
	}
	
	int dir = 0;
	board[0][0] = 1;
	sneak.push_back({ sneak_row ,sneak_col });

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
			for (std::pair<int, int> i : sneak) {
				//std::cout << i.first << i.second;
			}
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