#ifndef __APPCONFIG_LOAD_H_
#define __APPCONFIG_LOAD_H_


#define AppTypeLib ((AppType>>8))


#if (AppTypeLib==AppTypeLib_TeaBar)

#include "teabar\teabar_app.h"

#elif (AppTypeLib==AppTypeLib_WaterHeater)

#include "waterheater\waterheater_app.h"


#endif






#endif