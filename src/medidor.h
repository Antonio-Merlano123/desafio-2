#ifndef MEDIDOR_H
#define MEDIDOR_H

#include <cstddef>
#include <string>

using namespace std;

class Medidor {
public:
    // salida simple de metricas del proyecto
    Medidor();
    void mostrar();
    void mostrarfuncionalidad(string nombre, long long iteraciones, size_t memoria) const;
};

#endif // MEDIDOR_H
