#include "ACTUATOR.h"

void Turn_ON()
{
    LATD5 = 1;
}
void Turn_OFF()
{
    LATD5 = 0;
}
