#include "monitorizacionHospitales.h"

MonitorizacionHospitales::MonitorizacionHospitales() {
  primerHospital = NULL;
  numHospitales = 0;
}

MonitorizacionHospitales::~MonitorizacionHospitales() {
  Hospital *actual = primerHospital;
  while (actual != NULL) {
    Hospital *siguiente = actual->getSiguienteHospital();
    delete actual;
    actual = siguiente;
  }
  primerHospital = NULL;
  numHospitales = 0;
}

bool MonitorizacionHospitales::existeHospital(int idHospital) {
  return buscarHospital(idHospital) != NULL;
}

bool MonitorizacionHospitales::existePaciente(int idPaciente, cadena &lugar) {
  if (colaGlobal.buscar(idPaciente)) {
    strcpy(lugar, "cola de espera global");
    return true;
  }
  Hospital *hospital = buscarHospitalConPaciente(idPaciente);
  if (hospital != NULL) {
    hospital->getNombreHospital(lugar);
    return true;
  }

  return false;
}

Hospital *MonitorizacionHospitales::buscarHospitalConPaciente(int idPaciente) {
  Hospital *actual = primerHospital;
  while (actual != NULL) {
    if (actual->buscarPaciente(idPaciente)) {
      return actual;
    }
    actual = actual->getSiguienteHospital();
  }
  return NULL;
}

Hospital *MonitorizacionHospitales::buscarHospital(int idHospital) {
  Hospital *actual = primerHospital;
  while (actual != NULL) {
    if (actual->getIdHospital() == idHospital) {
      return actual;
    }
    actual = actual->getSiguienteHospital();
  }
  return NULL;
}

Hospital *MonitorizacionHospitales::buscarHospitalConMasCamasLibres() {
  Hospital *mejor = NULL;
  int maxLibres = -1;

  Hospital *actual = primerHospital;
  while (actual != NULL) {
    if (actual->estaActivo()) {
      int libres = actual->getMaxCamas() - actual->getNumPacientesIngresados();
      if (libres > maxLibres) {
        maxLibres = libres;
        mejor = actual;
      }
    }
    actual = actual->getSiguienteHospital();
  }

  return mejor;
}

Hospital *MonitorizacionHospitales::buscarHospitalParaEspera() {
  Hospital *mejor = NULL;
  int maxHuecos = -1;

  Hospital *actual = primerHospital;
  while (actual != NULL) {
    if (actual->estaActivo()) {
      int huecos = maxColaEspera - actual->getNumPacientesEnEspera();
      if (huecos > maxHuecos) {
        maxHuecos = huecos;
        mejor = actual;
      }
    }
    actual = actual->getSiguienteHospital();
  }

  return mejor;
}

int MonitorizacionHospitales::getNumHospitales() { return numHospitales; }

int MonitorizacionHospitales::getPosicionHospital(int idHospital) {
  int posicion = 1;
  Hospital *actual = primerHospital;
  while (actual != NULL) {
    if (actual->getIdHospital() == idHospital) {
      return posicion;
    }
    posicion++;
    actual = actual->getSiguienteHospital();
  }
  return -1;
}

bool MonitorizacionHospitales::crearHospital(cadena nombre, int idHospital,
                                             int maxCamas, int codPostal,
                                             cadena tipo) {
  if (existeHospital(idHospital)) {
    return false;
  }

  Hospital *nuevo = new Hospital(nombre, idHospital, maxCamas, codPostal, tipo);
  if (nuevo == NULL) {
    return false;
  }

  if (primerHospital == NULL) {
    primerHospital = nuevo;
  } else {
    Hospital *actual = primerHospital;
    while (actual->getSiguienteHospital() != NULL) {
      actual = actual->getSiguienteHospital();
    }
    actual->setSiguienteHospital(nuevo);
  }

  numHospitales++;
  return true;
}

