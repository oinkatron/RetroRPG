#ifndef BASIC_FUNC_H
#define BASIC_FUNC_H

#include <cstdlib>
#include <SDL/SDL.h>

template <class S>
inline void swap(S *f, S*s)
{
    S tmp;
    tmp = *s;
    *s = *f;
    *f = tmp;

    return;
}

inline int randomInt(int min, int max)
{
    if (min == max)
        return min;
    else if (min > max)
        swap(&min, &max);

    int range = max-min;
    return (rand()%range)+min;
}

inline float randomFloat(float min, float max)
{
    if (min == max)
        return min;
    else if (min > max)
        swap(&min, &max);

    float num = ((float)rand())/(float)RAND_MAX;
    return (num*(max-min))+min;
}

inline double randomDouble(double min, double max)
{
    if (min == max)
        return min;
    else if (min > max)
        swap(&min, &max);

    double num = ((double)rand())/(double)RAND_MAX;
    return (num*(max-min))+min;
}


#endif
