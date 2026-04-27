#include "torneo.h"

// para calculos matematicos como pow() y exp()
#include <cmath>
// para rand() y srand()
#include <cstdlib>
// para time() que sirve como semilla del random
#include <ctime>
#include <iostream>

#include "repositorio.h"

using namespace std;

// pasa texto a mayusculas pa comparar nombres sin distinguir mayus/minus
static string convertiramayuscula(string texto) {
    string salida = texto;

    for (int i = 0; i < int(salida.size()); i = i + 1) {
        char c = salida[i];
        if (c >= 'a' && c <= 'z') {
            salida[i] = char(c - ('a' - 'A'));
        }
    }

    return salida;
}

// revisa si el equipo es la sede (Estados Unidos 2026), busco varias formas del nombre
static bool eshostmundial(string nombreequipo) {
    string normal = convertiramayuscula(nombreequipo);

    if (normal.find("ESTADOS UNIDOS") != string::npos) {
        return true;
    }

    if (normal.find("UNITED STATES") != string::npos) {
        return true;
    }

    if (normal == "USA") {
        return true;
    }

    return false;
}

static string dosdigitos(int numero) {
    if (numero < 10) {
        return string("0") + char('0' + numero);
    }

    int decenas = numero / 10;
    int unidades = numero % 10;
    string texto = "";
    texto = texto + char('0' + decenas);
    texto = texto + char('0' + unidades);
    return texto;
}

// plantilla simple para limitar cualquier tipo comparable a un rango
template <typename T>
static T limitarenrango(T valor, T minimo, T maximo) {
    if (valor < minimo) {
        return minimo;
    }

    if (valor > maximo) {
        return maximo;
    }

    return valor;
}

// arranco todo en 0 para que el destructor no intente liberar punteros basura
// la semilla basada en la hora hace que cada ejecucion de resultados distintos
Torneo::Torneo() {
    nombretorneo = "UdeAWorldCup";
    grupos = 0;
    cantidadgrupos = 0;
    tabla = 0;
    cantidadfilastabla = 0;
    equiposcargados = 0;
    jugadoresbase = 0;
    cantidadjugadores = 0;
    capacidadjugadores = 0;
    equiposbase = 0;
    confederacionesbase = 0;
    rankingsbase = 0;
    cantidadequiposbase = 0;
    partidosgrupos = 0;
    diapartidosgrupos = 0;
    cantidadpartidosgrupos = 0;
    capacidadpartidosgrupos = 0;
    cantclasificados1 = 0;
    cantclasificados2 = 0;
    cantclasificados3 = 0;
    partidosdieciseisavos = 0;
    cantdieciseisavos = 0;
    partidosoctavos = 0;
    cantoctavos = 0;
    partidoscuartos = 0;
    cantcuartos = 0;
    partidossemis = 0;
    cantsemis = 0;
    equipocampeon = "";
    equiposubcampeon = "";
    equipotercero = "";
    equipocuarto = "";
    finalessimuladas = false;

    srand(unsigned(time(0)));  // semilla con hora actual = sorteos distintos cada vez
}

// libera toda la memoria pedida con new, sin esto quedaria memory leak al cerrar
Torneo::~Torneo() {
    if (grupos != 0) {
        delete[] grupos;
        grupos = 0;
    }

    if (tabla != 0) {
        delete[] tabla;
        tabla = 0;
    }

    if (jugadoresbase != 0) {
        delete[] jugadoresbase;
        jugadoresbase = 0;
    }

    if (equiposbase != 0) {
        delete[] equiposbase;
        equiposbase = 0;
    }

    if (confederacionesbase != 0) {
        delete[] confederacionesbase;
        confederacionesbase = 0;
    }

    if (rankingsbase != 0) {
        delete[] rankingsbase;
        rankingsbase = 0;
    }

    if (partidosgrupos != 0) {
        delete[] partidosgrupos;
        partidosgrupos = 0;
    }

    if (diapartidosgrupos != 0) {
        delete[] diapartidosgrupos;
        diapartidosgrupos = 0;
    }

    if (partidosdieciseisavos != 0) {
        delete[] partidosdieciseisavos;
        partidosdieciseisavos = 0;
    }

    if (partidosoctavos != 0) {
        delete[] partidosoctavos;
        partidosoctavos = 0;
    }

    if (partidoscuartos != 0) {
        delete[] partidoscuartos;
        partidoscuartos = 0;
    }

    if (partidossemis != 0) {
        delete[] partidossemis;
        partidossemis = 0;
    }
}

// crea los 12 grupos vacios, nombrados grupo a hasta grupo l
void Torneo::preparar() {
    iniciargrupos(12);  // 12 grupos para 48 equipos, 4 por grupo

    for (int i = 0; i < cantidadgrupos; i = i + 1) {
        // 'a' + 0 = 'a', 'a' + 1 = 'b', etc. — aritmetica de chars
        string nombregrupo = "grupo ";
        char letra = char('a' + i);
        nombregrupo = nombregrupo + letra;
        registrargrupobase(i, nombregrupo);
    }

    cout << "torneo base listo: " << nombretorneo << endl;
}

void Torneo::iniciargrupos(int cantidad) {
    if (grupos != 0) {
        delete[] grupos;
        grupos = 0;
    }

    if (tabla != 0) {
        delete[] tabla;
        tabla = 0;
    }

    if (jugadoresbase != 0) {
        delete[] jugadoresbase;
        jugadoresbase = 0;
    }

    if (equiposbase != 0) {
        delete[] equiposbase;
        equiposbase = 0;
    }

    if (confederacionesbase != 0) {
        delete[] confederacionesbase;
        confederacionesbase = 0;
    }

    if (rankingsbase != 0) {
        delete[] rankingsbase;
        rankingsbase = 0;
    }

    if (partidosgrupos != 0) {
        delete[] partidosgrupos;
        partidosgrupos = 0;
    }

    if (diapartidosgrupos != 0) {
        delete[] diapartidosgrupos;
        diapartidosgrupos = 0;
    }

    int cantidadfinal = cantidad;
    if (cantidadfinal < 0) {
        cantidadfinal = 0;
    }

    cantidadgrupos = cantidadfinal;
    grupos = new grupo[cantidadgrupos];

    cantidadfilastabla = cantidadgrupos * 4;
    tabla = new tablaposiciones[cantidadfilastabla];
    equiposcargados = 0;
    capacidadjugadores = cantidadfilastabla * 15;
    cantidadjugadores = 0;

    if (capacidadjugadores > 0) {
        jugadoresbase = new jugador[capacidadjugadores];
    }

    if (cantidadfilastabla > 0) {
        equiposbase = new string[cantidadfilastabla];
        confederacionesbase = new string[cantidadfilastabla];
        rankingsbase = new int[cantidadfilastabla];

        for (int i = 0; i < cantidadfilastabla; i = i + 1) {
            equiposbase[i] = "";
            confederacionesbase[i] = "";
            rankingsbase[i] = 0;
        }
    }

    cantidadequiposbase = 0;
    cantidadpartidosgrupos = 0;
    capacidadpartidosgrupos = cantidadgrupos * 6;

    if (capacidadpartidosgrupos > 0) {
        partidosgrupos = new partido[capacidadpartidosgrupos];
        diapartidosgrupos = new int[capacidadpartidosgrupos];

        for (int i = 0; i < capacidadpartidosgrupos; i = i + 1) {
            diapartidosgrupos[i] = -1;
        }
    }
}

bool Torneo::registrargrupobase(int indice, string nombregrupo) {
    if (indice < 0) {
        return false;
    } else {
        if (indice >= cantidadgrupos) {
            return false;
        }
    }

    grupos[indice].setnombre(nombregrupo);
    return true;
}

bool Torneo::cargarequipotabla(int fila, string nombreequipo) {
    if (fila < 0) {
        return false;
    }

    if (fila >= cantidadfilastabla) {
        return false;
    }

    tabla[fila].cargarequipo(nombreequipo);
    return true;
}

bool Torneo::cargarequipobase(int indice, string nombreequipo) {
    return cargarequipobase(indice, nombreequipo, "", 0);
}

bool Torneo::cargarequipobase(int indice, string nombreequipo, string confederacion, int ranking) {
    if (indice < 0) {
        return false;
    }

    if (indice >= cantidadfilastabla) {
        return false;
    }

    bool okfila = cargarequipotabla(indice, nombreequipo);
    if (okfila == false) {
        return false;
    }

    if (equiposbase == 0 || confederacionesbase == 0 || rankingsbase == 0) {
        return false;
    }

    equiposbase[indice] = nombreequipo;
    confederacionesbase[indice] = confederacion;
    rankingsbase[indice] = ranking;

    if (equiposcargados < indice + 1) {
        equiposcargados = indice + 1;
    }

    if (cantidadequiposbase < indice + 1) {
        cantidadequiposbase = indice + 1;
    }

    return true;
}

int Torneo::getequiposcargados() const {
    return equiposcargados;
}

bool Torneo::cargarjugadorbase(jugador nuevojugador) {
    if (jugadoresbase == 0) {
        return false;
    }

    if (cantidadjugadores >= capacidadjugadores) {
        return false;
    }

    jugadoresbase[cantidadjugadores] = nuevojugador;
    cantidadjugadores = cantidadjugadores + 1;
    return true;
}

int Torneo::getcantidadjugadores() const {
    return cantidadjugadores;
}

int Torneo::getcantidadgrupos() const {
    return cantidadgrupos;
}

// ordena por ranking, el numero mas bajo es el mejor equipo
void Torneo::ordenarporelranking(int indices[], int total) const {
    // bubble sort, pa 48 equipos es mas que suficiente
    for (int i = 0; i < total; i = i + 1) {
        for (int j = i + 1; j < total; j = j + 1) {
            int ai = indices[i];
            int aj = indices[j];

            bool intercambiar = false;
            if (rankingsbase[aj] < rankingsbase[ai]) {
                intercambiar = true;
            }

            if (rankingsbase[aj] == rankingsbase[ai]) {
                if (equiposbase[aj] < equiposbase[ai]) {
                    intercambiar = true;
                }
            }

            if (intercambiar) {
                int temporal = indices[i];
                indices[i] = indices[j];
                indices[j] = temporal;
            }
        }
    }
}

