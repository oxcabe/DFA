#ifndef SIMBOLONOTERMINAL_H
#define SIMBOLONOTERMINAL_H

#include <iostream>
#include <set>

namespace CyA {


class SimboloNoTerminal {
private:
  char simbolo_;
  unsigned int indice_;
  std::set<std::string> reglasDeProduccion_;

public:
  SimboloNoTerminal() = default;
  SimboloNoTerminal(char simbolo, unsigned int indice) : simbolo_(simbolo), indice_(indice), reglasDeProduccion_() {}
  ~SimboloNoTerminal() = default;

  char getSimbolo() const;
  void insertRegla(std::string regla);

  bool operator<(const SimboloNoTerminal& s) const;
  bool operator==(const SimboloNoTerminal& s) const;

  void imprimir(std::ostream& salida) const;

};
}

std::ostream& operator<<(std::ostream& salida, const CyA::SimboloNoTerminal& s);

#endif // SIMBOLONOTERMINAL_H
