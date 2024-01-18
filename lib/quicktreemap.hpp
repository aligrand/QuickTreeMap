#pragma once

typedef unsigned char Byte;

// bit = 1, 2, 4, 8
template <typename Value, Byte bit>
class QuickTreeMap
{
public:
    class Key
    {
    public:
        Key(const Byte *content, Byte len);

    private:
        Key();
        Byte getBits();
        bool operator==(Key key) const;

    private:
        Byte *content;
        Byte len;
        int count = 0;

        friend class QuickTreeMap;
    };

private:
    class Node
    {
    public:
        Key key;
        Value value;
        int height = 0;
        Node *parent = nullptr;
        Node **childNodes = new Node *[1 << bit]
        { nullptr };

        ~Node();
    };

public:
    QuickTreeMap();
    QuickTreeMap(const QuickTreeMap &other) = delete;
    QuickTreeMap &operator=(const QuickTreeMap &other) = delete;
    ~QuickTreeMap();
    void assign(Key key, Value value);
    void remove(Key key);
    Value &get(Key key);
    int size();
    int height();
    int nodeHeight(Key key);

private:
    Node *getNode(Key key);
    void removeNode(Node *node);

private:
    Node *headNode;
    int weight = 1;
};

template <typename Value, Byte bit>
QuickTreeMap<Value, bit>::QuickTreeMap()
{

    headNode = new Node();
    headNode->key = Key();
    headNode->value = Value(0);
}

template <typename Value, Byte bit>
QuickTreeMap<Value, bit>::~QuickTreeMap()
{
    delete headNode;
}

template <typename Value, Byte bit>
void QuickTreeMap<Value, bit>::assign(Key key, Value value)
{
    Node *itr = headNode;

    Byte child = key.getBits();

    while (itr->childNodes[child] != nullptr)
    {
        itr = itr->childNodes[child];

        if (itr->key == key)
        {
            itr->value = value;

            key.count = 0;

            return;
        }

        child = key.getBits();
    }

    key.count = 0;

    itr->childNodes[child] = new Node();
    itr->childNodes[child]->key = Key(key.content, key.len);
    itr->childNodes[child]->value = value;
    itr->childNodes[child]->parent = itr;

    itr = itr->childNodes[child];

    weight++;

    while ((itr->key).content != nullptr)
    {
        if (itr->parent->height <= itr->height)
        {
            itr->parent->height = itr->height + 1;
        }

        itr = itr->parent;
    }
}

template <typename Value, Byte bit>
void QuickTreeMap<Value, bit>::remove(Key key)
{
    Node *node;

    node = getNode(key);

    removeNode(node);
}

template <typename Value, Byte bit>
void QuickTreeMap<Value, bit>::removeNode(Node *node)
{
    int maxHeight = -1;
    int maxHeightNode = -1;
    for (int i = 0; i < (1 << bit); i++)
    {
        if (node->childNodes[i] != nullptr)
        {
            if (maxHeight < node->childNodes[i]->height)
            {
                maxHeight = node->childNodes[i]->height;
                maxHeightNode = i;
            }
        }
    }

    if (maxHeight == -1) // node in leaf
    {
        Node *leafNode = node;
        int childNum;

        for (childNum = 0; childNum < (1 << bit); childNum++)
        {
            if (node == node->parent->childNodes[childNum])
            {
                break;
            }
        }

        weight--;

        node = leafNode->parent;
        delete leafNode;

        node->childNodes[childNum] = nullptr;

        while (node != nullptr)
        {
            int h = -1;
            for (int i = 0; i < (1 << bit); i++)
            {
                if (node->childNodes[i] != nullptr)
                {
                    if (node->childNodes[i]->height > h)
                    {
                        h = node->childNodes[i]->height;
                    }
                }
            }

            if (node->height == h + 1)
            {
                break;
            }
            else
            {
                node->height = h + 1;

                node = node->parent;
            }
        }
    }
    else
    {
        node->key = node->childNodes[maxHeightNode]->key;
        node->value = node->childNodes[maxHeightNode]->value;

        removeNode(node->childNodes[maxHeightNode]);
    }
}

template <typename Value, Byte bit>
Value &QuickTreeMap<Value, bit>::get(Key key)
{
    Node *node;

    node = getNode(key);

    return node->value;
}

template <typename Value, Byte bit>
typename QuickTreeMap<Value, bit>::Node *QuickTreeMap<Value, bit>::getNode(Key key)
{
    Node *itr = headNode;

    Byte child = key.getBits();

    while (itr->childNodes[child] != nullptr)
    {
        itr = itr->childNodes[child];

        if (itr->key == key)
        {
            key.count = 0;

            return itr;
        }

        child = key.getBits();
    }

    key.count = 0;

    throw "Key Not Found";
}

template <typename Value, Byte bit>
QuickTreeMap<Value, bit>::Key::Key(const Byte *content, Byte len)
{
    if (content == nullptr)
    {
        throw "Key Is Wrong";
    }

    this->content = (Byte *)content;
    this->len = len;
}

template <typename Value, Byte bit>
QuickTreeMap<Value, bit>::Key::Key()
{
    this->content = nullptr;
    this->len = 0;
}

template <typename Value, Byte bit>
Byte QuickTreeMap<Value, bit>::Key::getBits()
{
    int ret;
    Byte key;

    if ((count / (8 / bit)) >= this->len)
    {
        ret = 0;
    }
    else
    {
        key = this->content[count / (8 / bit)];
        ret = (key >> ((count % (8 / bit)) * bit)) % (0b10 << (bit - 1));

        count++;
    }

    return (ret);
}

template <typename Value, Byte bit>
bool QuickTreeMap<Value, bit>::Key::operator==(Key key) const
{
    for (Byte i = 0; i < this->len; i++)
    {
        if (this->content[i] != key.content[i])
        {
            return false;
        }
    }

    return true;
}

template <typename Value, Byte bit>
QuickTreeMap<Value, bit>::Node::~Node()
{
    delete[] childNodes;
}

template <typename Value, Byte bit>
int QuickTreeMap<Value, bit>::size()
{
    return weight - 1;
}

template <typename Value, Byte bit>
int QuickTreeMap<Value, bit>::height()
{
    return headNode->height;
}

template <typename Value, Byte bit>
int QuickTreeMap<Value, bit>::nodeHeight(Key key)
{
    return getNode(key)->height;
}