// busca la sede en el arreglo, retorna -1 si no esta
int Torneo::buscarhost(int indices[], int total) const {
    // el host va directo al bombo 1 sin importar su ranking
    for (int i = 0; i < total; i = i + 1) {
        int indice = indices[i];
        if (eshostmundial(equiposbase[indice])) {
            return indice;
        }
    }

    return -1;
}

int Torneo::buscarindiceequipo(string nombreequipo) const {
    for (int i = 0; i < cantidadequiposbase; i = i + 1) {
        if (equiposbase[i] == nombreequipo) {
            return i;
        }
    }

    return -1;
}

int Torneo::buscarfilatabla(string nombreequipo) const {
    for (int i = 0; i < cantidadfilastabla; i = i + 1) {
        if (tabla[i].getnombre() == nombreequipo) {
            return i;
        }
    }

    return -1;
}

int Torneo::buscarindiceequiporepo(const Repositorio& repo, string nombreequipo) const {
    int total = repo.getcantidadequipos();

    for (int i = 0; i < total; i = i + 1) {
        if (repo.getequipo(i) == nombreequipo) {
            return i;
        }
    }

    return -1;
}

int Torneo::buscarjugadoresdelequipo(string nombreequipo, int indices[], int maxindices) const {
    if (jugadoresbase == 0) {
        return 0;
    }

    int guardados = 0;

    // saco indices de jugadores de ese equipo y ya
    for (int i = 0; i < cantidadjugadores; i = i + 1) {
        if (jugadoresbase[i].getequipo() != nombreequipo) {
            continue;
        }

        if (guardados < maxindices) {
            indices[guardados] = i;
            guardados = guardados + 1;
        }
    }

    return guardados;
}

// calculo de gol esperado: si un equipo ataca mejor y el rival defiende peor,
// el valor de lambda sube
double Torneo::calcularlambdapartido(double golesfavora, double golescontrab) const {
    double alpha = 0.6;  // el ataque propio pesa un poco mas
    double beta = 0.4;
    double mu = 1.35;    // promedio historico de goles en mundiales

    double factorataque = pow(golesfavora / mu, alpha);
    double factordefensa = pow(golescontrab / mu, beta);
    double lambda = mu * factorataque * factordefensa;

    return lambda;
}

// convierte lambda a goles enteros con el algoritmo de Poisson de Knuth:
// multiplica randoms entre 0 y 1 hasta bajar del umbral e^(-lambda)
// cuantas multiplicaciones se hagan - 1 es el numero de goles
int Torneo::redondeargolespartido(double lambda) const {
    // piso minimo por si lambda sale muy bajito
    if (lambda < 0.05) {
        lambda = 0.05;
    }

    double limite = exp(-lambda);  // umbral del metodo de Poisson
    double producto = 1.0;
    int k = 0;

    do {
        k = k + 1;
        // genero un numero entre 0 y 1 usando rand()
        // divido por 10000 para tener precision de 4 decimales
        double u = double(rand() % 10000) / 10000.0;
        if (u <= 0.0) {
            u = 0.0001;  // evito multiplicar por cero
        }
        producto = producto * u;
    } while (producto > limite);

    int goles = k - 1;  // el resultado de Poisson es k-1

    goles = limitarenrango(goles, 0, 6);  // tope pa no tener marcadores raros tipo 10-0

    return goles;
}

int Torneo::calcularposesionlocal(int rankinglocal, int rankingvisita) const {
    if (rankinglocal <= 0 || rankingvisita <= 0) {
        return 50;
    }

    double fuerzalocal = 1.0 / double(rankinglocal);
    double fuerzavisita = 1.0 / double(rankingvisita);
    double total = fuerzalocal + fuerzavisita;
    if (total <= 0.0) {
        return 50;
    }

    int posesion = int((100.0 * fuerzalocal / total) + 0.5);
    posesion = limitarenrango(posesion, 30, 70);
    return posesion;
}

string Torneo::construirfechagrupos(int dia) const {
    int diareal = 20 + dia;
    int mes = 6;
    if (diareal > 30) {
        diareal = diareal - 30;
        mes = 7;
    }

    string fecha = dosdigitos(diareal);
    fecha = fecha + "/";
    fecha = fecha + dosdigitos(mes);
    fecha = fecha + "/2026";
    return fecha;
}

// ordena las 4 filas del grupo: primero por puntos, luego diferencia, luego goles favor
// si todo sigue igual lo define un sorteo (igual que en el mundial real)
void Torneo::ordenarfilasgrupo(int filas[4]) const {
    for (int i = 0; i < 4; i = i + 1) {
        for (int j = i + 1; j < 4; j = j + 1) {
            int fi = filas[i];
            int fj = filas[j];

            bool intercambiar = false;

            if (tabla[fj].getpuntos() > tabla[fi].getpuntos()) {
                intercambiar = true;
            } else if (tabla[fj].getpuntos() == tabla[fi].getpuntos()) {
                if (tabla[fj].getdiferencia() > tabla[fi].getdiferencia()) {
                    intercambiar = true;
                } else if (tabla[fj].getdiferencia() == tabla[fi].getdiferencia()) {
                    if (tabla[fj].getgolesfavor() > tabla[fi].getgolesfavor()) {
                        intercambiar = true;
                    } else if (tabla[fj].getgolesfavor() == tabla[fi].getgolesfavor()) {
                        // ultimo criterio: sorteo real para que no sea siempre el mismo
                        int sorteo = rand() % 2;
                        if (sorteo == 1) {
                            intercambiar = true;
                        }
                    }
                }
            }

            if (intercambiar) {
                int temporal = filas[i];
                filas[i] = filas[j];
                filas[j] = temporal;
            }
        }
    }
}

void Torneo::barajarbombo(int bombo[], int inicio) const {
    for (int i = inicio; i < 12; i = i + 1) {
        int j = inicio + (rand() % (12 - inicio));
        int temporal = bombo[i];
        bombo[i] = bombo[j];
        bombo[j] = temporal;
    }
}

bool Torneo::intentarsorteo(int bombos[4][12]) {
    for (int g = 0; g < cantidadgrupos; g = g + 1) {
        grupos[g].limpiar();
    }

    for (int b = 0; b < 4; b = b + 1) {
        for (int g = 0; g < cantidadgrupos; g = g + 1) {
            int elegido = -1;

            for (int p = 0; p < 12; p = p + 1) {
                int indiceequipo = bombos[b][p];
                if (indiceequipo < 0) {
                    continue;
                }

                string conf = confederacionesbase[indiceequipo];
                if (grupos[g].puedeagregarconfederacion(conf)) {
                    elegido = p;
                    break;
                }
            }

            if (elegido < 0) {
                return false;
            }

            int indicefinal = bombos[b][elegido];
            grupos[g].agregarequipo(equiposbase[indicefinal], confederacionesbase[indicefinal]);

            for (int mover = elegido; mover < 11; mover = mover + 1) {
                bombos[b][mover] = bombos[b][mover + 1];
            }

            bombos[b][11] = -1;
        }
    }

    return true;
}

// sorteo con bombos: bombo 1 = top 12 (sede siempre ahi), bombos 2-4 el resto
// restriccion: no puede haber dos equipos de la misma confederacion en el mismo grupo
// intenta hasta 600 veces si hay conflicto de confederaciones
bool Torneo::armargruposporranking() {
    if (cantidadgrupos != 12) {
        return false;
    }

    if (cantidadequiposbase < 48) {
        return false;
    }

    // ordeno los 48 por ranking pa armar los bombos
    int ordenados[48];
    for (int i = 0; i < 48; i = i + 1) {
        ordenados[i] = i;
    }
    ordenarporelranking(ordenados, 48);

    int bombosbase[4][12];
    for (int b = 0; b < 4; b = b + 1) {
        for (int p = 0; p < 12; p = p + 1) {
            bombosbase[b][p] = -1;
        }
    }

    bool usado[48];
    for (int i = 0; i < 48; i = i + 1) {
        usado[i] = false;
    }

    // el host va directo al bombo 1, el resto del bombo 1 se llena con los mejores
    int host = buscarhost(ordenados, 48);
    int cursorb1 = 0;

    if (host >= 0) {
        bombosbase[0][cursorb1] = host;
        usado[host] = true;
        cursorb1 = cursorb1 + 1;
    }

    for (int i = 0; i < 48 && cursorb1 < 12; i = i + 1) {
        int indice = ordenados[i];
        if (usado[indice]) {
            continue;
        }

        bombosbase[0][cursorb1] = indice;
        usado[indice] = true;
        cursorb1 = cursorb1 + 1;
    }

    int bomboactual = 1;
    int posicionactual = 0;

    for (int i = 0; i < 48; i = i + 1) {
        int indice = ordenados[i];
        if (usado[indice]) {
            continue;
        }

        bombosbase[bomboactual][posicionactual] = indice;
        posicionactual = posicionactual + 1;

        if (posicionactual == 12) {
            posicionactual = 0;
            bomboactual = bomboactual + 1;
        }
    }

    // hasta 600 intentos: si un intento viola restricciones de confederacion, se descarta
    bool listo = false;

    for (int intento = 0; intento < 600; intento = intento + 1) {
        int bombosprueba[4][12];

        for (int b = 0; b < 4; b = b + 1) {
            for (int p = 0; p < 12; p = p + 1) {
                bombosprueba[b][p] = bombosbase[b][p];
            }
        }

        barajarbombo(bombosprueba[0], 1);
        barajarbombo(bombosprueba[1], 0);
        barajarbombo(bombosprueba[2], 0);
        barajarbombo(bombosprueba[3], 0);

        if (intentarsorteo(bombosprueba)) {
            listo = true;
            break;
        }
    }

    if (listo == false) {
        return false;
    }

    int fila = 0;
    for (int g = 0; g < cantidadgrupos; g = g + 1) {
        for (int e = 0; e < grupos[g].getcantidad(); e = e + 1) {
            cargarequipotabla(fila, grupos[g].getequipo(e));
            fila = fila + 1;
        }
    }

    return true;
}

void Torneo::mostrargrupos() const {
    cout << "grupos del torneo" << endl;

    for (int g = 0; g < cantidadgrupos; g = g + 1) {
        cout << grupos[g].getnombre() << endl;

        for (int e = 0; e < grupos[g].getcantidad(); e = e + 1) {
            cout << "  - " << grupos[g].getequipo(e);
            cout << " (" << grupos[g].getconfederacion(e) << ")" << endl;
        }
    }
}

