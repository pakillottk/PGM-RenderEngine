#pragma once

#define LOOP1(a) a
#define LOOP2(a) a LOOP1(a)
#define LOOP3(a) a LOOP2(a)

#define LOOPN(n,a) LOOP##n(a)