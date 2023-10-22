#pragma once

/**
 * @brief Macro que declara y define constructores y operadores de asignación para una clase.
 *
 * Esta macro genera de manera conveniente las declaraciones y definiciones de los constructores,
 * operadores de asignación y el constructor de movimiento (move constructor) para una clase determinada.
 *
 * @param Class Nombre de la clase.
 * @param Action Acción a realizar para los constructores y operadores. Puede ser 'delete' o 'default'.
 */
#define DECLARE_RULE4(Class, Action) \
  Class(const Class& other) = Action;\
  Class(Class&& other) = Action; \
  Class& operator= (const Class& other) = Action;\
  Class& operator= (Class&& other) = Action

/**
 * @brief Macro que deshabilita la copia de objetos de una clase.
 *
 * Esta macro utiliza la macro DECLARE_RULE4 con el argumento 'delete', lo que elimina las funciones
 * de copia de la clase, evitando así la copia de objetos.
 *
 * @param Class Nombre de la clase.
 */
#define DISABLE_COPY(Class) \
  DECLARE_RULE4(Class, delete);