bool Torneo::generarcalendarioconlimite(int maxpartidospordia, int descansominimo) {
    if (partidosgrupos == 0 || diapartidosgrupos == 0) {
        return false;
    }

    int pordia[17];
    for (int i = 0; i < 17; i = i + 1) {
        pordia[i] = 0;
    }

    int ultimodia[48];
    for (int i = 0; i < 48; i = i + 1) {
        ultimodia[i] = -100;
    }

    cantidadpartidosgrupos = 0;

    for (int g = 0; g < cantidadgrupos; g = g + 1) {
        if (grupos[g].getcantidad() != 4) {
            return false;
        }

        string e0 = grupos[g].getequipo(0);
        string e1 = grupos[g].getequipo(1);
        string e2 = grupos[g].getequipo(2);
        string e3 = grupos[g].getequipo(3);

        string local[6];
        string visita[6];

        local[0] = e0; visita[0] = e1;
        local[1] = e2; visita[1] = e3;
        local[2] = e0; visita[2] = e2;
        local[3] = e1; visita[3] = e3;
        local[4] = e0; visita[4] = e3;
        local[5] = e1; visita[5] = e2;

        for (int m = 0; m < 6; m = m + 1) {
            int ilocal = buscarindiceequipo(local[m]);
            int ivisita = buscarindiceequipo(visita[m]);

            if (ilocal < 0 || ivisita < 0) {
                return false;
            }

            int diaelegido = -1;

            for (int dia = 0; dia < 17; dia = dia + 1) {
                if (pordia[dia] >= maxpartidospordia) {
                    continue;
                }

                int descansolocal = dia - ultimodia[ilocal];
                int descansovisita = dia - ultimodia[ivisita];

                if (descansolocal < descansominimo) {
                    continue;
                }

                if (descansovisita < descansominimo) {
                    continue;
                }

                diaelegido = dia;
                break;
            }

            if (diaelegido < 0) {
                return false;
            }

            if (cantidadpartidosgrupos >= capacidadpartidosgrupos) {
                return false;
            }

            partidosgrupos[cantidadpartidosgrupos] = partido(local[m], visita[m]);
            partidosgrupos[cantidadpartidosgrupos].configurarcontexto("nombreSede",
                                                                       "codArbitro1",
                                                                       "codArbitro2",
                                                                       "codArbitro3",
                                                                       "00:00",
                                                                       construirfechagrupos(diaelegido));
            diapartidosgrupos[cantidadpartidosgrupos] = diaelegido;
            cantidadpartidosgrupos = cantidadpartidosgrupos + 1;

            pordia[diaelegido] = pordia[diaelegido] + 1;
            ultimodia[ilocal] = diaelegido;
            ultimodia[ivisita] = diaelegido;
        }
    }

    return true;
}

bool Torneo::generarcalendariogrupos() {
    // con 48 equipos hay 72 partidos; en 17 dias a maximo 4 por dia solo caben 68.
    // por eso, si falla el modo estricto, se usa 5 por dia manteniendo descanso de 3 dias.
    bool okestricto = generarcalendarioconlimite(4, 3);
    if (okestricto) {
        return true;
    }

    cout << "nota calendario: 72 partidos en 17 dias requiere al menos 5 partidos en algunos dias" << endl;
    bool okcinco = generarcalendarioconlimite(5, 3);
    if (okcinco) {
        return true;
    }

    cout << "nota calendario: para evitar bloqueo se relaja descanso minimo a 2 dias" << endl;
    return generarcalendarioconlimite(5, 2);
}

// simula los 72 partidos de grupos: lambda por equipo, goles con Poisson, estadisticas de jugadores
bool Torneo::simularfasegrupos(const Repositorio& repo) {
    if (cantidadpartidosgrupos <= 0) {
        return false;
    }

    // reseteo la tabla pa que no acumule partidos de ejecuciones viejas
    for (int i = 0; i < cantidadfilastabla; i = i + 1) {
        string nombre = tabla[i].getnombre();
        if (nombre != "") {
            tabla[i].cargarequipo(nombre);
        }
    }

    for (int i = 0; i < cantidadpartidosgrupos; i = i + 1) {
        string local = partidosgrupos[i].getlocal();
        string visita = partidosgrupos[i].getvisita();

        int ilocalrepo = buscarindiceequiporepo(repo, local);
        int ivisitarepo = buscarindiceequiporepo(repo, visita);
        int ilocaltabla = buscarfilatabla(local);
        int ivisitatabla = buscarfilatabla(visita);

        if (ilocalrepo < 0 || ivisitarepo < 0) {
            return false;
        }

        if (ilocaltabla < 0 || ivisitatabla < 0) {
            return false;
        }

        double gflocal = repo.getgolesfavorhistorico(ilocalrepo);
        double gclocal = repo.getgolescontrahistorico(ilocalrepo);
        double gfvisita = repo.getgolesfavorhistorico(ivisitarepo);
        double gcvisita = repo.getgolescontrahistorico(ivisitarepo);

        // cada equipo tiene su propio lambda segun su ataque vs la defensa del rival
        double lambdalocal = calcularlambdapartido(gflocal, gcvisita);
        double lambdavisita = calcularlambdapartido(gfvisita, gclocal);

        // goles con Poisson
        int goleslocal = redondeargolespartido(lambdalocal);
        int golesvisita = redondeargolespartido(lambdavisita);

        int rankinglocal = repo.getranking(ilocalrepo);
        int rankingvisita = repo.getranking(ivisitarepo);
        partidosgrupos[i].setposesionlocal(calcularposesionlocal(rankinglocal, rankingvisita));
        partidosgrupos[i].limpiargoleadores();
        partidosgrupos[i].setresultado(goleslocal, golesvisita);

        int oncelocalidx[11];
        int oncevisitaidx[11];
        bool okoncelocal = elegironceindices(local, oncelocalidx);
        bool okoncevisita = elegironceindices(visita, oncevisitaidx);
        if (okoncelocal == false || okoncevisita == false) {
            return false;
        }

        // actualizo estadisticas de los 22 jugadores que jugaron
        actualizarestadisticasjugadorespartido(oncelocalidx, goleslocal, 90, partidosgrupos[i], true);
        actualizarestadisticasjugadorespartido(oncevisitaidx, golesvisita, 90, partidosgrupos[i], false);

        // actualizo la tabla del grupo
        tabla[ilocaltabla].sumargoles(goleslocal, golesvisita);
        tabla[ivisitatabla].sumargoles(golesvisita, goleslocal);

        if (goleslocal > golesvisita) {
            tabla[ilocaltabla].sumarganado();
            tabla[ivisitatabla].sumarperdido();
        } else if (goleslocal < golesvisita) {
            tabla[ivisitatabla].sumarganado();
            tabla[ilocaltabla].sumarperdido();
        } else {
            // empate: cada uno gana 1 punto
            tabla[ilocaltabla].sumarempate();
            tabla[ivisitatabla].sumarempate();
        }
    }

    return true;
}

bool Torneo::elegironceinicial(string nombreequipo, jugador once[11]) const {
    int onceindices[11];
    bool ok = elegironceindices(nombreequipo, onceindices);
    if (ok == false) {
        return false;
    }

    for (int i = 0; i < 11; i = i + 1) {
        once[i] = jugadoresbase[onceindices[i]];
    }

    return true;
}

// elige 11 jugadores al azar del equipo con Fisher-Yates, simula la alineacion del tecnico
bool Torneo::elegironceindices(string nombreequipo, int onceindices[11]) const {
    int indices[32];
    int cantidad = buscarjugadoresdelequipo(nombreequipo, indices, 32);

    if (cantidad < 11) {
        return false;
    }

    for (int i = 0; i < cantidad; i = i + 1) {
        int j = i + (rand() % (cantidad - i));
        int temporal = indices[i];
        indices[i] = indices[j];
        indices[j] = temporal;
    }

    for (int i = 0; i < 11; i = i + 1) {
        onceindices[i] = indices[i];
    }

    return true;
}

// actualiza goles, asistencias, tarjetas y faltas de los 11 jugadores del partido
// goles se distribuyen uniformemente entre el once (segun enunciado del profe)
void Torneo::actualizarestadisticasjugadorespartido(int onceindices[11], int golesafavor, int minutos, partido& partidoref, bool eslocal) {
    if (jugadoresbase == 0) {
        return;
    }

    // recorro los 11 que jugaron
    for (int i = 0; i < 11; i = i + 1) {
        int idx = onceindices[i];
        if (idx < 0 || idx >= cantidadjugadores) {
            continue;  // indice invalido, lo salto
        }

        // suma el partido y los minutos
        jugadoresbase[idx].agregarpartido();
        jugadoresbase[idx].sumarminutos(minutos);

        // 6% de amarilla, y de esos un 1.15% se va doble amarilla+roja
        int r1 = rand() % 10000;
        if (r1 < 600) {  // 600/10000 = 6%
            jugadoresbase[idx].agregaramarilla();

            int r2 = rand() % 10000;
            if (r2 < 115) {  // 115/10000 = 1.15% de segunda amarilla y expulsion
                jugadoresbase[idx].agregaramarilla();
                jugadoresbase[idx].agregarroja();
            }
        }

        // faltas con probabilidades en cascada: 13% primera, 2.75% segunda, 0.7% tercera
        int f1 = rand() % 10000;
        if (f1 < 1300) {  // 1300/10000 = 13%
            jugadoresbase[idx].agregarfalta();

            int f2 = rand() % 10000;
            if (f2 < 275) {
                jugadoresbase[idx].agregarfalta();

                int f3 = rand() % 10000;
                if (f3 < 70) {
                    jugadoresbase[idx].agregarfalta();
                }
            }
        }
    }

    // regla del enunciado: evento de gol por jugador con probabilidad base del 4%
    int golesasignados = 0;
    int rondas = 0;

    while (golesasignados < golesafavor && rondas < 200) {
        for (int i = 0; i < 11 && golesasignados < golesafavor; i = i + 1) {
            int r = rand() % 100;
            if (r >= 4) {
                continue;
            }

            int anotadoridx = onceindices[i];
            if (anotadoridx < 0 || anotadoridx >= cantidadjugadores) {
                continue;
            }

            jugadoresbase[anotadoridx].agregargol();
            int camiseta = jugadoresbase[anotadoridx].getcamiseta();
            if (eslocal) {
                partidoref.agregargoleadorlocal(camiseta);
            } else {
                partidoref.agregargoleadorvisita(camiseta);
            }

            int asistpos = rand() % 11;
            if (asistpos == i) {
                asistpos = (asistpos + 1) % 11;
            }
            int asistidx = onceindices[asistpos];
            if (asistidx >= 0 && asistidx < cantidadjugadores) {
                jugadoresbase[asistidx].agregarasistencia();
            }

            golesasignados = golesasignados + 1;
        }

        rondas = rondas + 1;
    }

    // fallback para garantizar que se registren todos los goles del marcador
    while (golesasignados < golesafavor) {
        int anotadorpos = rand() % 11;
        int anotadoridx = onceindices[anotadorpos];
        if (anotadoridx < 0 || anotadoridx >= cantidadjugadores) {
            continue;
        }

        jugadoresbase[anotadoridx].agregargol();
        int camiseta = jugadoresbase[anotadoridx].getcamiseta();
        if (eslocal) {
            partidoref.agregargoleadorlocal(camiseta);
        } else {
            partidoref.agregargoleadorvisita(camiseta);
        }

        int asistpos = rand() % 11;
        if (asistpos == anotadorpos) {
            asistpos = (asistpos + 1) % 11;
        }
        int asistidx = onceindices[asistpos];
        if (asistidx >= 0 && asistidx < cantidadjugadores) {
            jugadoresbase[asistidx].agregarasistencia();
        }

        golesasignados = golesasignados + 1;
    }
}

