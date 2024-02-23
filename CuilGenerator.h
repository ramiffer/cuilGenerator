#ifndef CUILGENERATOR_H_INCLUDED
#define CUILGENERATOR_H_INCLUDED

#include <utility>
#include <string>

class CuilGenerator {

public:
    CuilGenerator(char XY, int DNI);
    ~CuilGenerator();

    char getXY() const { return XY; }
    const char* getDNI() const { return DNI; }
    int getVerifier() const { return V; }


    void setDNI(int dni) { fillDNI(dni); }
    void setXY(char xy) { XY = xy; }
    void setVerifier(int verifier) { V = verifier; }


    char* obtenerXY();
    std::pair<char*, char> calcularDigitoVerificador(const char* dni, char xy);
    std::string generarCuil();

private:
    char XY; //PREFIX
    char* DNI; //DNI TIENE QUE CONTENER 8 NUMEROS, SI ES MENOR AGREGAEMOS 0 ADELANTE HASTA QUE SEAN 8
    int V; //VERIFICADOR

    void fillDNI(int DNI);
};


#endif // CUILGENERATOR_H_INCLUDED
