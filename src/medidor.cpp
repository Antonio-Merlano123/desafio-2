#include "medidor.h"

#include <iostream>

using namespace std;

// el medidor no necesita nada al crearse, solo existe pa imprimir metricas
Medidor::Medidor() {
}

// mensaje de cierre del modulo, confirma que no hubo errores fatales
void Medidor::mostrar() {
    cout << "Modulo metrics listo" << endl;
}

// imprime las metricas de una funcionalidad especifica del torneo
// nombre: como se llama la funcionalidad (ej: "II - conformacion grupos")
// iteraciones: cuantas veces se recorren datos aproximadamente en esa etapa
// memoria: cuantos bytes de memoria estima que usa esa etapa
// nota: estas son estimaciones calculadas, no medicion real de tiempo de CPU
void Medidor::mostrarfuncionalidad(string nombre, long long iteraciones, size_t memoria) const {
    cout << "metricas -> " << nombre << endl;
    cout << "  iteraciones aprox: " << iteraciones << endl;
    cout << "  memoria aprox (bytes): " << memoria << endl;
}