void Torneo::imprimirgoleadorescamisetas(const partido& p) const {
    cout << "    goleadores local (camisetas): ";
    if (p.getcantgoleadoreslocal() == 0) {
        cout << "ninguno";
    } else {
        for (int i = 0; i < p.getcantgoleadoreslocal(); i = i + 1) {
            if (i > 0) {
                cout << ", ";
            }
            cout << p.getgoleadorlocal(i);
        }
    }
    cout << endl;

    cout << "    goleadores visita (camisetas): ";
    if (p.getcantgoleadoresvisita() == 0) {
        cout << "ninguno";
    } else {
        for (int i = 0; i < p.getcantgoleadoresvisita(); i = i + 1) {
            if (i > 0) {
                cout << ", ";
            }
            cout << p.getgoleadorvisita(i);
        }
    }
    cout << endl;
}

void Torneo::imprimirdatospartido(const partido& p, bool conmarcador) const {
    cout << "    sede: " << p.getsede() << endl;
    cout << "    arbitros: " << p.getarbitro(0) << ", " << p.getarbitro(1) << ", " << p.getarbitro(2) << endl;
    cout << "    fecha: " << p.getfecha() << " hora: " << p.gethora() << endl;
    cout << "    posesion: " << p.getposesionlocal() << "% - " << p.getposesionvisita() << "%" << endl;
    if (conmarcador) {
        cout << "    marcador: " << p.getlocal() << " " << p.getgoleslocal() << " - " << p.getgolesvisita() << " " << p.getvisita() << endl;
        imprimirgoleadorescamisetas(p);
    }
}

void Torneo::mostrarcalendariogrupos() const {
    if (cantidadpartidosgrupos <= 0) {
        return;
    }

    cout << "calendario fase de grupos" << endl;

    for (int dia = 0; dia < 17; dia = dia + 1) {
        bool tienepartidos = false;

        for (int i = 0; i < cantidadpartidosgrupos; i = i + 1) {
            if (diapartidosgrupos[i] == dia) {
                tienepartidos = true;
                break;
            }
        }

        if (tienepartidos == false) {
            continue;
        }

        cout << "dia " << (dia + 1) << endl;

        for (int i = 0; i < cantidadpartidosgrupos; i = i + 1) {
            if (diapartidosgrupos[i] != dia) {
                continue;
            }

            cout << "  - " << partidosgrupos[i].getlocal();
            cout << " vs " << partidosgrupos[i].getvisita() << endl;
            imprimirdatospartido(partidosgrupos[i], false);
        }
    }
}

void Torneo::mostrarresultadosfasegrupos() const {
    if (cantidadpartidosgrupos <= 0) {
        return;
    }

    cout << "resultados fase de grupos" << endl;
    for (int i = 0; i < cantidadpartidosgrupos; i = i + 1) {
        cout << "  partido " << (i + 1) << endl;
        imprimirdatospartido(partidosgrupos[i], true);
    }
}

void Torneo::mostraronceprueba() const {
    if (cantidadpartidosgrupos <= 0) {
        return;
    }

    string local = partidosgrupos[0].getlocal();
    string visita = partidosgrupos[0].getvisita();

    jugador oncelocal[11];
    jugador oncevisita[11];

    bool oklocal = elegironceinicial(local, oncelocal);
    bool okvisita = elegironceinicial(visita, oncevisita);

    if (oklocal == false || okvisita == false) {
        cout << "once inicial prueba: fallo" << endl;
        return;
    }

    cout << "once inicial prueba" << endl;
    cout << "  partido: " << local << " vs " << visita << endl;

    cout << "  titulares " << local << ":" << endl;
    for (int i = 0; i < 11; i = i + 1) {
        cout << "    - " << oncelocal[i].getnombre();
        cout << " (" << oncelocal[i].getposicion() << ")" << endl;
    }

    cout << "  titulares " << visita << ":" << endl;
    for (int i = 0; i < 11; i = i + 1) {
        cout << "    - " << oncevisita[i].getnombre();
        cout << " (" << oncevisita[i].getposicion() << ")" << endl;
    }
}

void Torneo::mostrartablagrupos() const {
    cout << "tabla fase de grupos" << endl;

    for (int g = 0; g < cantidadgrupos; g = g + 1) {
        int filas[4];

        for (int e = 0; e < 4; e = e + 1) {
            filas[e] = buscarfilatabla(grupos[g].getequipo(e));
        }

        bool completo = true;
        for (int e = 0; e < 4; e = e + 1) {
            if (filas[e] < 0) {
                completo = false;
            }
        }

        if (completo == false) {
            continue;
        }

        ordenarfilasgrupo(filas);

        cout << grupos[g].getnombre() << endl;
        for (int i = 0; i < 4; i = i + 1) {
            int f = filas[i];
            cout << "  " << (i + 1) << ". " << tabla[f].getnombre();
            cout << " | pts " << tabla[f].getpuntos();
            cout << " | pj " << tabla[f].getpartidos();
            cout << " | gf " << tabla[f].getgolesfavor();
            cout << " | gc " << tabla[f].getgolescontra();
            cout << " | dif " << tabla[f].getdiferencia() << endl;
        }
    }
}

// clasifica los 32 que pasan: 12 primeros + 12 segundos + 8 mejores terceros de los 12
void Torneo::clasificargrupos() {
    cantclasificados1 = 0;
    cantclasificados2 = 0;
    cantclasificados3 = 0;

    int filasterceros[12];
    int grupoterceros[12];
    int cantfilasterceros = 0;

    // saco primero y segundo de cada grupo, los terceros los guardo aparte pa ordenarlos
    for (int g = 0; g < cantidadgrupos; g = g + 1) {
        int filas[4];
        bool completo = true;

        for (int e = 0; e < 4; e = e + 1) {
            filas[e] = buscarfilatabla(grupos[g].getequipo(e));
            if (filas[e] < 0) {
                completo = false;
            }
        }

        if (completo == false) {
            continue;
        }

        ordenarfilasgrupo(filas);

        if (cantclasificados1 < 12) {
            clasificados1[cantclasificados1] = tabla[filas[0]].getnombre();
            cantclasificados1 = cantclasificados1 + 1;
        }

        if (cantclasificados2 < 12) {
            clasificados2[cantclasificados2] = tabla[filas[1]].getnombre();
            cantclasificados2 = cantclasificados2 + 1;
        }

        if (cantfilasterceros < 12) {
            filasterceros[cantfilasterceros] = filas[2];
            grupoterceros[cantfilasterceros] = g;
            cantfilasterceros = cantfilasterceros + 1;
        }
    }

    // comparo los 12 terceros entre si: los 8 mejores pasan, los otros 4 se quedan afuera
    for (int i = 0; i < cantfilasterceros; i = i + 1) {
        for (int j = i + 1; j < cantfilasterceros; j = j + 1) {
            int fi = filasterceros[i];
            int fj = filasterceros[j];
            bool intercambiar = false;

            if (tabla[fj].getpuntos() > tabla[fi].getpuntos()) {
                intercambiar = true;
            } else if (tabla[fj].getpuntos() == tabla[fi].getpuntos()) {
                if (tabla[fj].getdiferencia() > tabla[fi].getdiferencia()) {
                    intercambiar = true;
                } else if (tabla[fj].getdiferencia() == tabla[fi].getdiferencia()) {
                    if (tabla[fj].getgolesfavor() > tabla[fi].getgolesfavor()) {
                        intercambiar = true;
                    } else if (tabla[fj].getgolesfavor() == tabla[fi].getgolesfavor()) {
                        // si todo sigue igual, lo define un sorteo (como en el mundial real)
                        int sorteo = rand() % 2;
                        if (sorteo == 1) {
                            intercambiar = true;
                        }
                    }
                }
            }

            if (intercambiar) {
                int temporal = filasterceros[i];
                filasterceros[i] = filasterceros[j];
                filasterceros[j] = temporal;

                int tempg = grupoterceros[i];
                grupoterceros[i] = grupoterceros[j];
                grupoterceros[j] = tempg;
            }
        }
    }

    // solo pasan los 8 mejores terceros de los 12
    int limite = cantfilasterceros < 8 ? cantfilasterceros : 8;
    for (int i = 0; i < limite; i = i + 1) {
        clasificados3[i] = tabla[filasterceros[i]].getnombre();
        grupoindterceros[i] = grupoterceros[i];
    }
    cantclasificados3 = limite;
}

void Torneo::mostrarclasificados() const {
    cout << "clasificados fase de grupos" << endl;

    cout << "primeros de grupo (12):" << endl;
    for (int i = 0; i < cantclasificados1; i = i + 1) {
        cout << "  " << (i + 1) << ". " << clasificados1[i] << endl;
    }

    cout << "segundos de grupo (12):" << endl;
    for (int i = 0; i < cantclasificados2; i = i + 1) {
        cout << "  " << (i + 1) << ". " << clasificados2[i] << endl;
    }

    cout << "mejores terceros (8):" << endl;
    for (int i = 0; i < cantclasificados3; i = i + 1) {
        cout << "  " << (i + 1) << ". " << clasificados3[i] << endl;
    }
}

