#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "repositorio.h"

class Simulador {
public:
    Simulador();
    void probar(const Repositorio& repo);

private:
    double calcularlambda(double golesfavora, double golescontrab) const;
    int redondeargoles(double lambda) const;
};

#endif // SIMULADOR_H
