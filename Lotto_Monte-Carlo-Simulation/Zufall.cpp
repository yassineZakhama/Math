#include "Zufall.h"
#include <map>
int CZufall::wert(int a, int b)
{
    return a + rand() % (b - a + 1); // random number between a and b
}                          

void CZufall::initialisiere(int s)
{
    srand(s);
}

std::map<int, int> CZufall::test(int a, int b, int N)
{   
    // first ist die erzeugte nummer, second ist hauefigkeit
    std::map<int, int> h; 

    for (int i = 0; i < N; i++)
    {
        int random_number = wert(a, b);
        h[random_number] += 1;
    }
    return h;
    /*
    for (int i = 0; i < N; i++)
    {
        int random_number = wert(a, b);

        if (h.find(random_number) != h.end())
            h[random_number] += 1;
        else
            h.insert(std::make_pair(random_number,0));
    }   
    */
    
}

std::map<int, int> CZufall::test_falsch(int a, int b, int N)
{
    // first ist die erzeugte nummer, second ist hauefigkeit
    std::map<int, int> h;

    for (int i = 0; i < N; i++)
    {
        initialisiere(time(NULL));

        int random_number = wert(a, b);
        h[random_number] += 1;
    }
    return h;
}
