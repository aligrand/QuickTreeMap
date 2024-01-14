#include <iostream>

#include "quicktreemap.hpp"

int main(int argc, char const *argv[])
{
    int **numKeys = new int*[10000000];
    QuickTreeMap<int> map;

    for (int i = 0; i < 10000000; i++)
    {
        numKeys[i] = new int(i);

        map.assign(QuickTreeMap<int>::Key((Byte *)numKeys[i], sizeof(int)), i);
    }

    std::cout << map.height() << '\n';
    std::cout << map.nodeHeight(QuickTreeMap<int>::Key((Byte *)numKeys[5000], sizeof(int))) << '\n';
    
    for (int i = 11; i < 9999999; i++)
    {
        map.remove(QuickTreeMap<int>::Key((Byte *)numKeys[i], sizeof(int)));
    }

    std::cout << map.get(QuickTreeMap<int>::Key((Byte *)numKeys[10], sizeof(int))) << '\n';

    try
    {
        std::cout << map.get(QuickTreeMap<int>::Key((Byte *)numKeys[200], sizeof(int))) << '\n';
    }
    catch(const char *exeption)
    {
        std::cerr << exeption << '\n';
    }
    
    std::cout << map.get(QuickTreeMap<int>::Key((Byte *)numKeys[9999999], sizeof(int))) << '\n';

    std::cout << map.size() << '\n';
    std::cout << map.height();

    return 0;
}

/**
 * TODO:
 * 1: getNode has bug
 * */