#include <iostream>
#include "CuilGenerator.h"

int main() {

    //AGREGAR EL 'XY' Y DESPUES EL DNI Y A DISFRUTAR LA MAGIA :)
    CuilGenerator cuilGenerator('M', 1233123);

    std::cout << cuilGenerator.generarCuil() << std::endl;



return 0;
}
