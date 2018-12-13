#include "../include/DFA.h"


namespace CyA {

DFA::DFA(std::string& rutaFichero) {

  leerFichero(rutaFichero);

}

void DFA::leerFichero(std::string& rutaFichero) {
  estados_.clear();
  alfabeto_.clear();
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

        Estado estado(id, aceptacion);
        std::set<std::string> alfabeto;

        for (unsigned int j = 0; j < numTransiciones; ++j) {
          std::string simbolo;
          unsigned int destino;

          fichero >> simbolo;
          fichero >> destino;

          if (!alfabeto.count(simbolo)) {
            alfabeto.insert(simbolo);
            alfabeto_.insert(simbolo);
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

void DFA::minimizarDFA() {
  std::set<Estado> estadosAceptacion, estadosNoAceptacion;
  Particion particion, particionVieja;
  unsigned int contador = 0;

  for (auto& estado : estados_) {
    if (estado.esEstadoDeAceptacion()) {
      estadosAceptacion.insert(estado);
    } else {
      estadosNoAceptacion.insert(estado);
    }
  }

  particion.insert(estadosAceptacion);
  particion.insert(estadosNoAceptacion);

  do {

    particionVieja = particion;
    particion = crearNuevaParticion(particionVieja);

    for (auto& conjunto : particion) {
      if (conjunto.empty()) {
        particion.erase(conjunto);
      }
    }

    std::cout << 'P' << contador << ": " << particionVieja << '\n';
    ++contador;

  } while (particionVieja != particion);

  std::cout << "El DFA mínimo tiene " << particion.size() << " estados.\n";

  char opcion;
  std::cout << "\nSustituir DFA en memoria por minimizado? (S/n): ";
  std::cin >> opcion;

  if (opcion == 'S' || opcion == 's') {
    construirDFA(particion);
  } else if (opcion != 'N' && opcion != 'n') {
    std::cout << "Opcion invalida.\n";
  }

}

void DFA::exportarDFA(std::string& ruta) {
  std::ofstream fichero(ruta);

  fichero << (*this);

  fichero.close();
}

void DFA::imprimir(std::ostream& salida) const {

  salida << estados_.size() << '\n' <<
               arranque_ << '\n';

  for (auto& estado : estados_) {
    salida << estado << '\n';
  }
}

// Private

Particion DFA::crearNuevaParticion(Particion& particion) {
  Particion helper;

  for (auto& conjunto : particion) {

    Particion conjuntoEstadosDescomp = descomponerConjuntoEstados(conjunto, particion);
    helper = unir(helper, conjuntoEstadosDescomp);

  }

  return helper;

}

Particion DFA::descomponerConjuntoEstados(const std::set<Estado>& estados, Particion& particion) {

  Particion capaActual = { estados };

  for (auto& simbolo : alfabeto_) {
    Particion capaNueva;

    for (auto& conjuntoEstados : capaActual) {
      Particion capaActualPrima = particionarConjuntoPorSimbolo(conjuntoEstados, simbolo, particion);
      capaNueva = unir(capaNueva, capaActualPrima);
    }
    capaActual = capaNueva;
  }

  return capaActual;

}

Particion DFA::particionarConjuntoPorSimbolo(const std::set<Estado>& conjuntoEstados, const std::string& simbolo, Particion& particion) {

  Particion T, p;
  std::set<Estado> helper;
  for (auto& H : particion) {
    for (auto& q : conjuntoEstados) {
      if (H.count((*std::next(estados_.begin(), q.nextTransicion(simbolo))))) {
        helper.insert(q);

      }
    }

    p.insert(helper);
    T = unir(T, p);
    p.clear();
    helper.clear();
  }

  return T;

}

void DFA::construirDFA(Particion& particion) {

  estados_.clear();

  unsigned int contador = 0;
  for (auto& conjunto : particion) {

    Estado estadoMin(contador);

    for (auto& estado : conjunto) {
      if (estado.esEstadoDeAceptacion()) {
        estadoMin.setEstadoDeAceptacion(true);
      }
      for (auto& simbolo : alfabeto_) {
        estadoMin.addTransicion(simbolo,
          destinoTransicionMinimizada(estado.nextTransicion(simbolo), particion));
      }
    }
    estados_.insert(estadoMin);
    ++contador;
  }

}

Particion DFA::unir(Particion& p1, Particion& p2) {

  Particion helper = p1;

  for (auto& item : p2) {
    helper.insert(item);
  }

  return helper;

}

unsigned int DFA::destinoTransicionMinimizada(unsigned int idEstado, Particion& particion) {
  unsigned int contador = 0;
  for (auto& conjunto : particion) {
    for (auto& estado : conjunto) {
      if (idEstado == estado.getId()) {
        return contador;
      }
    }
    ++contador;
  }
  return 0;
}

}

std::ostream& operator<<(std::ostream& salida, const CyA::DFA& dfa) {
  dfa.imprimir(salida);
  return salida;
}

std::ostream& operator<<(std::ostream& salida, const CyA::Particion& particion) {
  std::cout << "{ ";
  for (auto& conjunto : particion) {
    std::cout << "{ ";
    for (auto& estado : conjunto) {
      salida << estado.getId() << " ";
    }
    std::cout << "} ";
  }
  salida << "}\n";
  return salida;
}
