#include <iostream>
#include <string>
#include <getopt.h>
#include "include/DFA.h"
#include "include/GramaticaRegular.h"

void ayuda() {
	std::cout << "Uso: dfa [-h|--help] [-i|--interactive] [-d|--dfa] automata.dfa [-g|--gramatica] gramatica.grammar\n" <<
		"\t[-h]               Muestra este menu.\n" <<
		"\t[-i|--interactive] Modo interactivo.\n" <<
		"\t[-d|--dfa]         DFA a introducir.\n" <<
		"\t[-g|--gramatica]   Gramática a introducir.\n";
}

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

void procesarArgumentos(int argc, char* argv[]) {

	bool mostrarAyuda = false, mostrarMenu = false;
	std::string ficheroAutomata, ficheroGramatica;

	const char* const opcionesCortas = "hid:g:";
	const option opcionesLargas[] = {
		{"help", no_argument, nullptr, 'h'},
		{"interactive", no_argument, nullptr, 'i'},
		{"dfa", required_argument, nullptr, 'd'},
		{"gramatica", required_argument, nullptr, 'g'},
		{nullptr, no_argument, nullptr, 0}
	};

	while (true) {
		const auto opciones = getopt_long(argc, argv, opcionesCortas, opcionesLargas, nullptr);

		if (opciones == -1) {
			break;
		}

		switch (opciones) {
			case 'i': {
			 	mostrarMenu = true;
				break;
			}
			case 'd': {
				ficheroAutomata = std::string(optarg);
				break;
			}
			case 'g': {
				ficheroGramatica = std::string(optarg);
				break;
			}
			case '?': {
				std::cout << "Argumento inválido\n";
			}
			case 'h':
			default: {
				mostrarAyuda = true;
				break;
			}
		}
	}

	// Implementar lógica de argumentos aquí
	if (mostrarAyuda) {
		ayuda();
	} else {
		if (!ficheroAutomata.empty() && !ficheroGramatica.empty()) {
			CyA::DFA dfa(ficheroAutomata);
			CyA::GramaticaRegular gramatica(dfa);

			gramatica.exportarGramatica(ficheroGramatica);
		} else {
			if (mostrarMenu) {
				menu();
			}
		}
	}

}

int main(int argc, char* argv[]) {
	procesarArgumentos(argc, argv);
}
