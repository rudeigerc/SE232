#include <unordered_map>

class RNode
{
  public:
    RNode() {}
    RNode(int k, int v) : key(k), value(v) {}

    int key;
    int value;
    RNode *prev;
    RNode *next;
};

class LRUCache
{
  public:
    LRUCache(int cap) : capacity(cap)
    {
        head->next = tail;
        tail->prev = head;
    }

    int get(int key)
    {
        if (auto it = nodes.find(key); it != nodes.end())
        {
            RNode *node = nodes[key];
            node->prev->next = node->next;
            node->next->prev = node->prev;

            node->prev = head;
            node->next = head->next;
            node->prev->next = node;
            node->next->prev = node;

            return node->value;
        }
        return -1;
    }

    void put(int key, int value)
    {
        RNode *node;

        if (auto it = nodes.find(key); it != nodes.end())
        {
            node = nodes[key];
            node->value = value;
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
        else
        {
            if (nodes.size() == capacity)
            {
                node = tail->prev;
                nodes.erase(tail->prev->key);
                tail->prev = tail->prev->prev;
                tail->prev->next = tail;
                node->next = NULL;
                node->prev = NULL;
            }
            node = new RNode(key, value);
            nodes[key] = node;
        }

        node->prev = head;
        node->next = head->next;
        node->prev->next = node;
        node->next->prev = node;
    }

  private:
    int capacity;
    std::unordered_map<int, RNode *> nodes;
    RNode *head = new RNode();
    RNode *tail = new RNode();
};
