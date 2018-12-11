#include <iostream>
#include <string>
#include "include/DFA.h"

void menu() {
	unsigned int opcion;
	bool dfaIntroducido = false;
	CyA::DFA dfa;

	do {
		std::cout << "Autómata Finito Determinista -- CyA\n" <<
						     "1. Leer DFA.\n" <<
								 "2. Mostrar DFA.\n" <<
								 "3. Identificar estados de muerte\n" <<
								 "4. Analizar cadena.\n" <<
								 "5. Minimizar DFA.\n" <<
								 "6. Exportar DFA.\n" <<
								 "0. Salir del programa\n" <<
								 "\n" <<
								 "Introduce una opción: ";

		std::cin >> opcion;

		std::cout << '\n';

		switch (opcion) {
			case 0: {
				std::cout << "Fin del programa.\n";
				break;
			}

			case 1: {
				std::string rutaFichero;

				std::cout << "Introduce ruta al fichero: "; std::cin >> rutaFichero;
				dfa.leerFichero(rutaFichero);
				dfaIntroducido = true;
				break;
			}

			case 2: {
				if (dfaIntroducido) {
					std::cout << dfa << '\n';
				} else {
					std::cout << "Debes introducir un DFA primero.\n";
				}
				break;
			}

			case 3: {
				if (dfaIntroducido) {
					dfa.mostrarEstadosDeMuerte();
				} else {
					std::cout << "Debes introducir un DFA primero.\n";
				}
				break;
			}

			case 4: {
				if (dfaIntroducido) {
					std::string cadena;
					std::cout << "Introduce una cadena a analizar: "; std::cin >> cadena;
					dfa.analizarCadena(cadena);
				} else {
					std::cout << "Debes introducir un DFA primero.\n";
				}
				break;
			}

			case 5: {
				if (dfaIntroducido) {
					dfa.minimizarDFA();
				} else {
					std::cout << "Debes introducir un DFA primero.\n";
				}
				break;
			}

			case 6: {
				if (dfaIntroducido) {
					std::string ruta;
					std::cout << "Nombre del fichero a exportar: "; std::cin >> ruta;
					dfa.exportarDFA(ruta);
				} else {
					std::cout << "Debes introducir un DFA primero.\n";
				}
				break;
			}

			default: {
				std::cout << "Opción incorrecta o aún no implementada.\n";
				break;
			}
		}
		std::cout << '\n';
	} while (opcion != 0);
}

int main(int argc, char* argv[]) {
	menu();
}
