#ifndef Sum_CPP
#define Sum_CPP

double sum(double a, double b)
{
    return a + b;
}

double sum(double a, double b, double c)
{
    return sum(sum(a,b),c);
}

#endif