#include "hospital.h"

// ejercicio 10 tema 3

using namespace std;

Hospital::~Hospital() {};
Hospital::Hospital(cadena nom, int id, int mC, int cP, cadena tH) {
  strcpy(estado, "INACTIVO");
  strcpy(nombreHospital, nom);
  strcpy(tipoHospital, tH);
  idHospital = id;
  codigoPostal = cP;
  maxCamas = mC;
};
// Método constructor que inicializa los atributos 'nombreHospital',
// 'idHospital', 'maxCamas', 'codigoPostal' y 'tipoHospital' con los valores
// de 'nom', 'id', 'mC', 'cP' y 'tH', respectivamente. Además, inicializa el
// atributo estado a "INACTIVO".
void Hospital::getNombreHospital(cadena &nH) { strcpy(nombreHospital, nH); };
// Devuelve el nombre del Hospital a través del parámetro 'nH'.
int Hospital::getIdHospital() {
  return 0;
}; // Devuelve el identificador del Hospital.
int Hospital::getMaxCamas() {
  return maxCamas;
}; // Devuelve el número máximo de camas
   // (ingresados) del Hospital.
int Hospital::getNumPacientesIngresados() {
  return pacientesIngresados.longitud();
}; // Devuelve el número de pacientes
   // ingresados.
int Hospital::getNumPacientesEnEspera() {
  return pacientesEnEspera.longitud();
}; // Devuelve el número de pacientes
   // en espera.
Hospital *Hospital::getSiguienteHospital() { return siguienteHospital; };
// Devuelve el puntero al siguiente Hospital.
void Hospital::setSiguienteHospital(Hospital *pH) { siguienteHospital = pH; };
// Asigna el valor recibido como parámetro al atributo siguienteHospital.
bool Hospital::setMaxCamas(int camas) {
  if (strcmp(estado, "INACTIVO")) {
    if (camas >= 5) {
      maxCamas = camas;
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
};
// Asigna un nuevo número de camas, el Hospital debe estar "INACTIVO" y el
// valor a asignar no debe ser menor a 5 para permitir el cambio, devolviendo
// true si lo realiza o false en caso contrario.
bool Hospital::buscarPaciente(int idPaciente) {};
// Busca un paciente por su historial clínico, devolviendo true si lo
// encuentra entre los ingresados o entre los que están en espera, o false en
// caso contrario.
bool Hospital::ingresarPaciente(Paciente p) {};
// Intenta añadir un paciente al Hospital devolviendo true si lo añade entre
// los ingresados o entre los que esperan, o false en caso contrario.
bool Hospital::bajaPaciente(int idPaciente) {};
// Elimina un paciente por su historial clínico, de la lista de ingresados o
// de la cola de espera. Si estaba ingresado y hay pacientes en espera
// el primero de la cola pasa a ingresado. Devuelve true si se dio de baja al
// paciente, o false si no se encontró.
void Hospital::exportarPacientesIngresados(Paciente *ingresados) {};
// Copia todos los pacientes ingresados en el vector dinámico accesible desde
// el puntero ingresados, parámetro de entrada.
void Hospital::exportarPacientesEnEspera(Paciente *enEspera) {};
// Copia todos los pacientes en cola en el vector dinámico accesible desde
// el puntero enEspera, parámetro de entrada.
bool Hospital::estaActivo() {
  if (strcmp(estado, "ACTIVO")) {
    return true;
  } else {
    return false;
  }
};
// Devuelve true si el Hospital está "ACTIVO", false en otro caso.
bool Hospital::estaInactivo() {
  if (strcmp(estado, "INACTIVO")) {
    return true;
  } else {
    return false;
  }
};
// Devuelve true si el Hospital está "INACTIVO" false en otro caso.
bool Hospital::activar() {
  if (strcmp(estado, "INACTIVO") || strcmp(estado, "SIN SANGRE")) {
    strcpy(estado, "ACTIVO");
    return false;
  } else {
    return true;
  }
};
// Cambia el estado del Hospital a "ACTIVO" si estaba "INACTIVO" o "SIN
// SANGRE" Devuelve true si el cambio fue exitoso, false si ya estaba activo.
bool Hospital::desactivar() {
  if (strcmp(estado, "INACTIVO") || strcmp(estado, "SIN SANGRE")) {
    return false;
  } else {
    while (!pacientesIngresados.esvacia()) {
      pacientesIngresados.eliminarIzq();
    }
    while (!pacientesEnEspera.esvacia()) {
      pacientesEnEspera.desencolar();
    }
    return true;
  }
};
// Cambia el estado del Hospital a "INACTIVO" si estaba previamente en el
// estado "ACTIVO". Vacía la lista de ingresados y la cola de espera. Devuelve
// true si se desactivó, false si ya estaba inactivo o en "SIN SANGRE".
bool Hospital::faltaSangre() {
  if (strcmp(estado, "INACTIVO") || strcmp(estado, "SIN SANGRE")) {
    return false;
  } else {
    while (!pacientesEnEspera.esvacia()) {
      pacientesEnEspera.desencolar();
    }
    return true;
  }
};
// Cambia el estado del Hospital a "SIN SANGRE" si estaba previamente en el
// estado "ACTIVO". Mantiene los ingresados, pero vacía la cola de espera
// Devuelve true si se consiguió, false si ya estaba "SIN SANGRE" o
// desactivado.
void Hospital::mostrarPacientesIngresados() {};
// Muestra todos los pacientes actualmente ingresados con sus datos.
void Hospital::mostrarPacientesEnEspera() {};
// Muestra todos los pacientes en la cola de espera con sus datos.
void Hospital::mostrarInformacion() {
  float gravedadMedia = 0;
  for (int i = 0; i < pacientesIngresados.longitud(); i++) {
    gravedadMedia += pacientesIngresados.observar(i).gravedad;
  }
  gravedadMedia = gravedadMedia / pacientesIngresados.longitud();

  cout << "Nombre: " << nombreHospital << endl;
  cout << "Identificador: " << idHospital << endl;
  cout << "Estado: " << estado << endl;
  cout << "Tipo: " << tipoHospital << endl;
  cout << "Codigo Postal" << codigoPostal << endl;
  cout << "Ocupacion" << pacientesIngresados.longitud() << endl;
  cout << "Gravedad media" << gravedadMedia << endl;
};
// Muestra información general del hospital:
// nombre, identificador, estado, tipo, CP, ocupación y gravedad media de
// ingresados.
