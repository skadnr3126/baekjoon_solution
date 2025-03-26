#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <queue>
//#define DEBUG


int dir_x[4] = { 1,0,-1, 0 };
int dir_y[4] = { 0,1, 0,-1 };

std::vector<std::pair<int,int>> mirro_grape[100][100];
int visted[100][100];

void BFS(int start_row, int start_col,int end_row, int end_col) {
	std::pair<int, int> parent_n;
	std::pair<int, int> child_n;
	std::queue< std::pair<int, int >> node_q;
	std::queue<int> deepness_q;
	node_q.push({ start_row, start_col });
	deepness_q.push(1);
	visted[start_row][start_col] = 1;
	while (!node_q.empty()) {

		//std::cout << deepness++ << std::endl;
		parent_n = node_q.front();

		for (int i = 0; i < mirro_grape[parent_n.first][parent_n.second].size(); ++i) {
			child_n = mirro_grape[parent_n.first][parent_n.second][i];
			if (!visted[child_n.first][child_n.second]) {
				node_q.push(child_n);
				deepness_q.push(deepness_q.front() + 1);
				visted[child_n.first][child_n.second] = 1;
				if (child_n.first == end_row && child_n.second == end_col) {
					std::cout << deepness_q.back();
					//printf("child_N : %d,%ddeepness is %d\n",child_n.first , child_n.second, deepness_q.back());
				}
				//printf("serach %d,%d\n", child_n.first, child_n.second);
			}
		}
		node_q.pop(); //parents node out;
		deepness_q.pop();
	}
}
int main() {
	int row, col;
	std::cin >> row >> col;
	//turning 1d arr to 2d arr
	int* temp_1d = new int[row * col];
	int** mirro = new int*[row];
	for (int i = 0; i < row; ++i) {
		mirro[i] = temp_1d + i * col;
	}

	//mirro input
	std::string one_row;
	for (int i = 0; i < row; ++i) {
		std::cin >> one_row;
		for (int j = 0; j < col; ++j) {
			mirro[i][j] = one_row[j] - '0';
#ifdef DEBUG
			printf("%d , %d = %d\n", i, j, mirro[i][j]);
#endif // DEBUG
		}
	}

	//init grape
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			for (int k= 0; k < 4; ++k) {
				int x = j+ dir_x[k];
				int y = i +dir_y[k];
				//printf("x : %d y: %d\n", x, y);
				if (x < 0 || y < 0 || x >=col || y >=row) {
					continue;
				}
				if (mirro[y][x] == 1) {
					mirro_grape[i][j].push_back({ y,x });
					//printf("%d,%d add node %d,%d\n", i, j, y, x);
				}
			}
		}
	}
	BFS(0, 0, row-1,col-1);





	


	return 0;
}