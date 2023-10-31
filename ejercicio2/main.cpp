#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <map>
#include <functional>

typedef std::vector<std::string> Tokens;

std::map<std::string, std::function<int(std::vector<int>)>> operations = {
        {"+", [](std::vector<int> args) {
            int result = 0;
            for (int num : args) {
                result += num;
            }
            return result;
        }},
        {"*", [](std::vector<int> args) {
            int result = 1;
            for (int num : args) {
                result *= num;
            }
            return result;
        }},
        {"min", [](std::vector<int> args) {
            if (args.empty()) return 0;
            int min_val = args[0];
            for (int num : args) {
                if (num < min_val) min_val = num;
            }
            return min_val;
        }},
        {"max", [](std::vector<int> args) {
            if (args.empty()) return 0;
            int max_val = args[0];
            for (int num : args) {
                if (num > max_val) max_val = num;
            }
            return max_val;
        }}
};

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
        if (operations.find(token) != operations.end()) {
            std::function<int(std::vector<int>)> operation = operations[token];

            std::vector<int> args;

            while (!stack.empty()) {
                args.push_back(stack.top());
                stack.pop();
            }


            int result = operation(args);
            stack.push(result);
        } else {
            stack.push(std::stoi(token));
        }
    }

    if (stack.size() != 1) {
        std::cerr << "Error: Expresión mal formada" << std::endl;
        return 0;
    }

    return stack.top();
}

int main() {
    std::string input;
    std::getline(std::cin, input);
    Tokens tokens = tokenize(input);
    int result = evaluate(tokens);
    std::cout << "Resultado: " << result << std::endl;
    return 0;
}