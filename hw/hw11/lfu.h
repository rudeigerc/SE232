#include <unordered_map>

class FrequencyNode
{
  public:
    FrequencyNode() {}
    FrequencyNode(int freq) : frequency(freq) {}

    int frequency;
    FrequencyNode *prev;
    FrequencyNode *next;
};

class FNode
{
  public:
    FNode() {}
    FNode(int k, int v) : key(k), value(v) {}

    int key;
    int value;
    FNode *prev;
    FNode *next;
    FrequencyNode *parent;
};

class LFUCache
{
  public:
    LFUCache(int cap) : capacity(cap)
    {
        head->next = tail;
        tail->prev = head;
    }

    int get(int key)
    {
        return -1;
    }

    void put(int key, int value)
    {
    }

  private:
    int capacity;
    std::unordered_map<int, FNode *> nodes;
    FrequencyNode *head = new FrequencyNode();
    FrequencyNode *tail = new FrequencyNode();
};
