#ifndef DFA_H
#define DFA_H

#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include "Estado.h"

namespace CyA {
class DFA {
private:
  std::set<Estado> estados_;
  unsigned int arranque_;

public:
  DFA() = default;
  DFA(std::string& rutaFichero);
  ~DFA() = default;

  void leerFichero(std::string& rutaFichero);
  void mostrarEstadosDeMuerte();
  void analizarCadena(std::string& cadena);

  void imprimir(std::ostream& salida) const;

};
}

std::ostream& operator<<(std::ostream& salida, const CyA::DFA& dfa);

#endif // DFA_H
