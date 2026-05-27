#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

typedef char cadena[50];

struct Paciente {
  cadena nombreCompleto; // Nombre completo de la persona registrada.
  int historialClinico;
  // Identificador númerico único del paciente utilizado para identificar a los
  // pacientes.
  char tipoSangre[3];
  // Cadena que guarda los valores de la sangre de los usuarios,
  // valores posibles: "A"; "AB"; "O".
  int gravedad; // Nivel de gravedad de la patología del paciente (escala de 1 a
                // 5,
  // donde 1 indica menor gravedad y 5 mayor gravedad).
  cadena patologia;
  // Nombre de la enfermedad o problema que presenta el paciente.
};

#endif
