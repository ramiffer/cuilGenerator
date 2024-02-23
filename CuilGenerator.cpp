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

    //Aseguramos que el DNI tiene 8 numeros.
    DNI = new char[8];
    char* pDni = DNI;

    int i = 0;

    //Rellenamos con 0
    for(; i < 8; ++i) *pDni++ = '0';

    //Si i >= 0 && dni > 0 asignamos i del array DNI
    //el valor del ultimo digito de dni, y despues
    //reducimos dividiendo por 10 para pasar al siguiente.
    for(i = 7; i >= 0 && dni >0; --i) {
        DNI[i] = dni % 10 + '0';
        dni /= 10;
    }

}

char* CuilGenerator::obtenerXY() {

    char* pXY = new char[3];

    switch(this->XY) {
    case 'M': //MASCULINO
        strcpy(pXY, "23");
        break;
    case 'F': //FEMENINO
        strcpy(pXY, "27");
        break;
    case 'E': //EMPRESA
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
    //Pesos del algoritmo modulo 11 para calcular el CUIL
    int W[] = {5,4,3,2,7,6,5,4,3,2};

    char* pXY = new char[3];

    int Wsum = 0;

    int i = 0;
    //Valor ponderado sumando los productos de cada digito por su peso
    for(; i < 8; ++i) Wsum += (dni[i] - '0') * W[i];

    //Agregamos XY al resultado ponderado
    Wsum += (XY - '0');

    //Calculamos el modulo 11 del resultado ponderado
    int r = Wsum % 11;

    //Calculamos el digito verificador segun las reglas del modulo 11
    int V = (11 - r) % 11;

    //Reglas adicionales para el caso de resto == 1
    if(r == 1) {
        if(XY == 'M') {
            V = 9;
            strcpy(pXY, "23");
        } else if (XY == 'F') {
            V = 4;
            strcpy(pXY, "23");
    }
}
    pXY[2] = '\0';

    std::pair<char*, char> res = std::make_pair(pXY, static_cast<char>(V + '0'));

    delete[] pXY;

    return res;
}

std::string CuilGenerator::generarCuil() {
    std::string cuil = "";

    std::pair<char*, char> res = calcularDigitoVerificador(getDNI(), getXY());

    //Lo que pasa aca es sencillo, si se modifica el valor del prefijo debido a que el resto fue 1
    //al cuil vamos a sumarle el res.first, sino simplemente sumamos el que nos devuelve obtenerXY;
    if(strcmp(res.first, obtenerXY()) != 0) cuil += res.first;
    else cuil += obtenerXY();

    int i = 0;
    for(; i < 8; ++i) cuil+= getDNI()[i];

    cuil+= res.second;

    return cuil;
}
