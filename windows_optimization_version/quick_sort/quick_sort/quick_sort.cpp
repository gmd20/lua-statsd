// quick_sort.cpp : Defines the exported functions for the DLL application.
//

#include <algorithm>

#include "windows.h"
#include "stdint.h"

extern "C"  {
  __declspec(dllexport) void quick_sort(int * buf, int size)
  {
    std::sort(buf, buf + size);
  }

  __declspec(dllexport) double gettime() {
	  //   uint64_t  intervals;
	  //   FILETIME  ft;

	  //   GetSystemTimeAsFileTime(&ft);

	  //   /*
	  //    * A file time is a 64-bit value that represents the number
	  //    * of 100-nanosecond intervals that have elapsed since
	  //    * January 1, 1601 12:00 A.M. UTC.
	  //    *
	  //    * Between January 1, 1970 (Epoch) and January 1, 1601 there were
	  //    * 134744 days,
	  //    * 11644473600 seconds or
	  //    * 11644473600,000,000,0 100-nanosecond intervals.
	  //    *
	  //    * See also MSKB Q167296.
	  //    */

	  //   intervals = ((uint64_t)ft.dwHighDateTime << 32) | ft.dwLowDateTime;
	  //   intervals -= 116444736000000000;
	  //	
	  //struct timeval tp;
	  //   tp.tv_sec = (long)(intervals / 10000000);
	  //   tp.tv_usec = (long)((intervals % 10000000) / 10);
	  //double now = tp.tv_sec + ((double)tp.tv_usec )/ 1000000;
	  //return now;


	  // 下面的代码来自最新的luasocket的，比上面的实现要快啊。
	  FILETIME ft;
	  double t;
	  GetSystemTimeAsFileTime(&ft);
	  /* Windows file time (time since January 1, 1601 (UTC)) */
	  t = ft.dwLowDateTime * (1 / 1.0e7) + ft.dwHighDateTime*(4294967296.0 / 1.0e7);
	  /* convert to Unix Epoch time (time since January 1, 1970 (UTC)) */
	  return (t - 11644473600.0);
  }
}
