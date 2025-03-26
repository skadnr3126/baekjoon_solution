#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <queue>
#include <stack>
//#define DEBUG

int dir_x[4] = { -1,0,1,0 };
int dir_y[4] = { 0,-1,0,1 };
int visted[100][100];

int main() {
	int row, col;
	std::cin >> row >> col;
	//turning 1d arr to 2d arr
	int* temp_1d = new int[row * col];
	int** mirro = new int* [row];
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
	
	std::stack<std::pair<int, int>> node_stack;
	node_stack.push({ 0,0 });

	while (!node_stack.empty()){
		std::pair<int, int> current = node_stack.top();
		printf("go to col:%d, row:%d\n", current.second, current.first);
		node_stack.pop();

		for (int i = 0; i < 4; ++i) {
			int y = current.first + dir_y[i];
			int x = current.second + dir_x[i];
			if (y < 0 || x < 0 || y >= row || x >= col) {
				continue;
			}
			if (mirro[y][x] == 1 && visted[y][x] == 0) {
				node_stack.push({ y,x });	
				visted[y][x] = 1;
				
			}
			if (y == row - 1 && x == col - 1) {
				std::cout << "finding path success";
				return 0;
			}
		}
	}
	std::cout << "finding paht failed";


	return 0;
}