#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <map>

typedef std::vector<std::string> Tokens;

std::map<std::string, std::vector<std::string>> userFunctions;

Tokens tokenize(const std::string& input) {
    Tokens tokens;
    std::string token;
    std::istringstream stream(input);

    while (stream >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

int evaluate(Tokens& tokens);

int evalFunction(const std::string& functionName, std::vector<std::string>& parameters, Tokens& tokens) {
    std::map<std::string, int> argumentMap;

    for (const std::string& param : parameters) {
        int argValue = evaluate(tokens);
        argumentMap[param] = argValue;
    }

    while (!tokens.empty()) {
        int result = evaluate(tokens);
        return result; // Termina la función después de evaluar la expresión
    }

    return 0;
}

int evaluate(Tokens& tokens) {
    std::stack<int> stack;

    while (!tokens.empty()) {
        std::string token = tokens.back();
        tokens.pop_back();

        if (token == "define") {
            // Procesa la definición de una función
            std::string functionName = tokens.back();
            tokens.pop_back();
            std::vector<std::string> parameters;

            while (!tokens.empty() && tokens.back() != "(") {
                parameters.push_back(tokens.back());
                tokens.pop_back();
            }

            if (!tokens.empty() && tokens.back() == "(") {
                tokens.pop_back(); // Remove the "("
                userFunctions[functionName] = parameters;
            } else {
                std::cerr << "Error: Función incompleta" << std::endl;
            }
        } else if (userFunctions.find(token) != userFunctions.end()) {
            // Procesa una llamada de función
            std::vector<std::string> parameters = userFunctions[token];
            int result = evalFunction(token, parameters, tokens);
            stack.push(result);
        } else if (token == "+") {
            int a = stack.top();
            stack.pop();
            int b = stack.top();
            stack.pop();
            stack.push(a + b);
        } else if (token == "*") {
            int a = stack.top();
            stack.pop();
            int b = stack.top();
            stack.pop();
            stack.push(a * b);
        } else if (token == "if") {
            // Implementa el operador de control 'if' aquí
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
    std::cout << evaluate(tokens) << std::endl;
    return 0;
}