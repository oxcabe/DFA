#include "../include/GramaticaRegular.h"

namespace CyA {

GramaticaRegular::GramaticaRegular(DFA& dfa) {

  simbolosTerminales_ = dfa.getAlfabeto();
  std::set<Estado> estadosDFA = dfa;

  for (auto& estado : estadosDFA) {

    SimboloNoTerminal s(idToSimbolo(estado.getId()), estado.getId());

    for (auto& simbolo : simbolosTerminales_) {

      std::string regla = "", comprobarNoExiste = "";



      regla += simbolo;
      comprobarNoExiste += idToSimbolo(estado.nextTransicion(simbolo));

      if (comprobarNoExiste != "?") {
        regla += comprobarNoExiste;
        s.insertRegla(regla);
      }
    }

    if (estado.esEstadoDeAceptacion()) {
      s.insertRegla("~");
    }

    simbolosNoTerminales_.insert(s);

  }

}

char GramaticaRegular::idToSimbolo(unsigned int id) {
  return (id == 0) ? 'S' : char('A' + id -1);
}

void GramaticaRegular::imprimir(std::ostream& salida) const {
  salida << simbolosTerminales_.size() << '\n';

  for (auto& simbolo : simbolosTerminales_) {
    salida << simbolo << ' ';
  }

  salida << '\n';

  salida << simbolosNoTerminales_.size() << '\n';

  for (auto& simbolo : simbolosNoTerminales_) {
    salida << simbolo.getSimbolo() << ' ';
  }

  salida << '\n';

  for (auto& simbolo : simbolosNoTerminales_) {
    salida << simbolo.getSimbolo() << " -> ";
    salida << simbolo;
    salida << '\n';
  }


}

void GramaticaRegular::exportarGramatica(std::string& rutaFichero) {
  std::ofstream fichero(rutaFichero);
  fichero << (*this);
  fichero.close();
}

}

std::ostream& operator<<(std::ostream& salida, const CyA::GramaticaRegular& g) {
  g.imprimir(salida);
  return salida;
}
