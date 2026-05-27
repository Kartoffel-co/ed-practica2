#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <cstring>
#include <fstream>
#include <iostream>

#include "cola.h"
#include "estructuras.h"
#include "lista.h"

using namespace std;

#define maxColaEspera 20 // Valor máximo de la cola de espera (siempre 20).
class Hospital {
  cadena nombreHospital;       // Nombre del Hospital.
  int codigoPostal;            // Código postal del Hospital.
  int idHospital;              // Identificador numérico único del Hospital.
  Hospital *siguienteHospital; // Puntero al siguiente Hospital del sistema.
  int maxCamas; // Capacidad máxima de pacientes ingresados (mínimo 5).
  lista pacientesIngresados; // Lista de pacientes ingresados ordenados por id
                             // ASC.
  cola pacientesEnEspera; // Cola de prioridad de pacientes por gravedad DESC.
  cadena estado;          // Estado actual del hospital, valores posibles:
                          // "ACTIVO"; "SIN SANGRE"; "INACTIVO".
  cadena tipoHospital;    // Tipo de hospital, valores posibles:
public:
  ~Hospital();
  Hospital(cadena nom, int id, int mC, int cP, cadena tH);
  // Método constructor que inicializa los atributos 'nombreHospital',
  // 'idHospital', 'maxCamas', 'codigoPostal' y 'tipoHospital' con los valores
  // de 'nom', 'id', 'mC', 'cP' y 'tH', respectivamente. Además, inicializa el
  // atributo estado a "INACTIVO".
  void getNombreHospital(cadena &nH);
  // Devuelve el nombre del Hospital a través del parámetro 'nH'.
  int getIdHospital(); // Devuelve el identificador del Hospital.
  int getMaxCamas();   // Devuelve el número máximo de camas (ingresados) del
                       // Hospital.
  int getNumPacientesIngresados(); // Devuelve el número de pacientes
                                   // ingresados.
  int getNumPacientesEnEspera();   // Devuelve el número de pacientes en espera.
  Hospital *
  getSiguienteHospital(); // Devuelve el puntero al siguiente Hospital.
  void setSiguienteHospital(Hospital *pH);
  // Asigna el valor recibido como parámetro al atributo siguienteHospital.
  bool setMaxCamas(int camas);
  // Asigna un nuevo número de camas, el Hospital debe estar "INACTIVO" y el
  // valor a asignar no debe ser menor a 5 para permitir el cambio, devolviendo
  // true si lo realiza o false en caso contrario.
  bool buscarPaciente(int idPaciente);
  // Busca un paciente por su historial clínico, devolviendo true si lo
  // encuentra entre los ingresados o entre los que están en espera, o false en
  // caso contrario.
  bool ingresarPaciente(Paciente p);
  // Intenta añadir un paciente al Hospital devolviendo true si lo añade entre
  // los ingresados o entre los que esperan, o false en caso contrario.
  bool bajaPaciente(int idPaciente);
  // Elimina un paciente por su historial clínico, de la lista de ingresados o
  // de la cola de espera. Si estaba ingresado y hay pacientes en espera
  // el primero de la cola pasa a ingresado. Devuelve true si se dio de baja al
  // paciente, o false si no se encontró.
  void exportarPacientesIngresados(Paciente *ingresados);
  // Copia todos los pacientes ingresados en el vector dinámico accesible desde
  // el puntero ingresados, parámetro de entrada.
  void exportarPacientesEnEspera(Paciente *enEspera);
  // Copia todos los pacientes en cola en el vector dinámico accesible desde
  // el puntero enEspera, parámetro de entrada.
  bool estaActivo();
  // Devuelve true si el Hospital está "ACTIVO", false en otro caso.
  bool estaInactivo();
  // Devuelve true si el Hospital está "INACTIVO" false en otro caso.
  bool activar();
  // Cambia el estado del Hospital a "ACTIVO" si estaba "INACTIVO" o "SIN
  // SANGRE" Devuelve true si el cambio fue exitoso, false si ya estaba activo.
  bool desactivar();
  // Cambia el estado del Hospital a "INACTIVO" si estaba previamente en el
  // estado "ACTIVO". Vacía la lista de ingresados y la cola de espera. Devuelve
  // true si se desactivó, false si ya estaba inactivo o en "SIN SANGRE".
  bool faltaSangre();
  // Cambia el estado del Hospital a "SIN SANGRE" si estaba previamente en el
  // estado "ACTIVO". Mantiene los ingresados, pero vacía la cola de espera
  // Devuelve true si se consiguió, false si ya estaba "SIN SANGRE" o
  // desactivado.
  void mostrarPacientesIngresados();
  // Muestra todos los pacientes actualmente ingresados con sus datos.
  void mostrarPacientesEnEspera();
  // Muestra todos los pacientes en la cola de espera con sus datos.
  void mostrarInformacion();
  // Muestra información general del hospital:
  // nombre, identificador, estado, tipo, CP, ocupación y gravedad media de
  // ingresados.
};
#endif
11;
rgb : 2626 / 2626 / 2626
