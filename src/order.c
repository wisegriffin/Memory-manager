#include "order.h"

int get_order(int n)
{
    int order = 0;

    if (n % 2 != 0) return -1;

    while (n != 1)
    {
        n /= 2;
        order++;
    }

    return order;
}

int order_to_number(int order)
{
    if (order == 0) return 1;

    int number = 2;
    for (; order > 1; order--)
    {
        number *= 2;
    }
    return number;
}