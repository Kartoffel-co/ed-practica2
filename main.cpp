#include "monitorizacionHospitales.h"

#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

int n_pacientes = 42;

void crearHospitales(MonitorizacionHospitales &sistema) {
  sistema.crearHospital((char *)"Hospital Juan Ramón Jiménez", 1, 4, 21005,
                        (char *)"PUBLICO");
  sistema.crearHospital((char *)"Hospital Infanta Elena", 2, 4, 21006,
                        (char *)"PUBLICO");
  sistema.crearHospital((char *)"Hospital Quirónsalud Huelva", 3, 5, 21007,
                        (char *)"PRIVADO");
  sistema.crearHospital((char *)"Hospital Virgen de la Victoria", 4, 3, 41005,
                        (char *)"PUBLICO");
  sistema.crearHospital((char *)"Hospital Sanatorio del Sol", 5, 3, 41006,
                        (char *)"PRIVADO");
  sistema.crearHospital((char *)"Hospital de la Esperanza", 6, 2, 41007,
                        (char *)"PUBLICO");

  cout << "[GEN] 6 hospitales creados.\n";

  sistema.activarHospital(1);
  sistema.activarHospital(2);
  sistema.activarHospital(3);
  sistema.activarHospital(4);
  sistema.activarHospital(5);

  cout << "[GEN] 5 hospitales activados y 1 permanece INACTIVO para pruebas.\n";
  cout << "[GEN] 42 pacientes generados para forzar escenarios de espera.\n";
}

void crearPacientes(MonitorizacionHospitales &sistema) {
  char sangre[4][3] = {"A", "B", "AB", "O"};

  for (int i = 1; i <= n_pacientes; i++) {
    Paciente p;

    sprintf(p.nombreCompleto, "Paciente_%d", i);
    p.historialClinico = 1000 + i;
    strcpy(p.tipoSangre, sangre[i % 4]);
    p.gravedad = (i % 5) + 1;
    sprintf(p.patologia, "Patologia_%d", i);

    cadena lugar;
    bool enEspera = false;

    sistema.ingresarPacienteSistema(p, lugar, enEspera);

    cout << "[GEN] Paciente " << p.historialClinico
         << (enEspera ? " -> EN ESPERA en " : " -> INGRESADO en ") << lugar
         << endl;
  }
}

void generarDatos(MonitorizacionHospitales &sistema) {
  crearHospitales(sistema);
  crearPacientes(sistema);

  cout << "\n[GEN] Generación de datos completada.\n";
}

static void establecerTipoSangre(Paciente &p, const char *tipo) {
  if (strcmp(tipo, "AB") == 0) {
    p.tipoSangre[0] = 'A';
    p.tipoSangre[1] = 'B';
  } else if (strcmp(tipo, "A") == 0) {
    p.tipoSangre[0] = 'A';
    p.tipoSangre[1] = '\0';
  } else if (strcmp(tipo, "O") == 0) {
    p.tipoSangre[0] = 'O';
    p.tipoSangre[1] = '\0';
  } else {
    p.tipoSangre[0] = '\0';
    p.tipoSangre[1] = '\0';
  }
}

static int menu() {
  int opcion;
  cout << "======================================" << endl;
  cout << "    SISTEMA DE MONITORIZACION MEDICA" << endl;
  cout << "======================================" << endl;
  cout << "1.  Consultar hospital" << endl;
  cout << "2.  Listar todos los hospitales" << endl;
  cout << "3.  Dar de alta nuevo hospital" << endl;
  cout << "4.  Eliminar hospital" << endl;
  cout << "5.  Activar hospital" << endl;
  cout << "6.  Desactivar hospital" << endl;
  cout << "7.  Declarar hospital 'SIN SANGRE'" << endl;
  cout << "8.  Modificar capacidad de camas" << endl;
  cout << "9.  Ingresar paciente" << endl;
  cout << "10. Dar de baja paciente" << endl;
  cout << "11. Mostrar cola global" << endl;
  cout << "0.  Salir" << endl;
  cout << "--------------------------------------" << endl;
  cout << "Seleccione una opcion: ";
  cin >> opcion;
  cin.ignore(1000, '\n');
  return opcion;
}

