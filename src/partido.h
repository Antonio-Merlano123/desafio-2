#ifndef PARTIDO_H
#define PARTIDO_H

#include <string>

using namespace std;

class partido {
public:
    // par de equipos + marcador final
    partido();
    partido(string local, string visita);

    void setresultado(int goleslocal, int golesvisita);
    bool sejugo() const;

    string getlocal() const;
    string getvisita() const;
    int getgoleslocal() const;
    int getgolesvisita() const;

private:
    string equipolocal;
    string equipovisita;
    int goleslocal;
    int golesvisita;
    bool jugado;
};

#endif // PARTIDO_H
