#include <iostream>
#include <random>
#include <chrono>

#include "quicktreemap.hpp"

#define b 2
#define s 1000000 // must be more than 20

int main(int argc, char const *argv[])
{
    int *numKeys = new int[s];
    QuickTreeMap<int, b> map;

    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::minstd_rand0 generator(seed); 

    for (int i = 0; i < s; i++)
    {
        // numKeys[i] = new int(i);
        numKeys[i] = generator();

        // map.assign(QuickTreeMap<int, b>::Key((Byte *)numKeys[i], sizeof(int)), i);
        map.assign(QuickTreeMap<int, b>::Key((Byte *)&numKeys[i], sizeof(int)), i);

        // std::cout << i  << ' ' << *numKeys[i] << ' ' << map.height() << '\n'; // for speed-up comment this line

        // std::cout << 'a' << i << '\n'; // for speed-up comment this line
    }

    std::cout << map.size() << '\n';
    std::cout << map.height() << '\n';
    std::cout << map.nodeHeight(QuickTreeMap<int, b>::Key((Byte *)&numKeys[s / 2], sizeof(int))) << '\n';

    getchar();
    
    for (int i = 11; i < s - 1; i++)
    {
        map.remove(QuickTreeMap<int, b>::Key((Byte *)&numKeys[i], sizeof(int)));

        // std::cout << 'r' << i << '\n'; // for speed-up comment this line
    }

    std::cout << map.get(QuickTreeMap<int, b>::Key((Byte *)&numKeys[10], sizeof(int))) << '\n';

    try
    {
        std::cout << map.get(QuickTreeMap<int, b>::Key((Byte *)&numKeys[s - 2], sizeof(int))) << '\n';
    }
    catch(const char *exeption)
    {
        std::cerr << exeption << '\n';
    }
    
    std::cout << map.get(QuickTreeMap<int, b>::Key((Byte *)&numKeys[s - 1], sizeof(int))) << '\n';

    std::cout << map.size() << '\n';
    std::cout << map.height();

    return 0;
}