#ifndef ESTADO_H
#define ESTADO_H

#include <iostream>
#include <set>
#include <utility>
#include <string>

namespace CyA {

typedef std::pair<std::string, unsigned int> Transicion;

class Estado {
private:
  unsigned int id_;
  bool aceptacion_;
  std::set<Transicion> transiciones_;
public:
  Estado(unsigned int id, bool aceptacion, unsigned int numTransiciones) :
    id_(id), aceptacion_(aceptacion), transiciones_() {}
  ~Estado() = default;

  void addTransicion(std::string& simbolo, unsigned int destino);
  bool esEstadoDeAceptacion() const;
  unsigned int getId() const;
  int nextTransicion(std::string c) const;

  bool operator<(const Estado& estado) const;

  void imprimir(std::ostream& salida) const;


};
}

std::ostream& operator<<(std::ostream& salida, const CyA::Estado& estado);

#endif // ESTADO_H
