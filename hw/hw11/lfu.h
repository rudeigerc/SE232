#include <unordered_map>

class FrequencyNode;
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

class FrequencyNode
{
  public:
    FrequencyNode() {}
    FrequencyNode(int freq) : frequency(freq) {}

    int frequency;
    FrequencyNode *prev;
    FrequencyNode *next;
    FNode *head;
    FNode *tail;
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
        if (auto it = nodes.find(key); it != nodes.end())
        {
            FNode *node = nodes[key];
            node->prev->next = node->next;
            node->next->prev = node->prev;

            // node->prev = head;
            // node->next = head->next;
            // head->next = node;
            node->next->prev = node;

            return node->value;
        }
        return -1;
    }

    void put(int key, int value)
    {
        FNode *node;

        if (auto it = nodes.find(key); it != nodes.end())
        {
            node = nodes[key];
            node->value = value;
            node->prev->next = node->next;
            node->next->prev = node->prev;

            FrequencyNode *f_node;
            if (int freq = node->parent->frequency + 1; node->parent->next->frequency != freq)
            {
                f_node = new FrequencyNode(freq);
                f_node->prev = node->parent;
                f_node->next = node->parent->next;
                f_node->prev->next = f_node;
                f_node->next->prev = f_node;

                f_node->head->next = node;
                f_node->tail->prev = node;
                node->prev = f_node->head;
                node->next = f_node->tail;
            }
            else
            {
                f_node = node->parent->next;
                node->prev = f_node->head;
                node->next = f_node->head->next;
                f_node->head->next = node;
                f_node->head->next->prev = node;
            }
        }
        else
        {
            if (nodes.size() == capacity)
            {
                node = head->next->head->next;
                nodes.erase(node->key);
                head->next->head->next = node->next;
                node->next->prev = head->next->head->next;
                node->prev = NULL;
                node->next = NULL;
            }
            node = new FNode(key, value);
            nodes[key] = node;
            if (head->next->frequency != 1)
            {
                FrequencyNode *f_node = new FrequencyNode(1);
                f_node->prev = head;
                f_node->next = head->next;
                f_node->prev->next = f_node;
                f_node->next->prev = f_node;
            }
            node = new FNode(key, value);
            node->parent = head->next;
        }
    }

  private:
    int capacity;
    std::unordered_map<int, FNode *> nodes;
    FrequencyNode *head = new FrequencyNode();
    FrequencyNode *tail = new FrequencyNode();
};