bool MonitorizacionHospitales::eliminarHospital(int idHospital) {
  Hospital *actual = primerHospital;
  Hospital *anterior = NULL;

  while (actual != NULL && actual->getIdHospital() != idHospital) {
    anterior = actual;
    actual = actual->getSiguienteHospital();
  }

  if (actual == NULL || !actual->estaInactivo()) {
    return false;
  }

  if (anterior == NULL) {
    primerHospital = actual->getSiguienteHospital();
  } else {
    anterior->setSiguienteHospital(actual->getSiguienteHospital());
  }

  delete actual;
  numHospitales--;
  return true;
}

bool MonitorizacionHospitales::activarHospital(int idHospital) {
  Hospital *hospital = buscarHospital(idHospital);
  if (hospital == NULL || hospital->estaActivo()) {
    return false;
  }

  if (!hospital->activar()) {
    return false;
  }

  while (colaGlobal.longitudcolapri() > 0 &&
         hospital->getNumPacientesIngresados() < hospital->getMaxCamas()) {
    Paciente p;
    p = colaGlobal.consultarcolapri();
    colaGlobal.sacarcolapri();
    if (!hospital->ingresarPaciente(p)) {
      colaGlobal.insertarcolapri(p, p.gravedad);
      break;
    }
  }

  while (colaGlobal.longitudcolapri() > 0 &&
         hospital->getNumPacientesEnEspera() < maxColaEspera) {
    Paciente p;
    p = colaGlobal.consultarcolapri();
    colaGlobal.sacarcolapri();
    if (!hospital->ingresarPaciente(p)) {
      colaGlobal.insertarcolapri(p, p.gravedad);
      break;
    }
  }

  return true;
}

bool MonitorizacionHospitales::declararSinSangre(int idHospital) {
  Hospital *hospital = buscarHospital(idHospital);
  if (hospital == NULL || !hospital->estaActivo()) {
    return false;
  }

  int n = hospital->getNumPacientesEnEspera();
  Paciente *espera = NULL;
  if (n > 0) {
    espera = new Paciente[n];
    hospital->exportarPacientesEnEspera(espera);
  }

  if (!hospital->faltaSangre()) {
    if (espera != NULL) {
      delete[] espera;
    }
    return false;
  }

  if (espera != NULL) {
    for (int i = 0; i < n; i++) {
      cadena destino;
      bool enEspera = false;
      ingresarPacienteSistema(espera[i], destino, enEspera);
    }
    delete[] espera;
  }

  return true;
}

bool MonitorizacionHospitales::desactivarHospital(int idHospital) {
  Hospital *hospital = buscarHospital(idHospital);
  if (hospital == NULL || !hospital->estaActivo()) {
    return false;
  }

  int nIngresados = hospital->getNumPacientesIngresados();
  Paciente *ingresados = NULL;
  if (nIngresados > 0) {
    ingresados = new Paciente[nIngresados];
    hospital->exportarPacientesIngresados(ingresados);
  }

  int nEspera = hospital->getNumPacientesEnEspera();
  Paciente *espera = NULL;
  if (nEspera > 0) {
    espera = new Paciente[nEspera];
    hospital->exportarPacientesEnEspera(espera);
  }

  if (!hospital->desactivar()) {
    if (ingresados != NULL) {
      delete[] ingresados;
    }
    if (espera != NULL) {
      delete[] espera;
    }
    return false;
  }

  if (ingresados != NULL) {
    for (int i = 0; i < nIngresados; i++) {
      cadena destino;
      bool enEspera = false;
      ingresarPacienteSistema(ingresados[i], destino, enEspera);
    }
    delete[] ingresados;
  }

  if (espera != NULL) {
    for (int i = 0; i < nEspera; i++) {
      cadena destino;
      bool enEspera = false;
      ingresarPacienteSistema(espera[i], destino, enEspera);
    }
    delete[] espera;
  }

  return true;
}

bool MonitorizacionHospitales::modificarCamasHospital(int idHospital,
                                                      int maxCamas) {
  Hospital *hospital = buscarHospital(idHospital);
  if (hospital == NULL) {
    return false;
  }

  return hospital->setMaxCamas(maxCamas);
}

