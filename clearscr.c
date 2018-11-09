//
// Created by Grave on 08/11/18.
//

#include "clearscr.h"
#include <stdlib.h>

void clearscr(){
#ifdef _WIN32
    system("cls");
#elif defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
    system("clear");
#endif
}
