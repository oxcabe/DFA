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
  Estado(unsigned int id, bool aceptacion = false) :
    id_(id), aceptacion_(aceptacion), transiciones_() {}
  ~Estado() = default;

  void addTransicion(const std::string& simbolo, unsigned int destino);
  bool esEstadoDeAceptacion() const;
  void setEstadoDeAceptacion(bool aceptacion);
  unsigned int getId() const;
  int nextTransicion(std::string c) const;

  bool operator<(const Estado& estado) const;
  bool operator==(const Estado& estado) const;

  void imprimir(std::ostream& salida) const;


};
}

std::ostream& operator<<(std::ostream& salida, const CyA::Estado& estado);

#endif // ESTADO_H
