#include <iostream>
#include <stack>
#include <string>


int priority(char c) {
	if (c == '(' || c == ')') {
		return 0; // 0이여야 되는 이유는? 실제로 연산를 하지 않기떄문 잘 생가
	}
	else if (c == '*' || c == '/') {
		return 2;
	}
	else {
		return 1;
	}
}


std::stack<char> sign;


int main() {

	std::string input_expression, output_expression = "";
	
	std::cin >> input_expression;

	for (int i = 0; i < input_expression.size(); ++i) {
		char ch = input_expression[i];

		if ('A' <= ch && ch <= 'Z') {
			output_expression += ch;
			//std::cout << ch << std::endl;
		}
		else {
			if (sign.empty()) {
				sign.push(ch);
			}
			else if (ch == ')') {
				while (sign.top() != '(') {
					output_expression += sign.top();
					sign.pop();	
				}
				sign.pop();
			}
			else if (ch == '(') {
				sign.push(ch);
			}
			else if (priority(ch) >= priority(sign.top())) {
				sign.push(ch);
			}
			else {//low priorirty comes in, have to pop out a sign
				while (!sign.empty() && priority(ch) <= priority(sign.top())){
					output_expression += sign.top();
					sign.pop();
				}
				sign.push(ch);
			}
		}
	}

	while (!sign.empty()) {
		output_expression += sign.top();
		sign.pop();
	}
	std::cout << output_expression;
	
}