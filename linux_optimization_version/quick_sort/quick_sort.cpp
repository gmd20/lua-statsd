// quick_sort.cpp : Defines the exported functions for the DLL application.
//

#include <algorithm>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <linux/types.h>

extern "C"  {
  void quick_sort(int * buf, int size)
  {
    std::sort(buf, buf + size);
  }

  double gettime()
  {
    /* 注意只有CLOCK_REALTIME返回的是从“00:00 hours, Jan 1, 1970 UTC” */
    /* 开始的秒数，才能用于那个graphite里面timestamp，其他的都是相对时间， */
    /* CLOCK_MONOTONIC_COARSE这个说事last tick时间，但粒度太粗了。 */
    /* 但我的ubuntu虚机上面 clock_gettime 比gettimeofday慢好多，可能是时钟源的问题。 */
    /* struct timespec tp; */
    /* clock_gettime(CLOCK_REALTIME, &tp); */
    /* clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp); */
    /* clock_gettime(CLOCK_MONOTONIC_COARSE, &tp); **/
    /* double now = tp.tv_sec + ((double)tp.tv_nsec ) /1.0e9; */
    /* return now; */

    struct timeval v;
    gettimeofday(&v, (struct timezone *) NULL);
    /* Unix Epoch time (time since January 1, 1970 (UTC)) */
    return v.tv_sec + v.tv_usec/1.0e6;
  }
}
