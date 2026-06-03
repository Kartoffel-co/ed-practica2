#define MAXcolas 5
#include "cola.h"
class colapri {
  cola tabla[MAXcolas];

public:
  colapri();                               // crea una cola vacía
  void insertarcolapri(Paciente i, int p); // 0<=p<=9
  void sacarcolapri();                     /*Devuelve una colapri sin el
                       elemento de mayor prioridad. Si hay varios con la
                       misma prioridad saldrá aquel que lleve más tiempo
                       en la colapri*/
  Paciente consultarcolapri();             /*Devuelve el elemento de
               mayor prioridad almacenado en la colapri original
               sin quitarlo. Si hay varios con la misma
               prioridad saldrá aquel que lleve más tiempo en la
               colapri*/
  bool esvaciacolapri();
  int longitudcolapri();
  cola consultarcola(int p); // devuelve una cola segun su prioridad
  int getmaxcolas();
  bool buscar(int idPaciente); // busca paciente por id
  void exportar(Paciente *p);
};
