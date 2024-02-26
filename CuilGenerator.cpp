#include "CuilGenerator.h"
#include <iostream>
#include <string.h>
#include <utility>
#include <string>

CuilGenerator::CuilGenerator(char prefix, int document) {
     setXY(prefix);
     fillDNI(document);
}

CuilGenerator::~CuilGenerator(){ delete[] DNI; }


void CuilGenerator::fillDNI(int dni) {

    DNI = new char[8];
    char* pDni = DNI;

    int i = 0;

    for(; i < 8; ++i) *pDni++ = '0';

    for(i = 7; i >= 0 && dni >0; --i) {
        DNI[i] = dni % 10 + '0';
        dni /= 10;
    }

}

char* CuilGenerator::obtenerXY() {

    char* pXY = new char[3];

    switch(this->XY) {
    case 'M':
        strcpy(pXY, "20");
        break;
    case 'F':
        strcpy(pXY, "27");
        break;
    case 'E':
        strcpy(pXY, "30");
        break;
    default:
        std::cerr << "== ERROR: El valor del prefijo no es valido ==" <<std::endl;
        break;
    }
    pXY[2] = '\0';


    return pXY;
}

std::pair<char*, char> CuilGenerator::calcularDigitoVerificador(const char* dni, char XY) {
    int W[] = {5,4,3,2,7,6,5,4,3,2};

    char* pXY = new char[3];

    pXY = obtenerXY();

    int Wsum = 0;

    Wsum += (pXY[0] - '0') * W[0];
    Wsum += (pXY[1] - '0') * W[1];

    for(int i = 2; i < 10; ++i) Wsum += (dni[i - 2] - '0') * W[i];

    int r = Wsum % 11;
    if(r == 0) V = 0;
    else if(r == 1) {
        if (pXY[0] == '2' && pXY[1] == '0') {
            V = 9;
            pXY[1] = '3';

        } else if (pXY[0] == '2' && pXY[1] == '7') {
            V = 4;
            pXY[1] = '3';
        }

    } else V = (11 - r);

    std::pair<char*, char> res = std::make_pair(pXY, static_cast<char>(V + '0'));

    return res;
}

std::string CuilGenerator::generarCuil() {
    std::string cuil = "";

    std::pair<char*, char> res = calcularDigitoVerificador(getDNI(), getXY());

    cuil+= res.first;

    int i = 0;
    for(; i < 8; ++i) cuil+= getDNI()[i];

    cuil+= res.second;

    return cuil;
}
