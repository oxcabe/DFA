#ifndef DFA_H
#define DFA_H

#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <algorithm>
#include "Estado.h"

namespace CyA {

typedef std::set<std::set<Estado>> Particion;

class DFA {
private:
  std::set<Estado> estados_;
  unsigned int arranque_;
  std::set<std::string> alfabeto_;

  Particion crearNuevaParticion(Particion& particion);
  Particion descomponerConjuntoEstados(const std::set<Estado>& estados, Particion& particion);
  Particion particionarConjuntoPorSimbolo(const std::set<Estado>& conjuntoEstados, const std::string& simbolo, Particion& particion);
  void construirDFA(Particion& particion);
  Particion unir(Particion& p1, Particion& p2);
  unsigned int destinoTransicionMinimizada(unsigned int idEstado, Particion& particion);



public:
  DFA() = default;
  DFA(std::string& rutaFichero);
  ~DFA() = default;

  void leerFichero(std::string& rutaFichero);
  void mostrarEstadosDeMuerte();
  void analizarCadena(std::string& cadena);
  void minimizarDFA();
  void exportarDFA(std::string& ruta);

  void imprimir(std::ostream& salida) const;

};
}

std::ostream& operator<<(std::ostream& salida, const CyA::DFA& dfa);
std::ostream& operator<<(std::ostream& salida, const CyA::Particion& particion);

#endif // DFA_H