int main() {
  MonitorizacionHospitales sistema;
  generarDatos(sistema);
  int opcion = menu();

  while (opcion != 0) {
    switch (opcion) {
    case 1: {
      int id;
      cout << "Identificador del hospital: ";
      cin >> id;
      cin.ignore(1000, '\n');
      if (sistema.getPosicionHospital(id) == -1) {
        cout << "Error: el hospital no existe." << endl;
      } else {
        sistema.mostrarInformacionHospitales(sistema.getPosicionHospital(id));
      }
      break;
    }
    case 2:
      sistema.mostrarInformacionHospitales(-1);
      break;
    case 3: {
      cadena nombre, tipo;
      int id, camas, codigo;
      cout << "Nombre del hospital: ";
      cin.getline(nombre, sizeof(nombre));
      cout << "Identificador del hospital: ";
      cin >> id;
      cin.ignore(1000, '\n');
      cout << "Numero de camas: ";
      cin >> camas;
      cin.ignore(1000, '\n');
      cout << "Codigo postal: ";
      cin >> codigo;
      cin.ignore(1000, '\n');
      cout << "Tipo (PRIVADO o PUBLICO): ";
      cin.getline(tipo, sizeof(tipo));
      if (!sistema.crearHospital(nombre, id, camas, codigo, tipo)) {
        cout << "Error: el hospital ya existe o no se pudo crear." << endl;
      } else {
        cout << "Hospital registrado correctamente." << endl;
      }
      break;
    }
    case 4: {
      int id;
      cout << "Identificador del hospital: ";
      cin >> id;
      cin.ignore(1000, '\n');
      if (!sistema.eliminarHospital(id)) {
        cout << "Error: no se pudo eliminar el hospital (no existe o no esta "
                "INACTIVO)."
             << endl;
      } else {
        cout << "Hospital eliminado correctamente." << endl;
      }
      break;
    }
    case 5: {
      int id;
      cout << "Identificador del hospital: ";
      cin >> id;
      cin.ignore(1000, '\n');
      if (!sistema.activarHospital(id)) {
        cout << "Error: no se pudo activar el hospital." << endl;
      } else {
        cout << "Hospital activado correctamente." << endl;
      }
      break;
    }
    case 6: {
      int id;
      cout << "Identificador del hospital: ";
      cin >> id;
      cin.ignore(1000, '\n');
      if (!sistema.desactivarHospital(id)) {
        cout << "Error: no se pudo desactivar el hospital." << endl;
      } else {
        cout << "Hospital desactivado correctamente." << endl;
      }
      break;
    }
    case 7: {
      int id;
      cout << "Identificador del hospital: ";
      cin >> id;
      cin.ignore(1000, '\n');
      if (!sistema.declararSinSangre(id)) {
        cout << "Error: no se pudo declarar el hospital SIN SANGRE." << endl;
      } else {
        cout << "Hospital declarado SIN SANGRE correctamente." << endl;
      }
      break;
    }
    case 8: {
      int id, camas;
      cout << "Identificador del hospital: ";
      cin >> id;
      cin.ignore(1000, '\n');
      cout << "Nuevo numero de camas: ";
      cin >> camas;
      cin.ignore(1000, '\n');
      if (!sistema.modificarCamasHospital(id, camas)) {
        cout << "Error: no se pudo modificar la capacidad de camas." << endl;
      } else {
        cout << "Capacidad de camas actualizada correctamente." << endl;
      }
      break;
    }
    case 9: {
      Paciente p;
      cadena tipo;
      cout << "Nombre completo: ";
      cin.getline(p.nombreCompleto, sizeof(p.nombreCompleto));
      cout << "Historial clinico: ";
      cin >> p.historialClinico;
      cin.ignore(1000, '\n');
      cout << "Tipo de sangre (A, AB, O): ";
      cin.getline(tipo, sizeof(tipo));
      establecerTipoSangre(p, tipo);
      cout << "Gravedad (1-5): ";
      cin >> p.gravedad;
      cin.ignore(1000, '\n');
      cout << "Patologia: ";
      cin.getline(p.patologia, sizeof(p.patologia));

      cadena destino;
      bool enEspera = false;
      if (!sistema.ingresarPacienteSistema(p, destino, enEspera)) {
        cout << "Error: el paciente ya existe en el sistema." << endl;
      } else {
        cout << "Paciente asignado a: " << destino;
        if (enEspera) {
          cout << " (en espera)";
        }
        cout << endl;
      }
      break;
    }
    case 10: {
      int id;
      cadena origen;
      cout << "Historial clinico del paciente: ";
      cin >> id;
      cin.ignore(1000, '\n');
      if (!sistema.bajaPacienteSistema(id, origen)) {
        cout << "Error: no se encontro el paciente en el sistema." << endl;
      } else {
        cout << "Paciente dado de baja correctamente desde: " << origen << endl;
      }
      break;
    }
    case 11:
      sistema.mostrarInformacionColaGlobal();
      break;
    default:
      cout << "Opcion incorrecta" << endl;
    }

    cout << endl;
    opcion = menu();
  }

  return 0;
}
