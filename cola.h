#ifndef COLA_H
#define COLA_H

#include <iostream>

#include "estructuras.h"

#define INCREMENTO 4

using namespace std;

class cola {
  Paciente *elementos; // elementos de la cola
  int inicio, fin;     // principio y fin de la cola
  int Tama;            // Capacidad de la tabla
  int ne;              // Nº de elementos
public:
  cola();  // constructor de la clase
  ~cola(); // destructor de la clase
  void encolar(Paciente e);
  void desencolar();
  bool esvacia();
  Paciente primero();
  int longitud();
};
#endif
