#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, double> variables; // Un mapa que mapea nombres de variables a valores.

    while (true) {
        std::cout << "Ingrese una expresión (o 'quit' para salir): ";
        std::string input;
        std::getline(std::cin, input);

        if (input == "quit") {
            break;
        }

        // Dividir la entrada en nombre de variable y valor usando el signo igual.
        size_t pos = input.find('=');
        if (pos != std::string::npos) {
            std::string variable_name = input.substr(0, pos);
            std::string value_str = input.substr(pos + 1);
            try {
                double value = std::stod(value_str);
                variables[variable_name] = value;
                std::cout << "Variable " << variable_name << " definida con valor " << value << std::endl;
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error: Valor no válido para la variable " << variable_name << std::endl;
            }
        } else {
            std::cerr << "Error: Entrada no válida. Debe ser en el formato 'nombre = valor'." << std::endl;
        }
    }

    // Mostrar las variables definidas.
    std::cout << "Variables definidas:\n";
    for (const auto& pair : variables) {
        std::cout << pair.first << " = " << pair.second << std::endl;
    }

    return 0;
}
