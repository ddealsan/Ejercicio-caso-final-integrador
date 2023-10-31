#include <iostream>
#include <stack>
#include <sstream>
#include <string>

// Función para verificar si un token es un operador
bool esOperador(const std::string& token) {
    return (token == "+" || token == "-" || token == "*" || token == "/");
}

int main() {
    std::stack<double> pila;

    while (true) {
        std::string expresion;
<<<<<<< HEAD
        std::cout << "Ingresa una expresion en notacion RPN (o 'salir' para finalizar): ";
=======
        std::cout << "Ingresa una expresión en notacion RPN (o 'salir' para finalizar): ";
>>>>>>> f850bb2 (Initial commit)
        std::getline(std::cin, expresion);

        if (expresion == "salir") {
            break;
        }

        std::istringstream stream(expresion);
        std::string token;

        while (stream >> token) {
            if (!esOperador(token)) {
                double numero;
                std::istringstream(token) >> numero;
                pila.push(numero);
            } else {
                if (pila.size() < 2) {
                    std::cout << "Error: no hay suficientes operandos para la operacion " << token << std::endl;
                    while (!pila.empty()) {
                        pila.pop();
                    }
                    break;
                }
                double operando2 = pila.top();
                pila.pop();
                double operando1 = pila.top();
                pila.pop();
                double resultado;

                if (token == "+") {
                    resultado = operando1 + operando2;
                } else if (token == "-") {
                    resultado = operando1 - operando2;
                } else if (token == "*") {
                    resultado = operando1 * operando2;
                } else if (token == "/") {
                    if (operando2 == 0) {
                        std::cout << "Error: division por cero" << std::endl;
                        while (!pila.empty()) {
                            pila.pop();
                        }
                        break;
                    }
                    resultado = operando1 / operando2;
                }

                pila.push(resultado);
            }
        }

        if (pila.size() == 1) {
            std::cout << "Resultado: " << pila.top() << std::endl;
            pila.pop();
        } else {
            std::cout << "Error: expresion mal formada" << std::endl;
        }
    }

    return 0;
}
