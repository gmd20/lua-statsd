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
    /* ע��ֻ��CLOCK_REALTIME���ص��Ǵӡ�00:00 hours, Jan 1, 1970 UTC�� */
    /* ��ʼ�����������������Ǹ�graphite����timestamp�������Ķ������ʱ�䣬 */
    /* CLOCK_MONOTONIC_COARSE���˵��last tickʱ�䣬������̫���ˡ� */
    /* ���ҵ�ubuntu������� clock_gettime ��gettimeofday���ö࣬������ʱ��Դ�����⡣ */
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
