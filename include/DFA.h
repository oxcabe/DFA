

#ifndef DFA_H
#define DFA_H

#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include "Estado.h"

namespace CyA {

typedef std::set<std::set<Estado>> Particion;

/**
 * \class DFA
 *
 * \brief Simulación de Autómata Finito Determinista
 *
 * Un autómata finito determinista (abreviado AFD) es un autómata finito que
 * además es un sistema determinista; es decir, para cada estado en que se
 * encuentre el autómata, y con cualquier símbolo del alfabeto leído, existe
 * siempre no más de una transición posible desde ese estado y con ese símbolo.
 *
 * \author Óscar
 *
 * \version $Revision: 1.1 $
 *
 *
 *
 */
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

  /** \brief Insertar DFA a partir de fichero
  * \param rutaFichero
  * Cadena con la ubicación del fichero a leer.
  */
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
