#ifndef PARTIDO_H
#define PARTIDO_H

#include <string>

using namespace std;

class partido {
public:
    // partido con contexto completo y marcador
    partido();
    partido(string local, string visita);

    void configurarcontexto(string sedefija,
                            string arbitro1,
                            string arbitro2,
                            string arbitro3,
                            string horafija,
                            string fechafija);
    void setresultado(int goleslocal, int golesvisita);
    bool sejugo() const;
    void setposesionlocal(int porcentaje);
    int getposesionlocal() const;
    int getposesionvisita() const;
    void limpiargoleadores();
    void agregargoleadorlocal(int camiseta);
    void agregargoleadorvisita(int camiseta);
    int getcantgoleadoreslocal() const;
    int getcantgoleadoresvisita() const;
    int getgoleadorlocal(int pos) const;
    int getgoleadorvisita(int pos) const;

    string getlocal() const;
    string getvisita() const;
    string getsede() const;
    string getarbitro(int indice) const;
    string gethora() const;
    string getfecha() const;
    int getgoleslocal() const;
    int getgolesvisita() const;

private:
    string equipolocal;
    string equipovisita;
    string sede;
    string arbitros[3];
    string hora;
    string fecha;
    int goleslocal;
    int golesvisita;
    int posesionlocal;
    int goleadoreslocal[16];
    int goleadoresvisita[16];
    int cantgoleadoreslocal;
    int cantgoleadoresvisita;
    bool jugado;
};

#endif // PARTIDO_H
