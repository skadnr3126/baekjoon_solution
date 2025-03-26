#include <iostream>
#include <stack>
#include <string>

//#define DEBUG

void print_stack(std::stack<double> &my_stack) {
	while (!my_stack.empty()) {
		std::cout << my_stack.top();
		my_stack.pop();
	}
	
}
int main() {
	int n; //피연잔사의개수 a~z까지
	std::string expreesion; //후위표기법으로 나타낸 식

	std::cin >> n;
	std::cin >> expreesion;

	std::stack<double> my_stack;
	int map_arr[26]; //각 알파벳에 대응되는 값
	for (int i = 0; i < n; ++i) {
		int temp;
		std::cin >> temp;
		map_arr[i] = temp;
	}
#ifdef DEBUG
	for (int i = 0; i < n; ++i) {
		std::cout << map_arr[i];
}
#endif // DEBUG

	double result = 0;
	for (int i = 0; i < expreesion.size(); ++i) {
		char ch = expreesion[i];
		if ('A' <= ch && ch <= 'Z') {
			double data = map_arr[ch - 'A'];
			my_stack.push(data);
			//printf("pushed data %f", my_stack.top());
		}
		else {
			double b = my_stack.top();
			my_stack.pop();
			double a = my_stack.top();
			my_stack.pop();
			switch (ch) {
			case '*':
				result = a * b;
				//printf("result %f a %f b %f\n", result, a, b);
				break;

			case '+':
				result = a + b;
				//printf("result %f a %f b %f\n", result, a, b);
				break;

			case '/':
				result = a / b;
				//printf("result %f a %f b %f\n", result, a, b);
				break;

			case '-':
				result = a - b;
				//printf("result %f a %f b %f\n", result, a, b);
				break;
			}
			my_stack.push(result);
		}
		
	}
	printf("%0.2f", my_stack.top());

}
