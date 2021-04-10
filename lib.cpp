#include "lib.h"

#include "version.h"

int version()
{
#ifdef PROJECT_VERSION_PATCH
    return PROJECT_VERSION_PATCH;
#else
    return 1;
#endif
}
