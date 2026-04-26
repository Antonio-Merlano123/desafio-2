#include "simulador.h"

#include <cmath>
#include <iostream>

using namespace std;

Simulador::Simulador() {
}

double Simulador::calcularlambda(double golesfavora, double golescontrab) const {
    // Valores fijos del enunciado: se da un poco mas de peso al ataque que a la defensa.
    double alpha = 0.6;
    double beta = 0.4;
    double mu = 1.35;

    double gfa = golesfavora;
    double gcb = golescontrab;

    if (gfa <= 0.0) {
        gfa = mu;
    }

    if (gcb <= 0.0) {
        gcb = mu;
    }

    double factorataque = pow(gfa / mu, alpha);
    double factordefensa = pow(gcb / mu, beta);
    double lambda = mu * factorataque * factordefensa;

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
    double gfahistorico = repo.getgolesfavorhistorico(0);
    double gcbhistorico = repo.getgolescontrahistorico(1);
    double gfbhistorico = repo.getgolesfavorhistorico(1);
    double gcahistorico = repo.getgolescontrahistorico(0);

    double lambdaa = calcularlambda(gfahistorico, gcbhistorico);
    double lambdab = calcularlambda(gfbhistorico, gcahistorico);

    int golesa = redondeargoles(lambdaa);
    int golesb = redondeargoles(lambdab);

    cout << "lambda base prueba" << endl;
    cout << "  " << equipoa << " vs " << equipob << endl;
    cout << "  promedio de gol (\u03BB) " << equipoa << ": " << lambdaa << endl;
    cout << "  promedio de gol (\u03BB) " << equipob << ": " << lambdab << endl;
    cout << "  marcador estimado: " << golesa << " - " << golesb << endl;
}
