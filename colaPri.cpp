#include "colaPri.h"

colapri::colapri() {};
void colapri::insertarcolapri(Paciente i, int p) { tabla[p - 1].encolar(i); }
void colapri::sacarcolapri() {
  int i = MAXcolas - 1;
  while ((tabla[i].esvacia()) && (i > 0))
    i--;
  tabla[i].desencolar();
}
Paciente colapri::consultarcolapri() {
  int i = MAXcolas - 1;
  while ((tabla[i].esvacia()) && (i > 0))
    i--;
  return tabla[i].primero();
}
bool colapri::esvaciacolapri() {
  int i = MAXcolas - 1;
  bool vacia = false;
  while ((tabla[i].esvacia()) && (i > 0))
    i--;
  if (tabla[i].esvacia())
    vacia = true;
  return vacia;
}
int colapri::longitudcolapri() {
  int lon = 0;
  for (int i = 0; i < MAXcolas; i++)
    lon = lon + tabla[i].longitud();
  return lon;
}

cola colapri::consultarcola(int p) { return tabla[p - 1]; }

int colapri::getmaxcolas() { return MAXcolas; }

bool colapri::buscar(int idPaciente) {
  for (int i = MAXcolas - 1; i >= 0; i--) {
    cola cola = tabla[i];
    int n = cola.longitud();
    for (int j = 0; j < n; j++) {
      Paciente paciente = cola.primero();
      if (paciente.historialClinico == idPaciente) {
        return true;
      } else {
        cola.desencolar();
        cola.encolar(paciente);
      }
    }
  }
  return false;
}

void colapri::exportar(Paciente *p) {
  int pos = 0;

  for (int i = MAXcolas - 1; i >= 0; i--) {

    cola colaAux = tabla[i];
    int n = colaAux.longitud();

    for (int j = 0; j < n; j++) {
      p[pos] = colaAux.primero();
      colaAux.desencolar();
      pos++;
    }
  }
}