// arma los 16 cruces del bracket: primeros A-H vs 8 terceros, primeros I-L vs 4 peores segundos,
// segundos restantes entre si — ningun cruce puede tener dos equipos del mismo grupo
void Torneo::armardieciseisavos() {
    int total = cantclasificados1 + cantclasificados2 + cantclasificados3;
    // si no hay 32 exactos, mejor no seguir porq rompe la llave
    if (cantclasificados1 != 12 || cantclasificados2 != 12 || cantclasificados3 != 8 || total != 32) {
        cout << "armado dieciseisavos: clasificacion incompleta" << endl;
        return;
    }

    // los 4 peores segundos se cruzan con los primeros de los grupos I-L
    int peoressegundos[12];
    for (int i = 0; i < 12; i = i + 1) {
        peoressegundos[i] = i;
    }

    // ordeno de peor a mejor segundo
    for (int i = 0; i < 12; i = i + 1) {
        for (int j = i + 1; j < 12; j = j + 1) {
            int fi = buscarfilatabla(clasificados2[peoressegundos[i]]);
            int fj = buscarfilatabla(clasificados2[peoressegundos[j]]);

            bool intercambiar = false;
            if (fi >= 0 && fj >= 0) {
                if (tabla[fj].getpuntos() < tabla[fi].getpuntos()) {
                    intercambiar = true;
                } else if (tabla[fj].getpuntos() == tabla[fi].getpuntos()) {
                    if (tabla[fj].getdiferencia() < tabla[fi].getdiferencia()) {
                        intercambiar = true;
                    } else if (tabla[fj].getdiferencia() == tabla[fi].getdiferencia()) {
                        if (tabla[fj].getgolesfavor() < tabla[fi].getgolesfavor()) {
                            intercambiar = true;
                        } else if (tabla[fj].getgolesfavor() == tabla[fi].getgolesfavor()) {
                            if (tabla[fj].getnombre() < tabla[fi].getnombre()) {
                                intercambiar = true;
                            }
                        }
                    }
                }
            }

            if (intercambiar) {
                int t = peoressegundos[i];
                peoressegundos[i] = peoressegundos[j];
                peoressegundos[j] = t;
            }
        }
    }

    int terceros[8];
    int peores4[4];
    int usadossegundo[12];
    int usadostercero[8];

    for (int i = 0; i < 12; i = i + 1) {
        usadossegundo[i] = 0;
    }
    for (int i = 0; i < 8; i = i + 1) {
        terceros[i] = i;
        usadostercero[i] = 0;
    }
    for (int i = 0; i < 4; i = i + 1) {
        peores4[i] = peoressegundos[i];
        usadossegundo[peores4[i]] = 2; // 2 = reservado en bloque de peores segundos
    }

    // barajo para que los cruces no sean siempre los mismos
    for (int i = 7; i > 0; i = i - 1) {
        int j = rand() % (i + 1);
        int t = terceros[i];
        terceros[i] = terceros[j];
        terceros[j] = t;
    }
    for (int i = 3; i > 0; i = i - 1) {
        int j = rand() % (i + 1);
        int t = peores4[i];
        peores4[i] = peores4[j];
        peores4[j] = t;
    }

    string locales[16];
    string visitas[16];
    int gruposlocal[16];
    int gruposvisita[16];
    int partidosarmados = 0;

    for (int i = 0; i < 8; i = i + 1) {
        int grupohead = i;
        int elegido = -1;

        for (int t = 0; t < 8; t = t + 1) {
            int idtercero = terceros[t];
            if (usadostercero[idtercero] == 1) {
                continue;
            }
            if (grupoindterceros[idtercero] != grupohead) {
                elegido = idtercero;
                break;
            }
        }

        if (elegido < 0) {
            for (int t = 0; t < 8; t = t + 1) {
                int idtercero = terceros[t];
                if (usadostercero[idtercero] == 0) {
                    elegido = idtercero;
                    break;
                }
            }
        }

        locales[partidosarmados] = clasificados1[i];
        visitas[partidosarmados] = clasificados3[elegido];
        gruposlocal[partidosarmados] = grupohead;
        gruposvisita[partidosarmados] = grupoindterceros[elegido];
        usadostercero[elegido] = 1;
        partidosarmados = partidosarmados + 1;
    }

    for (int i = 8; i < 12; i = i + 1) {
        int grupohead = i;
        int elegido = -1;

        for (int s = 0; s < 4; s = s + 1) {
            int idseg = peores4[s];
            if (usadossegundo[idseg] == 1) {
                continue;
            }
            if (idseg != grupohead) {
                elegido = idseg;
                break;
            }
        }

        if (elegido < 0) {
            for (int s = 0; s < 4; s = s + 1) {
                int idseg = peores4[s];
                if (usadossegundo[idseg] != 1) {
                    elegido = idseg;
                    break;
                }
            }
        }

        locales[partidosarmados] = clasificados1[i];
        visitas[partidosarmados] = clasificados2[elegido];
        gruposlocal[partidosarmados] = grupohead;
        gruposvisita[partidosarmados] = elegido;
        usadossegundo[elegido] = 1; // ya se uso
        partidosarmados = partidosarmados + 1;
    }

    int segundosrestantes[8];
    int cantrestantes = 0;
    for (int i = 0; i < 12; i = i + 1) {
        if (usadossegundo[i] == 0) {
            segundosrestantes[cantrestantes] = i;
            cantrestantes = cantrestantes + 1;
        }
    }

    int usadorestante[8];
    for (int i = 0; i < 8; i = i + 1) {
        usadorestante[i] = 0;
    }

    for (int i = 0; i < cantrestantes; i = i + 1) {
        if (usadorestante[i] == 1) {
            continue;
        }

        int jpareja = -1;
        for (int j = i + 1; j < cantrestantes; j = j + 1) {
            if (usadorestante[j] == 1) {
                continue;
            }
            if (segundosrestantes[i] != segundosrestantes[j]) {
                jpareja = j;
                break;
            }
        }

        if (jpareja < 0) {
            for (int j = i + 1; j < cantrestantes; j = j + 1) {
                if (usadorestante[j] == 0) {
                    jpareja = j;
                    break;
                }
            }
        }

        if (jpareja >= 0) {
            locales[partidosarmados] = clasificados2[segundosrestantes[i]];
            visitas[partidosarmados] = clasificados2[segundosrestantes[jpareja]];
            gruposlocal[partidosarmados] = segundosrestantes[i];
            gruposvisita[partidosarmados] = segundosrestantes[jpareja];
            usadorestante[i] = 1;
            usadorestante[jpareja] = 1;
            partidosarmados = partidosarmados + 1;
        }
    }

    // ajuste final: si despues de todo algun partido cruzaria equipos del mismo grupo,
    // intento intercambiar visitantes con otro partido que no genere el mismo problema
    for (int i = 0; i < partidosarmados; i = i + 1) {
        if (gruposlocal[i] != gruposvisita[i]) {
            continue;
        }
        for (int j = i + 1; j < partidosarmados; j = j + 1) {
            if (gruposlocal[i] != gruposvisita[j] && gruposlocal[j] != gruposvisita[i]) {
                string tv = visitas[i];
                visitas[i] = visitas[j];
                visitas[j] = tv;
                int tg = gruposvisita[i];
                gruposvisita[i] = gruposvisita[j];
                gruposvisita[j] = tg;
                break;
            }
        }
    }

    // si despues de todos los intentos siguen quedando cruces del mismo grupo, aviso
    bool crucesvalidos = true;
    for (int i = 0; i < partidosarmados; i = i + 1) {
        if (gruposlocal[i] == gruposvisita[i]) {
            crucesvalidos = false;
            break;
        }
    }

    if (crucesvalidos == false) {
        cout << "armado dieciseisavos: no se pudo evitar cruces del mismo grupo" << endl;
        if (partidosdieciseisavos != 0) {
            delete[] partidosdieciseisavos;
            partidosdieciseisavos = 0;
        }
        cantdieciseisavos = 0;
        return;
    }

    if (partidosdieciseisavos != 0) {
        delete[] partidosdieciseisavos;
    }
    cantdieciseisavos = partidosarmados;
    partidosdieciseisavos = new partido[cantdieciseisavos];

    for (int i = 0; i < cantdieciseisavos; i = i + 1) {
        partidosdieciseisavos[i] = partido(locales[i], visitas[i]);
    }
}

void Torneo::mostrardieciseisavos() const {
    cout << "llave dieciseisavos de final" << endl;
    for (int i = 0; i < cantdieciseisavos; i = i + 1) {
        cout << "  partido " << (i + 1) << ": "
             << partidosdieciseisavos[i].getlocal()
             << " vs "
             << partidosdieciseisavos[i].getvisita() << endl;
    }
}

// si hay empate se va a tiempo extra: el mejor rankeado tiene hasta 35% mas de probabilidad
// retorna el ganador y ajusta los goles con los del tiempo extra
string Torneo::resolverganadoreliminacion(const Repositorio& repo, string local, string visita, int& goleslocal, int& golesvisita) const {
    if (goleslocal > golesvisita) {
        return local;  // gano el local, no hay mas que calcular
    }
    if (golesvisita > goleslocal) {
        return visita;  // gano el visitante
    }

    // hay empate: aplico desempate con sesgo por ranking
    int ilocal = buscarindiceequiporepo(repo, local);
    int ivisita = buscarindiceequiporepo(repo, visita);

    // arranco en 50/50, si hay datos de ranking ajusto la probabilidad
    double problocal = 0.5;

    if (ilocal >= 0 && ivisita >= 0) {
        int rankinglocal = repo.getranking(ilocal);
        int rankingvisita = repo.getranking(ivisita);
        // diferencia de ranking: si el rival esta mas abajo (numero mayor), el local tiene ventaja
        int diferencia = rankingvisita - rankinglocal;

        double sesgo = double(diferencia) / 220.0;  // normalizo entre -1 y 1
        // limito el sesgo a +/-35% para que ninguno sea favorito aplastante
        if (sesgo > 0.35) {
            sesgo = 0.35;
        }
        if (sesgo < -0.35) {
            sesgo = -0.35;
        }

        problocal = 0.5 + sesgo;
        if (problocal < 0.1) {
            problocal = 0.1;
        }
        if (problocal > 0.9) {
            problocal = 0.9;
        }
    }

    double r = double(rand() % 10000) / 10000.0;
    // la mayoria de veces el tiempo extra se define por 1 gol, a veces 2 o 3
    int golesdesempate = 1;
    int extra = rand() % 100;
    if (extra < 25) {
        golesdesempate = 2;  // 25% de chance de que se defina por 2 goles
    } else if (extra < 32) {
        golesdesempate = 3;  // 7% de chance de que se defina por 3 goles
    }

    if (r < problocal) {
        goleslocal = goleslocal + golesdesempate;
        return local;
    }

    golesvisita = golesvisita + golesdesempate;
    return visita;
}

