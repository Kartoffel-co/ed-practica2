#include "monitorizacionHospitales.h"
#include <cstring>
#include <iostream>

using namespace std;

/********************************************************
 GENERADOR DE DATOS PARA SISTEMA DE MONITORIZACIÓN MÉDICA

 Este módulo sirve para inicializar el sistema con datos
 de prueba automáticos.

 - Añadir hospitales
 - Generar pacientes ficticios
 - Asigna pacientes automáticos

 Se debe añadir el archivo junto al main.cpp del proyecto

 Se debe agregar la cabecera al main:

 - void generarDatos(MonitorizacionHospitales &sistema);

 Se debe llamar desde el main así:

   - MonitorizacionHospitales sistema;
   - generarDatos(sistema);

***********************************************************/

// Número de pacientes a generar
// aumentar si se requiere más pacientes
int n_pacientes = 20;

////////////////
// HOSPITALES //
////////////////
void crearHospitales(MonitorizacionHospitales &sistema) {
  // Hospitales definidos
  sistema.crearHospital((char *)"Hospital Juan Ramón Jiménez", 1, 10, 21005,
                        (char *)"PUBLICO");
  sistema.crearHospital((char *)"Hospital Infanta Elena", 2, 8, 21006,
                        (char *)"PUBLICO");
  sistema.crearHospital((char *)"Hospital Quirónsalud Huelva", 3, 12, 21007,
                        (char *)"PRIVADO");

  cout << "[GEN] 3 hospitales de Huelva creados.\n";

  // Activar Hospitales
  sistema.activarHospital(1);
  sistema.activarHospital(2);
  sistema.activarHospital(3);

  cout << "[GEN] 3 hospitales de Huelva activados.\n";
}

///////////////
// PACIENTES //
///////////////
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

    // Insertar en sistema
    sistema.ingresarPacienteSistema(p, lugar, enEspera);

    cout << "[GEN] Paciente " << p.historialClinico
         << (enEspera ? " -> EN ESPERA en " : " -> INGRESADO en ") << lugar
         << endl;
  }
}

///////////////////////////
// FUNCIÓN PRINCIPAL GEN //
///////////////////////////
void generarDatos(MonitorizacionHospitales &sistema) {
  crearHospitales(sistema);
  crearPacientes(sistema);

  cout << "\n[GEN] Generación de datos completada.\n";
}
