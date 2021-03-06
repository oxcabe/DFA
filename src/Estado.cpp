#include "../include/Estado.h"

namespace CyA {

void Estado::addTransicion(const std::string& simbolo, unsigned int destino) {
  transiciones_.insert(Transicion(simbolo, destino));
}

bool Estado::esEstadoDeAceptacion() const {
  return aceptacion_;
}

void Estado::setEstadoDeAceptacion(bool aceptacion) {
  aceptacion_ = aceptacion;
}

unsigned int Estado::getId() const {
  return id_;
}

int Estado::nextTransicion(std::string cadena) const {
  for (auto& transicion : transiciones_) {
    if (transicion.first == cadena) {
      return transicion.second;
    }
  }
  return -1;
}

bool Estado::operator<(const Estado& estado) const {
  return id_ < estado.id_;
}

bool Estado::operator==(const Estado& estado) const {
  return id_ == estado.id_;
}

void Estado::imprimir(std::ostream& salida) const {
  salida << id_ << ' ' << aceptacion_ << ' ' << transiciones_.size() << ' ';
  for (auto& transicion : transiciones_) {
    salida << transicion.first << ' ' << transicion.second << ' ';
  }
}

}

std::ostream& operator<<(std::ostream& salida, const CyA::Estado& estado) {
  estado.imprimir(salida);
  return salida;
}
