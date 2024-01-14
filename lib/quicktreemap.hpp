#pragma once

typedef unsigned char Byte;

template <typename Value>
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
        Node **childNodes = new Node *[16]
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
    int weight = 0;
};

template <typename Value>
QuickTreeMap<Value>::QuickTreeMap()
{

    headNode = new Node();
    headNode->key = Key();
    headNode->value = Value(0);
}

template <typename Value>
QuickTreeMap<Value>::~QuickTreeMap()
{
    delete headNode;
}

template <typename Value>
void QuickTreeMap<Value>::assign(Key key, Value value)
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

template <typename Value>
void QuickTreeMap<Value>::remove(Key key)
{
    Node *node;

    node = getNode(key);

    removeNode(node);
}

template <typename Value>
void QuickTreeMap<Value>::removeNode(Node *node)
{
    int maxHeight = -1;
    int maxHeightNode = -1;
    for (int i = 0; i < 16; i++)
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

        for (childNum = 0; childNum < 16; childNum++)
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
            for (int i = 0; i < 16; i++)
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

template <typename Value>
Value &QuickTreeMap<Value>::get(Key key)
{
    Node *node;

    node = getNode(key);

    return node->value;
}

template <typename Value>
typename QuickTreeMap<Value>::Node *QuickTreeMap<Value>::getNode(Key key)
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

template <typename Value>
QuickTreeMap<Value>::Key::Key(const Byte *content, Byte len)
{
    if (content == nullptr)
    {
        throw "Key Is Wrong";
    }

    this->content = (Byte *)content;
    this->len = len;
}

template <typename Value>
QuickTreeMap<Value>::Key::Key()
{
    this->content = nullptr;
    this->len = 0;
}

template <typename Value>
Byte QuickTreeMap<Value>::Key::getBits()
{
    int ret;

    if (count * 0.5 >= this->len)
    {
        ret = 0;
    }
    else
    {
        if (count % 2 == 0)
        {
            ret = this->content[count / 2] % 16;

            count++;
        }
        else
        {
            ret = this->content[count / 2] / 16;

            count++;
        }
    }

    return (ret);
}

template <typename Value>
bool QuickTreeMap<Value>::Key::operator==(Key key) const
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

template <typename Value>
QuickTreeMap<Value>::Node::~Node()
{
    delete[] childNodes;
}

template <typename Value>
int QuickTreeMap<Value>::size()
{
    return weight;
}

template <typename Value>
int QuickTreeMap<Value>::height()
{
    return headNode->height;
}

template <typename Value>
int QuickTreeMap<Value>::nodeHeight(Key key)
{
    return getNode(key)->height;
}
