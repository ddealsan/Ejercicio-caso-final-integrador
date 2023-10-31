#include <iostream>
#include <sstream>
#include <stack>
#include <vector>

typedef std::vector<std::string> Tokens;

Tokens tokenize(const std::string& input) {
    Tokens tokens;
    std::string token;
    std::istringstream stream(input);

    while (stream >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

int evaluate(Tokens& tokens) {
    std::stack<int> stack;

    while (!tokens.empty()) {
        std::string token = tokens.back();
        tokens.pop_back();

        if (token == "+") {
            int a = stack.top();
            stack.pop();
            int b = stack.top();
            stack.pop();
            stack.push(b + a);
        } else if (token == "-") {
            int a = stack.top();
            stack.pop();
            int b = stack.top();
            stack.pop();
            stack.push(b - a);
        } else if (token == "*") {
            int a = stack.top();
            stack.pop();
            int b = stack.top();
            stack.pop();
            stack.push(b * a);
        } else if (token == "/") {
            int a = stack.top();
            stack.pop();
            int b = stack.top();
            stack.pop();
            if (a != 0) {
                stack.push(b / a);
            } else {
                std::cerr << "Error: División por cero" << std::endl;
                return 0;
            }
        } else {
            stack.push(std::stoi(token));
        }
    }

    return stack.top();
}

int main() {
    std::string input;
    std::getline(std::cin, input);
    Tokens tokens = tokenize(input);
    int result = evaluate(tokens);

    if (!tokens.empty()) {
        std::cerr << "Error: Entrada inválida" << std::endl;
        return 1;
    }

    std::cout << "Resultado: " << result << std::endl;
    return 0;

}