bool Torneo::simularfasesfinales(const Repositorio& repo) {
    if (partidosdieciseisavos == 0 || cantdieciseisavos <= 0) {
        return false;
    }

    finalessimuladas = false;

    if (partidosoctavos != 0) {
        delete[] partidosoctavos;
        partidosoctavos = 0;
    }
    if (partidoscuartos != 0) {
        delete[] partidoscuartos;
        partidoscuartos = 0;
    }
    if (partidossemis != 0) {
        delete[] partidossemis;
        partidossemis = 0;
    }

    string* ganadores16 = new string[cantdieciseisavos];

    for (int i = 0; i < cantdieciseisavos; i = i + 1) {
        string local = partidosdieciseisavos[i].getlocal();
        string visita = partidosdieciseisavos[i].getvisita();

        partidosdieciseisavos[i].configurarcontexto("nombreSede", "codArbitro1", "codArbitro2", "codArbitro3", "00:00", "01/01/2026");
        partidosdieciseisavos[i].limpiargoleadores();

        int ilocal = buscarindiceequiporepo(repo, local);
        int ivisita = buscarindiceequiporepo(repo, visita);

        double gflocal = 1.35;
        double gclocal = 1.35;
        double gfvisita = 1.35;
        double gcvisita = 1.35;

        if (ilocal >= 0) {
            gflocal = repo.getgolesfavorhistorico(ilocal);
            gclocal = repo.getgolescontrahistorico(ilocal);
        }
        if (ivisita >= 0) {
            gfvisita = repo.getgolesfavorhistorico(ivisita);
            gcvisita = repo.getgolescontrahistorico(ivisita);
        }

        partidosdieciseisavos[i].setposesionlocal(calcularposesionlocal(repo.getranking(ilocal), repo.getranking(ivisita)));

        double lambdalocal = calcularlambdapartido(gflocal, gcvisita);
        double lambdavisita = calcularlambdapartido(gfvisita, gclocal);
        int goleslocal = redondeargolespartido(lambdalocal);
        int golesvisita = redondeargolespartido(lambdavisita);
        int minutospartido = 90;
        if (goleslocal == golesvisita) {
            minutospartido = 120; // en eliminacion se contempla tiempo extra
        }

        string ganador = resolverganadoreliminacion(repo, local, visita, goleslocal, golesvisita);

        int oncelocalidx[11];
        int oncevisitaidx[11];
        bool okoncelocal = elegironceindices(local, oncelocalidx);
        bool okoncevisita = elegironceindices(visita, oncevisitaidx);
        if (okoncelocal == false || okoncevisita == false) {
            delete[] ganadores16;
            return false;
        }

        actualizarestadisticasjugadorespartido(oncelocalidx, goleslocal, minutospartido, partidosdieciseisavos[i], true);
        actualizarestadisticasjugadorespartido(oncevisitaidx, golesvisita, minutospartido, partidosdieciseisavos[i], false);

        partidosdieciseisavos[i].setresultado(goleslocal, golesvisita);
        ganadores16[i] = ganador;
    }

    cantoctavos = cantdieciseisavos / 2;
    partidosoctavos = new partido[cantoctavos];

    for (int i = 0; i < cantoctavos; i = i + 1) {
        partidosoctavos[i] = partido(ganadores16[i * 2], ganadores16[i * 2 + 1]);
    }

    delete[] ganadores16;

    string* ganadores8 = new string[cantoctavos];

    for (int i = 0; i < cantoctavos; i = i + 1) {
        string local = partidosoctavos[i].getlocal();
        string visita = partidosoctavos[i].getvisita();

        partidosoctavos[i].configurarcontexto("nombreSede", "codArbitro1", "codArbitro2", "codArbitro3", "00:00", "01/01/2026");
        partidosoctavos[i].limpiargoleadores();

        int ilocal = buscarindiceequiporepo(repo, local);
        int ivisita = buscarindiceequiporepo(repo, visita);

        double gflocal = 1.35;
        double gclocal = 1.35;
        double gfvisita = 1.35;
        double gcvisita = 1.35;

        if (ilocal >= 0) {
            gflocal = repo.getgolesfavorhistorico(ilocal);
            gclocal = repo.getgolescontrahistorico(ilocal);
        }
        if (ivisita >= 0) {
            gfvisita = repo.getgolesfavorhistorico(ivisita);
            gcvisita = repo.getgolescontrahistorico(ivisita);
        }

        partidosoctavos[i].setposesionlocal(calcularposesionlocal(repo.getranking(ilocal), repo.getranking(ivisita)));

        double lambdalocal = calcularlambdapartido(gflocal, gcvisita);
        double lambdavisita = calcularlambdapartido(gfvisita, gclocal);
        int goleslocal = redondeargolespartido(lambdalocal);
        int golesvisita = redondeargolespartido(lambdavisita);
        int minutospartido = 90;
        if (goleslocal == golesvisita) {
            minutospartido = 120;
        }

        string ganador = resolverganadoreliminacion(repo, local, visita, goleslocal, golesvisita);

        int oncelocalidx[11];
        int oncevisitaidx[11];
        bool okoncelocal = elegironceindices(local, oncelocalidx);
        bool okoncevisita = elegironceindices(visita, oncevisitaidx);
        if (okoncelocal == false || okoncevisita == false) {
            delete[] ganadores8;
            return false;
        }

        actualizarestadisticasjugadorespartido(oncelocalidx, goleslocal, minutospartido, partidosoctavos[i], true);
        actualizarestadisticasjugadorespartido(oncevisitaidx, golesvisita, minutospartido, partidosoctavos[i], false);

        partidosoctavos[i].setresultado(goleslocal, golesvisita);
        ganadores8[i] = ganador;
    }

    cantcuartos = cantoctavos / 2;
    partidoscuartos = new partido[cantcuartos];

    for (int i = 0; i < cantcuartos; i = i + 1) {
        partidoscuartos[i] = partido(ganadores8[i * 2], ganadores8[i * 2 + 1]);
    }

    delete[] ganadores8;

    string* ganadores4 = new string[cantcuartos];

    for (int i = 0; i < cantcuartos; i = i + 1) {
        string local = partidoscuartos[i].getlocal();
        string visita = partidoscuartos[i].getvisita();

        partidoscuartos[i].configurarcontexto("nombreSede", "codArbitro1", "codArbitro2", "codArbitro3", "00:00", "01/01/2026");
        partidoscuartos[i].limpiargoleadores();

        int ilocal = buscarindiceequiporepo(repo, local);
        int ivisita = buscarindiceequiporepo(repo, visita);

        double gflocal = 1.35;
        double gclocal = 1.35;
        double gfvisita = 1.35;
        double gcvisita = 1.35;

        if (ilocal >= 0) {
            gflocal = repo.getgolesfavorhistorico(ilocal);
            gclocal = repo.getgolescontrahistorico(ilocal);
        }
        if (ivisita >= 0) {
            gfvisita = repo.getgolesfavorhistorico(ivisita);
            gcvisita = repo.getgolescontrahistorico(ivisita);
        }

        partidoscuartos[i].setposesionlocal(calcularposesionlocal(repo.getranking(ilocal), repo.getranking(ivisita)));

        double lambdalocal = calcularlambdapartido(gflocal, gcvisita);
        double lambdavisita = calcularlambdapartido(gfvisita, gclocal);
        int goleslocal = redondeargolespartido(lambdalocal);
        int golesvisita = redondeargolespartido(lambdavisita);
        int minutospartido = 90;
        if (goleslocal == golesvisita) {
            minutospartido = 120;
        }

        string ganador = resolverganadoreliminacion(repo, local, visita, goleslocal, golesvisita);

        int oncelocalidx[11];
        int oncevisitaidx[11];
        bool okoncelocal = elegironceindices(local, oncelocalidx);
        bool okoncevisita = elegironceindices(visita, oncevisitaidx);
        if (okoncelocal == false || okoncevisita == false) {
            delete[] ganadores4;
            return false;
        }

        actualizarestadisticasjugadorespartido(oncelocalidx, goleslocal, minutospartido, partidoscuartos[i], true);
        actualizarestadisticasjugadorespartido(oncevisitaidx, golesvisita, minutospartido, partidoscuartos[i], false);

        partidoscuartos[i].setresultado(goleslocal, golesvisita);
        ganadores4[i] = ganador;
    }

    cantsemis = cantcuartos / 2;
    partidossemis = new partido[cantsemis];

    for (int i = 0; i < cantsemis; i = i + 1) {
        partidossemis[i] = partido(ganadores4[i * 2], ganadores4[i * 2 + 1]);
    }

    delete[] ganadores4;

    string ganadores2[2];
    string perdedores2[2];

    for (int i = 0; i < cantsemis; i = i + 1) {
        string local = partidossemis[i].getlocal();
        string visita = partidossemis[i].getvisita();

        partidossemis[i].configurarcontexto("nombreSede", "codArbitro1", "codArbitro2", "codArbitro3", "00:00", "01/01/2026");
        partidossemis[i].limpiargoleadores();

        int ilocal = buscarindiceequiporepo(repo, local);
        int ivisita = buscarindiceequiporepo(repo, visita);

        double gflocal = 1.35;
        double gclocal = 1.35;
        double gfvisita = 1.35;
        double gcvisita = 1.35;

        if (ilocal >= 0) {
            gflocal = repo.getgolesfavorhistorico(ilocal);
            gclocal = repo.getgolescontrahistorico(ilocal);
        }
        if (ivisita >= 0) {
            gfvisita = repo.getgolesfavorhistorico(ivisita);
            gcvisita = repo.getgolescontrahistorico(ivisita);
        }

        partidossemis[i].setposesionlocal(calcularposesionlocal(repo.getranking(ilocal), repo.getranking(ivisita)));

        double lambdalocal = calcularlambdapartido(gflocal, gcvisita);
        double lambdavisita = calcularlambdapartido(gfvisita, gclocal);
        int goleslocal = redondeargolespartido(lambdalocal);
        int golesvisita = redondeargolespartido(lambdavisita);
        int minutospartido = 90;
        if (goleslocal == golesvisita) {
            minutospartido = 120;
        }

        string ganador = resolverganadoreliminacion(repo, local, visita, goleslocal, golesvisita);

        int oncelocalidx[11];
        int oncevisitaidx[11];
        bool okoncelocal = elegironceindices(local, oncelocalidx);
        bool okoncevisita = elegironceindices(visita, oncevisitaidx);
        if (okoncelocal == false || okoncevisita == false) {
            return false;
        }

        actualizarestadisticasjugadorespartido(oncelocalidx, goleslocal, minutospartido, partidossemis[i], true);
        actualizarestadisticasjugadorespartido(oncevisitaidx, golesvisita, minutospartido, partidossemis[i], false);

        partidossemis[i].setresultado(goleslocal, golesvisita);

        ganadores2[i] = ganador;
        if (ganador == local) {
            perdedores2[i] = visita;
        } else {
            perdedores2[i] = local;
        }
    }

    partidofinal = partido(ganadores2[0], ganadores2[1]);
    partidotercero = partido(perdedores2[0], perdedores2[1]);

    {
        string local = partidofinal.getlocal();
        string visita = partidofinal.getvisita();
        partidofinal.configurarcontexto("nombreSede", "codArbitro1", "codArbitro2", "codArbitro3", "00:00", "01/01/2026");
        partidofinal.limpiargoleadores();
        int ilocal = buscarindiceequiporepo(repo, local);
        int ivisita = buscarindiceequiporepo(repo, visita);

        double gflocal = 1.35;
        double gclocal = 1.35;
        double gfvisita = 1.35;
        double gcvisita = 1.35;

        if (ilocal >= 0) {
            gflocal = repo.getgolesfavorhistorico(ilocal);
            gclocal = repo.getgolescontrahistorico(ilocal);
        }
        if (ivisita >= 0) {
            gfvisita = repo.getgolesfavorhistorico(ivisita);
            gcvisita = repo.getgolescontrahistorico(ivisita);
        }

        partidofinal.setposesionlocal(calcularposesionlocal(repo.getranking(ilocal), repo.getranking(ivisita)));

        int goleslocal = redondeargolespartido(calcularlambdapartido(gflocal, gcvisita));
        int golesvisita = redondeargolespartido(calcularlambdapartido(gfvisita, gclocal));
        int minutospartido = 90;
        if (goleslocal == golesvisita) {
            minutospartido = 120;
        }
        string ganador = resolverganadoreliminacion(repo, local, visita, goleslocal, golesvisita);

        int oncelocalidx[11];
        int oncevisitaidx[11];
        bool okoncelocal = elegironceindices(local, oncelocalidx);
        bool okoncevisita = elegironceindices(visita, oncevisitaidx);
        if (okoncelocal == false || okoncevisita == false) {
            return false;
        }

        actualizarestadisticasjugadorespartido(oncelocalidx, goleslocal, minutospartido, partidofinal, true);
        actualizarestadisticasjugadorespartido(oncevisitaidx, golesvisita, minutospartido, partidofinal, false);

        partidofinal.setresultado(goleslocal, golesvisita);

        if (ganador == local) {
            equipocampeon = local;
            equiposubcampeon = visita;
        } else {
            equipocampeon = visita;
            equiposubcampeon = local;
        }
    }

    {
        string local = partidotercero.getlocal();
        string visita = partidotercero.getvisita();
        partidotercero.configurarcontexto("nombreSede", "codArbitro1", "codArbitro2", "codArbitro3", "00:00", "01/01/2026");
        partidotercero.limpiargoleadores();
        int ilocal = buscarindiceequiporepo(repo, local);
        int ivisita = buscarindiceequiporepo(repo, visita);

        double gflocal = 1.35;
        double gclocal = 1.35;
        double gfvisita = 1.35;
        double gcvisita = 1.35;

        if (ilocal >= 0) {
            gflocal = repo.getgolesfavorhistorico(ilocal);
            gclocal = repo.getgolescontrahistorico(ilocal);
        }
        if (ivisita >= 0) {
            gfvisita = repo.getgolesfavorhistorico(ivisita);
            gcvisita = repo.getgolescontrahistorico(ivisita);
        }

        partidotercero.setposesionlocal(calcularposesionlocal(repo.getranking(ilocal), repo.getranking(ivisita)));

        int goleslocal = redondeargolespartido(calcularlambdapartido(gflocal, gcvisita));
        int golesvisita = redondeargolespartido(calcularlambdapartido(gfvisita, gclocal));
        int minutospartido = 90;
        if (goleslocal == golesvisita) {
            minutospartido = 120;
        }
        string ganador = resolverganadoreliminacion(repo, local, visita, goleslocal, golesvisita);

        int oncelocalidx[11];
        int oncevisitaidx[11];
        bool okoncelocal = elegironceindices(local, oncelocalidx);
        bool okoncevisita = elegironceindices(visita, oncevisitaidx);
        if (okoncelocal == false || okoncevisita == false) {
            return false;
        }

        actualizarestadisticasjugadorespartido(oncelocalidx, goleslocal, minutospartido, partidotercero, true);
        actualizarestadisticasjugadorespartido(oncevisitaidx, golesvisita, minutospartido, partidotercero, false);

        partidotercero.setresultado(goleslocal, golesvisita);

        if (ganador == local) {
            equipotercero = local;
            equipocuarto = visita;
        } else {
            equipotercero = visita;
            equipocuarto = local;
        }
    }

    finalessimuladas = true;
    return true;
}

