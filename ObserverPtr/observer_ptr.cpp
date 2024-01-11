#include "observer_ptr.h"
#include "Pylon.h"
#include "Bridge.h"


template class __declspec(dllexport) nonstd::observer_ptr<twixt::Pylon>;
template class __declspec(dllexport) nonstd::observer_ptr<twixt::Bridge>;