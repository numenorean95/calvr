#ifndef TIME_OF_DAY_H
#define TIME_OF_DAY_H

#ifdef WIN32
#include <util/Export.h>

#include <time.h>
#include <windows.h>

CVRUTIL_EXPORT int gettimeofday(struct timeval *tv, void *tz);
#endif
#endif