void Torneo::mostrarfasesfinales() const {
    if (finalessimuladas == false) {
        cout << "fases finales: no simuladas" << endl;
        return;
    }

    cout << "resultados dieciseisavos" << endl;
    for (int i = 0; i < cantdieciseisavos; i = i + 1) {
        cout << "  partido " << (i + 1) << endl;
        imprimirdatospartido(partidosdieciseisavos[i], true);
    }

    cout << "resultados octavos" << endl;
    for (int i = 0; i < cantoctavos; i = i + 1) {
        cout << "  partido " << (i + 1) << endl;
        imprimirdatospartido(partidosoctavos[i], true);
    }

    cout << "resultados cuartos" << endl;
    for (int i = 0; i < cantcuartos; i = i + 1) {
        cout << "  partido " << (i + 1) << endl;
        imprimirdatospartido(partidoscuartos[i], true);
    }

    cout << "resultados semifinales" << endl;
    for (int i = 0; i < cantsemis; i = i + 1) {
           cout << "  partido " << (i + 1) << endl;
           imprimirdatospartido(partidossemis[i], true);
    }

    cout << "tercer puesto" << endl;
        imprimirdatospartido(partidotercero, true);

    cout << "final" << endl;
        imprimirdatospartido(partidofinal, true);

    cout << "podio" << endl;
    cout << "  campeon: " << equipocampeon << endl;
    cout << "  subcampeon: " << equiposubcampeon << endl;
    cout << "  tercero: " << equipotercero << endl;
    cout << "  cuarto: " << equipocuarto << endl;
}

// suma los goles que metio el equipo en todos los partidos del torneo
int Torneo::contargolestorneoequipo(string nombreequipo) const {
    int total = 0;

    for (int i = 0; i < cantidadpartidosgrupos; i = i + 1) {
        if (partidosgrupos[i].getlocal() == nombreequipo) {
            total = total + partidosgrupos[i].getgoleslocal();
        }
        if (partidosgrupos[i].getvisita() == nombreequipo) {
            total = total + partidosgrupos[i].getgolesvisita();
        }
    }

    for (int i = 0; i < cantdieciseisavos; i = i + 1) {
        if (partidosdieciseisavos[i].getlocal() == nombreequipo) {
            total = total + partidosdieciseisavos[i].getgoleslocal();
        }
        if (partidosdieciseisavos[i].getvisita() == nombreequipo) {
            total = total + partidosdieciseisavos[i].getgolesvisita();
        }
    }

    for (int i = 0; i < cantoctavos; i = i + 1) {
        if (partidosoctavos[i].getlocal() == nombreequipo) {
            total = total + partidosoctavos[i].getgoleslocal();
        }
        if (partidosoctavos[i].getvisita() == nombreequipo) {
            total = total + partidosoctavos[i].getgolesvisita();
        }
    }

    for (int i = 0; i < cantcuartos; i = i + 1) {
        if (partidoscuartos[i].getlocal() == nombreequipo) {
            total = total + partidoscuartos[i].getgoleslocal();
        }
        if (partidoscuartos[i].getvisita() == nombreequipo) {
            total = total + partidoscuartos[i].getgolesvisita();
        }
    }

    for (int i = 0; i < cantsemis; i = i + 1) {
        if (partidossemis[i].getlocal() == nombreequipo) {
            total = total + partidossemis[i].getgoleslocal();
        }
        if (partidossemis[i].getvisita() == nombreequipo) {
            total = total + partidossemis[i].getgolesvisita();
        }
    }

    if (partidofinal.sejugo()) {
        if (partidofinal.getlocal() == nombreequipo) {
            total = total + partidofinal.getgoleslocal();
        }
        if (partidofinal.getvisita() == nombreequipo) {
            total = total + partidofinal.getgolesvisita();
        }
    }

    if (partidotercero.sejugo()) {
        if (partidotercero.getlocal() == nombreequipo) {
            total = total + partidotercero.getgoleslocal();
        }
        if (partidotercero.getvisita() == nombreequipo) {
            total = total + partidotercero.getgolesvisita();
        }
    }

    return total;
}

