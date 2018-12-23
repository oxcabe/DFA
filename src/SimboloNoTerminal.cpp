#include "../include/SimboloNoTerminal.h"

namespace CyA {

char SimboloNoTerminal::getSimbolo() const {
  return simbolo_;
}

void SimboloNoTerminal::insertRegla(std::string regla) {
  reglasDeProduccion_.insert(regla);
}

bool SimboloNoTerminal::operator<(const SimboloNoTerminal& s) const {
  return indice_ < s.indice_;
}
bool SimboloNoTerminal::operator==(const SimboloNoTerminal& s) const {
  return indice_ == s.indice_;
}

void SimboloNoTerminal::imprimir(std::ostream& salida) const {

  unsigned int comprobarFinal = 1;

  for (auto& regla : reglasDeProduccion_) {
    salida << regla;
    if (comprobarFinal != reglasDeProduccion_.size()) {
      salida << " | ";
    }
    ++comprobarFinal;
  }

}

}

std::ostream& operator<<(std::ostream& salida, const CyA::SimboloNoTerminal& s) {
  s.imprimir(salida);
  return salida;
}
