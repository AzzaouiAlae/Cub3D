#ifndef CUB3D_H
#define CUB3D_H

#include "ft_func/ft_func.h"
#include "garbage_collector/garbage_collector.h"
#include "list/list.h"
#include "map/map.h"
#include "string/string.h"

typedef struct s_point
{
    float x;
    float y;
} t_point;

typedef struct s_line
{
    t_point start;
    t_point end;
} t_line;

typedef struct s_end_point
{
    t_point point;
    float distance;
} s_end_point;

#endif