int Torneo::contargolesrecibidostorneoequipo(string nombreequipo) const {
    int total = 0;

    for (int i = 0; i < cantidadpartidosgrupos; i = i + 1) {
        if (partidosgrupos[i].getlocal() == nombreequipo) {
            total = total + partidosgrupos[i].getgolesvisita();
        }
        if (partidosgrupos[i].getvisita() == nombreequipo) {
            total = total + partidosgrupos[i].getgoleslocal();
        }
    }

    for (int i = 0; i < cantdieciseisavos; i = i + 1) {
        if (partidosdieciseisavos[i].getlocal() == nombreequipo) {
            total = total + partidosdieciseisavos[i].getgolesvisita();
        }
        if (partidosdieciseisavos[i].getvisita() == nombreequipo) {
            total = total + partidosdieciseisavos[i].getgoleslocal();
        }
    }

    for (int i = 0; i < cantoctavos; i = i + 1) {
        if (partidosoctavos[i].getlocal() == nombreequipo) {
            total = total + partidosoctavos[i].getgolesvisita();
        }
        if (partidosoctavos[i].getvisita() == nombreequipo) {
            total = total + partidosoctavos[i].getgoleslocal();
        }
    }

    for (int i = 0; i < cantcuartos; i = i + 1) {
        if (partidoscuartos[i].getlocal() == nombreequipo) {
            total = total + partidoscuartos[i].getgolesvisita();
        }
        if (partidoscuartos[i].getvisita() == nombreequipo) {
            total = total + partidoscuartos[i].getgoleslocal();
        }
    }

    for (int i = 0; i < cantsemis; i = i + 1) {
        if (partidossemis[i].getlocal() == nombreequipo) {
            total = total + partidossemis[i].getgolesvisita();
        }
        if (partidossemis[i].getvisita() == nombreequipo) {
            total = total + partidossemis[i].getgoleslocal();
        }
    }

    if (partidofinal.sejugo()) {
        if (partidofinal.getlocal() == nombreequipo) {
            total = total + partidofinal.getgolesvisita();
        }
        if (partidofinal.getvisita() == nombreequipo) {
            total = total + partidofinal.getgoleslocal();
        }
    }

    if (partidotercero.sejugo()) {
        if (partidotercero.getlocal() == nombreequipo) {
            total = total + partidotercero.getgolesvisita();
        }
        if (partidotercero.getvisita() == nombreequipo) {
            total = total + partidotercero.getgoleslocal();
        }
    }

    return total;
}

bool Torneo::guardarhistoricoactualizado(const Repositorio& repo) const {
    if (cantidadequiposbase <= 0 || cantidadjugadores <= 0 || jugadoresbase == 0) {
        return false;
    }

    int golesfavoractualizados[64];
    int golescontraactualizados[64];

    int limite = repo.getcantidadequipos();
    if (limite > 64) {
        limite = 64;
    }

    for (int i = 0; i < limite; i = i + 1) {
        string equipo = repo.getequipo(i);
        golesfavoractualizados[i] = repo.getgolesfavorhistoricototal(i) + contargolestorneoequipo(equipo);
        golescontraactualizados[i] = repo.getgolescontrahistoricototal(i) + contargolesrecibidostorneoequipo(equipo);
    }

    bool okequipos = repo.guardarequiposhistoricoactualizado(golesfavoractualizados,
                                                              golescontraactualizados,
                                                              limite,
                                                              "../../../equipos_historico_actualizado.csv");

    bool okjugadores = repo.guardarjugadoreshistoricoactualizado(jugadoresbase,
                                                                  cantidadjugadores,
                                                                  "../../../jugadores_historico_actualizado.csv");

    return okequipos && okjugadores;
}

// retorna la confederacion con mas equipos en una ronda, sin contar el mismo equipo dos veces
string Torneo::confederacionconmayorpresencia(const Repositorio& repo, const partido* partidos, int cantidad) const {
    if (partidos == 0 || cantidad <= 0) {
        return "sin datos";
    }

    string confs[8];
    int conteos[8];
    int usados = 0;
    string equiposvistos[64];
    int viste = 0;

    for (int i = 0; i < 8; i = i + 1) {
        confs[i] = "";
        conteos[i] = 0;
    }

    for (int i = 0; i < cantidad; i = i + 1) {
        string nombres[2];
        nombres[0] = partidos[i].getlocal();
        nombres[1] = partidos[i].getvisita();

        for (int k = 0; k < 2; k = k + 1) {
            string equipo = nombres[k];

            bool repetido = false;
            for (int v = 0; v < viste; v = v + 1) {
                if (equiposvistos[v] == equipo) {
                    repetido = true;
                    break;
                }
            }
            if (repetido) {
                continue;
            }

            if (viste < 64) {
                equiposvistos[viste] = equipo;
                viste = viste + 1;
            }

            int indice = buscarindiceequiporepo(repo, equipo);
            if (indice < 0) {
                continue;
            }

            string conf = repo.getconfederacion(indice);
            int pos = -1;

            for (int c = 0; c < usados; c = c + 1) {
                if (confs[c] == conf) {
                    pos = c;
                    break;
                }
            }

            if (pos < 0 && usados < 8) {
                pos = usados;
                confs[usados] = conf;
                conteos[usados] = 0;
                usados = usados + 1;
            }

            if (pos >= 0) {
                conteos[pos] = conteos[pos] + 1;
            }
        }
    }

    if (usados == 0) {
        return "sin datos";
    }

    int mejor = 0;
    for (int i = 1; i < usados; i = i + 1) {
        if (conteos[i] > conteos[mejor]) {
            mejor = i;
        } else if (conteos[i] == conteos[mejor]) {
                // si hay empate de confederaciones, lo decide sorteo
                int sorteo = rand() % 2;
            if (sorteo == 1) {
                mejor = i;
            }
        }
    }

    return confs[mejor];
}

// informe completo: top4, goleador del campeon, top3, equipo mas goleador e confederacion dominante
void Torneo::mostrarinformeestadisticas(const Repositorio& repo) const {
    cout << "informe final del torneo" << endl;

    cout << "top 4 del mundial" << endl;
    cout << "  1. " << equipocampeon << endl;
    cout << "  2. " << equiposubcampeon << endl;
    cout << "  3. " << equipotercero << endl;
    cout << "  4. " << equipocuarto << endl;

    // recorro los jugadores y busco el que mas metio del equipo campeon
    string goleadorcampeon = "sin datos";
    int golescampeon = -1;

    for (int i = 0; i < cantidadjugadores; i = i + 1) {
        if (jugadoresbase[i].getequipo() != equipocampeon) {
            continue;  // solo me interesan los del equipo campeon
        }

        if (jugadoresbase[i].getgoles() > golescampeon) {
            golescampeon = jugadoresbase[i].getgoles();
            goleadorcampeon = jugadoresbase[i].getnombre();
        }
    }

    cout << "maximo goleador del campeon" << endl;
    cout << "  " << goleadorcampeon << " (" << golescampeon << " goles)" << endl;

    // top 3 goleadores del torneo completo
    int top[3];
    for (int i = 0; i < 3; i = i + 1) {
        top[i] = -1;
    }

    for (int i = 0; i < cantidadjugadores; i = i + 1) {
        for (int p = 0; p < 3; p = p + 1) {
            if (top[p] < 0 || jugadoresbase[i].getgoles() > jugadoresbase[top[p]].getgoles()) {
                for (int mover = 2; mover > p; mover = mover - 1) {
                    top[mover] = top[mover - 1];
                }
                top[p] = i;
                break;
            }
        }
    }

    cout << "top 3 goleadores de la copa" << endl;
    for (int i = 0; i < 3; i = i + 1) {
        if (top[i] < 0) {
            continue;
        }

        cout << "  " << (i + 1) << ". " << jugadoresbase[top[i]] << endl;
    }

    // historial actualizado = goles historicos totales del csv + goles anotados en esta copa
    string mejorequipo = "sin datos";
    int mejorgoles = -1;

    for (int i = 0; i < repo.getcantidadequipos(); i = i + 1) {
        int basehistoricototal = repo.getgolesfavorhistoricototal(i);
        int totalactualizado = basehistoricototal + contargolestorneoequipo(repo.getequipo(i));

        if (totalactualizado > mejorgoles) {
            mejorgoles = totalactualizado;
            mejorequipo = repo.getequipo(i);
        }
    }

    cout << "equipo con mas goles historicos actualizados" << endl;
    cout << "  " << mejorequipo << " (" << mejorgoles << " goles)" << endl;

    cout << "confederacion con mayor presencia" << endl;
    cout << "  R16: " << confederacionconmayorpresencia(repo, partidosdieciseisavos, cantdieciseisavos) << endl;
    cout << "  R8: " << confederacionconmayorpresencia(repo, partidosoctavos, cantoctavos) << endl;
    cout << "  R4: " << confederacionconmayorpresencia(repo, partidossemis, cantsemis) << endl;
}

// iteraciones estimadas de la func II: grupos + simulacion + clasificacion + bracket R16
long long Torneo::estimariteracionesfuncionalidadII() const {
    long long total = 0;
    total = total + (long long)cantidadgrupos * 6;
    total = total + (long long)cantidadpartidosgrupos * 12;
    total = total + (long long)cantidadgrupos * 8;
    total = total + 16;
    return total;
}

// iteraciones estimadas de la func III: ~40 ops por cada partido de eliminatorias
long long Torneo::estimariteracionesfuncionalidadIII() const {
    long long total = 0;
    total = total + (long long)cantdieciseisavos * 40;
    total = total + (long long)cantoctavos * 40;
    total = total + (long long)cantcuartos * 40;
    total = total + (long long)cantsemis * 40;
    total = total + 80;
    return total;
}

// iteraciones estimadas de la func IV: recorre jugadores y equipos para el informe
long long Torneo::estimariteracionesfuncionalidadIV() const {
    long long total = 0;
    total = total + (long long)cantidadjugadores * 6;
    total = total + (long long)cantidadequiposbase * 3;
    return total;
}

// suma los sizeof de todas las estructuras dinamicas activas
// el medidor usa esto para reportar cuanta memoria aproximada usa cada etapa
size_t Torneo::estimarmemoriaactual() const {
    size_t total = sizeof(Torneo);

    total = total + sizeof(grupo) * size_t(cantidadgrupos);
    total = total + sizeof(tablaposiciones) * size_t(cantidadfilastabla);
    total = total + sizeof(jugador) * size_t(capacidadjugadores);
    total = total + sizeof(string) * size_t(cantidadfilastabla) * 2;
    total = total + sizeof(int) * size_t(cantidadfilastabla);
    total = total + sizeof(partido) * size_t(capacidadpartidosgrupos);
    total = total + sizeof(int) * size_t(capacidadpartidosgrupos);
    total = total + sizeof(partido) * size_t(cantdieciseisavos);
    total = total + sizeof(partido) * size_t(cantoctavos);
    total = total + sizeof(partido) * size_t(cantcuartos);
    total = total + sizeof(partido) * size_t(cantsemis);

    return total;
}
