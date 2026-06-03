#ifndef MONITORIZACIONHOSPITAL_H
#define MONITORIZACIONHOSPITAL_H

#include <cstring>
#include <fstream>
#include <iostream>

#include "hospital.h"

class MonitorizacionHospitales {
  colapri colaGlobal;
  // Cola de prioridad de pacientes por gravedad DESC.
  Hospital
      *primerHospital; // Puntero al inicio de la lista enlazada de hospitales.
  int numHospitales;
  // Contador total de hospitales registrados.
  bool existeHospital(int idHospital);
  // Comprueba si ya existe un hospital con el identificador pasado por
  // parámetros. Devolviendo true si existe o false si no.
  bool existePaciente(int idPaciente, cadena &lugar);
  // Busca en TODO el sistema si el paciente ocupa alguna cama, o si
  // está en la lista de espera de algún hospital o la cola de espera global,
  // devolviendo true si se encuentra o false en caso contrario.
  // Además, si lo encuentra, devuelve por el parámetro por referencia "lugar",
  // el hospital donde se encuentra o, la cola de espera global si se encontrase
  // ahí.
  Hospital *buscarHospital(int idHospital);
  // Busca un hospital por su identificador recorriendo la estructura de nodos
  // enlazados. Devuelve el puntero al hospital o NULL si no existe.
  Hospital *buscarHospitalConMasCamasLibres();
  // Localiza el hospital "ACTIVO" con mayor disponibilidad de camas.
  // Devuelve el puntero al hospital o NULL si no hay ninguno disponible.
  Hospital *buscarHospitalParaEspera();
  // Localiza el hospital "ACTIVO" con más huecos libres en su cola de espera.
  // Devuelve el puntero al hospital o NULL si todas las colas están llenas.

  Hospital *buscarHospitalConPaciente(int idPaciente);

public:
  ~MonitorizacionHospitales();
  // Recorre la lista de hospitales y elimina cada nodo liberando la memoria
  // dinámica.
  MonitorizacionHospitales();
  // Constructor que inicializa el sistema sin hospitales y contadores a cero.
  int getNumHospitales();
  // Devuelve la cantidad de hospitales que hay actualmente en el sistema.
  bool crearHospital(cadena nombre, int idHospital, int maxCamas, int codPostal,
                     cadena tipo);
  // Crea un nuevo hospital y lo añade a la lista enlazada de hospitales.
  // Inicializa el hospital con los valores proporcionados por parámetro.
  // Devuelve true si la creación y adición fueron exitosas,
  // o false si ya existe un hospital con el mismo identificador.
  bool eliminarHospital(int idHospital);
  // Elimina un hospital de la memoria y lo desconecta de la estructura de nodos
  // enlazados, si y solo si, el hospital está "INACTIVO".
  // Devuelve true si se eliminó o false si no existe o no estaba "INACTIVO".
  bool activarHospital(int idHospital);
  // Cambia el estado del hospital con el identificador proporcionado por
  // parámetro a "ACTIVO", permitiendo que el hospital reciba pacientes. Al
  // activarse, comprueba si hay pacientes en la cola global y asigna a los
  // pacientes disponibles al hospital, es decir, los extrae de la cola global y
  // los incorpora al hospital. Devuelve true si el hospital se activó
  // correctamente, o false si no existe o ya estaba activo.
  bool declararSinSangre(int idHospital);
  // Cambia el estado del hospital con el identificador proporcionado a "SIN
  // SANGRE". Trasladando los pacientes de su cola de espera por orden de
  // prioridad a otros centros disponibles. Si no existe otro hospital al que
  // transferir los pacientes, se moverán a la cola global del sistema. Devuelve
  // true si el hospital vació su cola y su estado se cambió correctamente, o
  // false si el hospital no existe o si no estaba previamente "ACTIVO".
  bool desactivarHospital(int idHospital);
  // Cambia el estado del hospital con el identificador proporcionado a
  // "INACTIVO". Traslada a TODOS sus pacientes por orden de prioridad a otros
  // centros disponibles. Si no existe otro hospital al que transferir los
  // pacientes, se moverán a la cola global del sistema. Devuelve true si el
  // hospital se vació y desactivó correctamente, o false si el hospital no
  // existe o no estaba "ACTIVO".
  bool modificarCamasHospital(int idHospital, int maxCamas);
  // Modifica la cantidad total de camas de un hospital con el identificador
  // proporcionado, para ello, el hospital debe estar "INACTIVO".
  // Devuelve true si la modificación fue exitosa, o false si el hospital
  // no existe, o el valor de maxCamas es menor a 5.
  bool ingresarPacienteSistema(Paciente p, cadena &lugarDestino,
                               bool &enEspera);
  // Busca el hospital con mayor disponibilidad de camas. En caso de ausencia de
  // hueco, se selecciona el hospital con menor número de pacientes en espera.
  // Si hay algún hospital disponible para ser ingresado o añadido a su cola de
  // espera, el paciente se le asigna, en caso contrario, pasa a la cola de
  // espera global. Si se realiza la inserción, devuelve true y actualiza
  // "lugarDestino" con el nombre del hospital o de la cola de espera global. El
  // parámetro "enEspera" se establece a true si el paciente queda en alguna
  // cola de espera, o a false si es ingresado directamente en el hospital.
  // Devuelve false si el paciente ya existe.
  bool bajaPacienteSistema(int idPaciente, cadena &lugarOrigen);
  // Busca y elimina a un paciente de cualquier hospital o de la cola global.
  // Si se elimina de un hospital y se libera una cama, el primer paciente de la
  // cola de espera de ese hospital pasa a ocuparla. A su vez, se incorpora un
  // paciente desde la cola de espera global a la cola de espera del hospital.
  // Actualiza "lugarOrigen" con el nombre del hospital o de la cola de espera
  // de donde se eliminó el paciente.
  // Devuelve true si se dio de baja al paciente, o false si no existe en el
  // sistema.
  int getPosicionHospital(int idHospital);
  // Busca la posición numérica de un hospital en la lista enlazada, comenzando
  // en 1. Devuelve la posición encontrada o -1 si el hospital no existe.
  void mostrarInformacionHospitales(int pos);
  // Imprime los datos y pacientes de un hospital específico según su posición.
  // Si se pasa pos = -1, imprime solo los datos de todos los hospitales.
  void mostrarInformacionColaGlobal();
  // Imprime los pacientes que se encuentran en la cola global del sistema.
};
#endif
