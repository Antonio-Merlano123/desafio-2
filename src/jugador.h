#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>

using namespace std;

class jugador {
public:
    jugador();
    jugador(string nombreinicial, string equipoinicial, string posicioninicial);

    string getnombre() const;
    string getequipo() const;
    string getposicion() const;
    int getgoles() const;
    int getasistencias() const;
    int getpartidos() const;

    void setnombre(string nuevonombre);
    void setequipo(string nuevoequipo);
    void setposicion(string nuevaposicion);
    void agregargol();
    void agregarasistencia();
    void agregarpartido();

private:
    string nombre;
    string equipo;
    string posicion;
    int goles;
    int asistencias;
    int partidos;
};

#endif // JUGADOR_H
