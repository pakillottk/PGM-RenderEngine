#pragma once

#define LOOP1(a) a
#define LOOP2(a) a LOOP1(a)
#define LOOP3(a) a LOOP2(a)

#define LOOPN(n,a) LOOP##n(a)

#define LOOP_COUNT1(i,a) a (i+1);
#define LOOP_COUNT2(i,a) a (i+1); LOOP1(a)
#define LOOP_COUNT3(i,a) a (i+1); LOOP2(a)

#define LOOP_COUNTN(n,i,a) LOOP_COUNT##n(i,a)
