#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <string>

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

    for (const std::string& token : tokens) {
        if (std::isdigit(token[0]) || (token[0] == '-' && token.length() > 1)) {
            stack.push(std::stoi(token));
        } else {
            if (stack.size() < 2) {
                std::cerr << "Error: No hay suficientes operandos para la operación '" << token << "'" << std::endl;
                return 0;
            }

            int a = stack.top();
            stack.pop();
            int b = stack.top();
            stack.pop();

            if (token == "+") {
                stack.push(b + a);
            } else if (token == "-") {
                stack.push(b - a);
            } else if (token == "*") {
                stack.push(b * a);
            } else if (token == "/") {
                if (a != 0) {
                    stack.push(b / a);
                } else {
                    std::cerr << "Error: División por cero" << std::endl;
                    return 0;
                }
            } else if (token == "^") {
                int result = 1;
                for (int i = 0; i < a; i++) {
                    result *= b;
                }
                stack.push(result);
            } else if (token == "%") {
                if (a != 0) {
                    stack.push(b % a);
                } else {
                    std::cerr << "Error: Módulo por cero" << std::endl;
                    return 0;
                }
            }
        }
    }

    if (stack.size() == 1) {
        return stack.top();
    } else {
        std::cerr << "Error: Operadores insuficientes" << std::endl;
        return 0;
    }
}

int main() {
    std::string input;
    std::getline(std::cin, input);
    Tokens tokens = tokenize(input);
    int result = evaluate(tokens);

    if (result != 0) {
        std::cout << "Resultado: " << result << std::endl;
        return 0;
    }

    return 1;
}
