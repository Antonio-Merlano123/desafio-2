#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "repositorio.h"

class Simulador {
public:
    Simulador();
    void probar(const Repositorio& repo);

private:
    double calculargolescalafavor(int ranking) const;
    double calculargolescalacontra(int ranking) const;
    double calcularlambda(int rankinga, int rankingb) const;
    int redondeargoles(double lambda) const;
};

#endif // SIMULADOR_H
