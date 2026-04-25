#include "simulador.h"

#include <iostream>

using namespace std;

Simulador::Simulador() {
}

double Simulador::calculargolescalafavor(int ranking) const {
    if (ranking <= 0) {
        return 1.4;
    }

    if (ranking <= 8) {
        return 2.1;
    }

    if (ranking <= 20) {
        return 1.8;
    }

    if (ranking <= 35) {
        return 1.5;
    }

    return 1.3;
}

double Simulador::calculargolescalacontra(int ranking) const {
    if (ranking <= 0) {
        return 1.5;
    }

    if (ranking <= 8) {
        return 0.9;
    }

    if (ranking <= 20) {
        return 1.1;
    }

    if (ranking <= 35) {
        return 1.4;
    }

    return 1.6;
}

double Simulador::calcularlambda(int rankinga, int rankingb) const {
    double alpha = 0.6;
    double beta = 0.4;
    double mu = 1.35;

    double gfa = calculargolescalafavor(rankinga);
    double gcb = calculargolescalacontra(rankingb);

    if (gcb <= 0.0) {
        gcb = 1.0;
    }

    double lambda = alpha * (gfa / gcb) + beta * mu;

    if (lambda < 0.2) {
        lambda = 0.2;
    }

    return lambda;
}

int Simulador::redondeargoles(double lambda) const {
    int goles = int(lambda + 0.5);

    if (goles < 0) {
        goles = 0;
    }

    return goles;
}

void Simulador::probar(const Repositorio& repo) {
    cout << "Modulo sim listo" << endl;

    if (repo.getcantidadequipos() < 2) {
        return;
    }

    string equipoa = repo.getequipo(0);
    string equipob = repo.getequipo(1);
    int rankinga = repo.getranking(0);
    int rankingb = repo.getranking(1);

    double lambdaa = calcularlambda(rankinga, rankingb);
    double lambdab = calcularlambda(rankingb, rankinga);

    int golesa = redondeargoles(lambdaa);
    int golesb = redondeargoles(lambdab);

    cout << "lambda base prueba" << endl;
    cout << "  " << equipoa << " vs " << equipob << endl;
    cout << "  lambda " << equipoa << ": " << lambdaa << endl;
    cout << "  lambda " << equipob << ": " << lambdab << endl;
    cout << "  marcador estimado: " << golesa << " - " << golesb << endl;
}
