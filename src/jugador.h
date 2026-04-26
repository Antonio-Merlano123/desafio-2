#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>

using namespace std;

class jugador {
public:
    // jugador con stats acumuladas del torneo
    jugador();
    jugador(string nombreinicial, string equipoinicial, string posicioninicial, int camisetainicial);

    string getnombre() const;
    string getequipo() const;
    string getposicion() const;
    int getcamiseta() const;
    int getgoles() const;
    int getrojas() const;
    int getamarillas() const;
    int getfaltas() const;
    int getminutosjugados() const;
    int getasistencias() const;
    int getpartidos() const;

    void setnombre(string nuevonombre);
    void setequipo(string nuevoequipo);
    void setposicion(string nuevaposicion);
    void setcamiseta(int nuevacamiseta);
    void agregargol();
    void agregarroja();
    void agregaramarilla();
    void agregarfalta();
    void sumarminutos(int minutos);
    void agregarasistencia();
    void agregarpartido();

private:
    // info fija + contadores
    string nombre;
    string equipo;
    string posicion;
    int camiseta;
    int goles;
    int rojas;
    int amarillas;
    int faltas;
    int minutosjugados;
    int asistencias;
    int partidos;
};

#endif // JUGADOR_H
