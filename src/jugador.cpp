#include "jugador.h"

#include <ostream>

jugador::jugador() {
    // default simple pa objetos temporales
    nombre = "sin nombre";
    equipo = "sin equipo";
    posicion = "delantero";
    camiseta = 0;
    goles = 0;
    rojas = 0;
    amarillas = 0;
    faltas = 0;
    minutosjugados = 0;
    asistencias = 0;
    partidos = 0;
}

jugador::jugador(string nombreinicial, string equipoinicial, string posicioninicial, int camisetainicial) {
    nombre = nombreinicial;
    equipo = equipoinicial;
    posicion = posicioninicial;
    camiseta = camisetainicial;
    goles = 0;
    rojas = 0;
    amarillas = 0;
    faltas = 0;
    minutosjugados = 0;
    asistencias = 0;
    partidos = 0;
}

string jugador::getnombre() const {
    return nombre;
}

string jugador::getequipo() const {
    return equipo;
}

string jugador::getposicion() const {
    return posicion;
}

int jugador::getcamiseta() const {
    return camiseta;
}

int jugador::getgoles() const {
    return goles;
}

int jugador::getrojas() const {
    return rojas;
}

int jugador::getamarillas() const {
    return amarillas;
}

int jugador::getfaltas() const {
    return faltas;
}

int jugador::getminutosjugados() const {
    return minutosjugados;
}

int jugador::getasistencias() const {
    return asistencias;
}

int jugador::getpartidos() const {
    return partidos;
}

void jugador::setnombre(string nuevonombre) {
    nombre = nuevonombre;
}

void jugador::setequipo(string nuevoequipo) {
    equipo = nuevoequipo;
}

void jugador::setposicion(string nuevaposicion) {
    posicion = nuevaposicion;
}

void jugador::setcamiseta(int nuevacamiseta) {
    camiseta = nuevacamiseta;
}

void jugador::agregargol() {
    goles = goles + 1;
}

void jugador::agregarroja() {
    rojas = rojas + 1;
}

void jugador::agregaramarilla() {
    amarillas = amarillas + 1;
}

void jugador::agregarfalta() {
    faltas = faltas + 1;
}

void jugador::sumarminutos(int minutos) {
    // no valido negativo aca, lo controla quien llama
    minutosjugados = minutosjugados + minutos;
}

void jugador::agregarasistencia() {
    asistencias = asistencias + 1;
}

void jugador::agregarpartido() {
    partidos = partidos + 1;
}

ostream& operator<<(ostream& salida, const jugador& j) {
    salida << j.nombre
           << " - " << j.equipo
           << " (#" << j.camiseta << ", "
           << j.posicion << ", "
           << j.goles << " goles)";
    return salida;
}
