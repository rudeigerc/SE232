#include "lru.h"
#include "lfu.h"
#include <iostream>

enum Type
{
    LRU,
    LFU
};

Type parseType(std::string str)
{
    if (str == "LRU")
        return LRU;
    if (str == "LFU")
        return LFU;
    return Type();
}

enum Operation
{
    PUT,
    GET
};

Operation parseOperation(std::string str)
{
    if (str == "PUT")
        return PUT;
    if (str == "GET")
        return GET;
    return Operation();
}

int main()
{
    std::string type;
    int capacity;

    LRUCache *lru_cache;
    LFUCache *lfu_cache;

    std::cin >> type >> capacity;

    switch (parseType(type))
    {
    case LRU:
        lru_cache = new LRUCache(capacity);
        break;
    case LFU:
        lfu_cache = new LFUCache(capacity);
        break;
    }

    while (std::cin)
    {
        std::string operation;
        int key;
        int value;

        std::cin >> operation;
        switch (parseOperation(operation))
        {
        case PUT:
            std::cin >> key >> value;
            switch (parseType(type))
            {
            case LRU:
                lru_cache->put(key, value);
                break;
            case LFU:
                lfu_cache->put(key, value);
                break;
            }
            break;
        case GET:
            std::cin >> key;
            switch (parseType(type))
            {
            case LRU:
                std::cout << lru_cache->get(key) << std::endl;
                break;
            case LFU:
                std::cout << lfu_cache->get(key) << std::endl;
                break;
            }
            break;
        }
    }
    return 0;
}
