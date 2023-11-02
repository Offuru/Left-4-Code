#include "SinglePylon.h"

SinglePylon::SinglePylon(const Foundation& foundation, Color color):
Pylon(foundation,color){}

SinglePylon::SinglePylon(const SinglePylon& singlePylon):
Pylon(singlePylon){}