bool MonitorizacionHospitales::ingresarPacienteSistema(Paciente p,
                                                       cadena &lugarDestino,
                                                       bool &enEspera) {
  cadena lugarActual;
  if (existePaciente(p.historialClinico, lugarActual)) {
    return false;
  }

  Hospital *mejorCamas = buscarHospitalConMasCamasLibres();
  if (mejorCamas != NULL) {
    if (mejorCamas->ingresarPaciente(p)) {
      mejorCamas->getNombreHospital(lugarDestino);
      enEspera = false;
      return true;
    }
  }

  Hospital *mejorEspera = buscarHospitalParaEspera();
  if (mejorEspera != NULL) {
    if (mejorEspera->ingresarPaciente(p)) {
      mejorEspera->getNombreHospital(lugarDestino);
      enEspera = true;
      return true;
    }
  }

  colaGlobal.insertarcolapri(p, p.gravedad);
  strcpy(lugarDestino, "cola de espera global");
  enEspera = true;
  return true;
}

bool MonitorizacionHospitales::bajaPacienteSistema(int idPaciente,
                                                   cadena &lugarOrigen) {
  cadena lugar;
  if (!existePaciente(idPaciente, lugar)) {
    return false;
  }

  if (strcmp(lugar, "cola de espera global") == 0) {
    if (!colaGlobal.buscar(idPaciente)) {
      return false;
    }
    strcpy(lugarOrigen, "cola de espera global");
    return true;
  }

  Hospital *hospital = buscarHospitalConPaciente(idPaciente);
  if (hospital == NULL) {
    return false;
  }

  if (hospital->buscarPaciente(idPaciente)) {
    if (!hospital->bajaPaciente(idPaciente)) {
      return false;
    }
    hospital->getNombreHospital(lugarOrigen);

    if (colaGlobal.longitudcolapri() > 0 &&
        hospital->getNumPacientesEnEspera() < maxColaEspera) {
      Paciente p = colaGlobal.consultarcolapri();
      colaGlobal.sacarcolapri();
      if (!hospital->ingresarPaciente(p)) {
        colaGlobal.insertarcolapri(p, p.gravedad);
      }
    }
    return true;
  }

  if (hospital->buscarPaciente(idPaciente)) {
    if (!hospital->bajaPaciente(idPaciente)) {
      return false;
    }
    hospital->getNombreHospital(lugarOrigen);
    return true;
  }

  return false;
}

void MonitorizacionHospitales::mostrarInformacionHospitales(int pos) {
  if (numHospitales == 0) {
    cout << "No hay hospitales registrados." << endl;
    return;
  }

  if (pos == -1) {
    Hospital *actual = primerHospital;
    while (actual != NULL) {
      actual->mostrarInformacion();
      cout << "------------------------------" << endl;
      actual = actual->getSiguienteHospital();
    }
    return;
  }

  int posicion = 1;
  Hospital *actual = primerHospital;
  while (actual != NULL) {
    if (posicion == pos) {
      actual->mostrarInformacion();
      cout << "Pacientes ingresados:" << endl;
      actual->mostrarPacientesIngresados();
      cout << "Pacientes en espera:" << endl;
      actual->mostrarPacientesEnEspera();
      return;
    }
    posicion++;
    actual = actual->getSiguienteHospital();
  }

  cout << "Error: posicion de hospital invalida." << endl;
}

void MonitorizacionHospitales::mostrarInformacionColaGlobal() {
  if (colaGlobal.longitudcolapri() == 0) {
    cout << "La cola global est\u00e1 vac\u00eda." << endl;
    return;
  }

  Paciente *global = new Paciente[colaGlobal.longitudcolapri()];
  colaGlobal.exportar(global);
  for (int i = 0; i < colaGlobal.longitudcolapri(); i++) {
    cout << "- " << global[i].historialClinico << " | "
         << global[i].nombreCompleto << " | gravedad " << global[i].gravedad
         << endl;
  }
  delete[] global;
}
