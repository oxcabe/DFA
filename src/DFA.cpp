#include "../include/DFA.h"


namespace CyA {

DFA::DFA(std::string& rutaFichero) {

  leerFichero(rutaFichero);

}

void DFA::leerFichero(std::string& rutaFichero) {
  std::ifstream fichero;

  try {
    fichero.open(rutaFichero);

    if (fichero.is_open()) {

      unsigned int numEstados;

      fichero >> numEstados;
      fichero >> arranque_;

      if (fichero.peek() != '\n' && fichero.peek() != 13) {
        throw 2;
      }

      for (unsigned int i = 0; i < numEstados; ++i) {
        unsigned int id, aceptacion, numTransiciones;
        fichero >> id;
        fichero >> aceptacion;
        fichero >> numTransiciones;

        Estado estado(id, aceptacion, numTransiciones);
        std::set<std::string> alfabeto;

        for (unsigned int j = 0; j < numTransiciones; ++j) {
          std::string simbolo;
          unsigned int destino;

          fichero >> simbolo;
          fichero >> destino;

          if (!alfabeto.count(simbolo)) {
            alfabeto.insert(simbolo);
            estado.addTransicion(simbolo, destino);
          } else {
            throw 3;
          }

        }
        estados_.insert(estado);
      }
    } else {
      throw 1;
    }

  } catch (int e) {
    std::cout << "Fallo en la síntesis del fichero: " << e << "\n";
    estados_.clear();
  }
  fichero.close();
}

void DFA::mostrarEstadosDeMuerte() {

  bool hayEstadosDeMuerte = false;

  for (auto& estado : estados_) {
    if (estado.esEstadoDeAceptacion()) {
      if (!hayEstadosDeMuerte) {
        std::cout << "[+] Hay estado/s de muerte: \n";
        hayEstadosDeMuerte = true;
      }

      std::cout << "[*] Estado de muerte en: q" << estado.getId() << '\n';

    }
  }

  if (!hayEstadosDeMuerte) {
    std::cout << "[-] No hay estados de muerte.\n";
  }

}

void DFA::analizarCadena(std::string& cadena) {

  std::cout << "Cadena de entrada: " << cadena << '\n';

  auto iterSetEstado = std::next(estados_.begin(), arranque_);

  std::cout << "Estado actual    Entrada    Siguiente estado    Aceptación\n";

  for (char cadenaChar : cadena) {
    std::string cadenaString(1, cadenaChar);

    std::cout << (*iterSetEstado).getId() <<
      "                " << cadenaString <<
      "                ";

    iterSetEstado = std::next(estados_.begin(),
      (*iterSetEstado).nextTransicion(cadenaString));

    std::cout << (*iterSetEstado).getId() << "                ";
    std::cout << (((*iterSetEstado).esEstadoDeAceptacion()) ? "SI\n" : "NO\n");
  }

  std::cout << (((*iterSetEstado).esEstadoDeAceptacion()) ? "CADENA ACEPTADA\n" :
   "CADENA NO ACEPTADA\n");

}

void DFA::imprimir(std::ostream& salida) const {
  std::cout << estados_.size() << '\n' <<
               arranque_ << '\n';

  for (auto& estado : estados_) {
    std::cout << estado << '\n';
  }
}

}

std::ostream& operator<<(std::ostream& salida, const CyA::DFA& dfa) {
  dfa.imprimir(salida);
  return salida;
}
