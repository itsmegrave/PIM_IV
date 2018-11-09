//
// Created by Grave on 09/11/18.
//

#include "pausecmd.h"
#include <stdlib.h>

void pausecmd(){
#ifdef _WIN32
    system("pause");
#elif defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
    system("read -p '\t\tPressione ENTER para continuar...' var");
#endif
}
