#include <iostream>

using namespace std;

typedef int T;

bool compare(T a, T b)
{
    return a == b;
}

struct Node
{
    T data;
    Node* next;

    Node(T data)
    {
        this->data = data;
        this->next = nullptr;
    }
};

struct HashTable
{
private:
    Node** hash_table;
    int hash_table_size;
    int hash_table_mul;

    int hash(T data)
    {
        return data % this->hash_table_size;
    }

    int hashString(char* str)
    {
        int h = 0;

        for (char* p = str; *p != '\0'; p++)
        {
            h = h * this->hash_table_mul + (int)*p;
        }

        return h % this->hash_table_size;
    }

public:
    HashTable(int size)
    {
        this->hash_table = new Node * [size];
        this->hash_table_size = size;
        this->hash_table_mul = 31;

        for (int i = 0; i < size; i++)
        {
            this->hash_table[i] = nullptr;
        }
    }

    void insert(T data)
    {
        int hashcode = this->hash(data);

        Node* newHead = new Node(data);
        Node* prevHead = this->hash_table[hashcode];

        this->hash_table[hashcode] = newHead;
        newHead->next = prevHead;
    }

    bool remove(T data)
    {
        int hashcode = this->hash(data);
        Node* current = this->hash_table[hashcode];
        Node* previous;

        bool removed = false;

        while (current)
        {
            if (compare(current->data, data))
            {
                if (previous)
                    previous->next = current->next;
                else
                    this->hash_table[hashcode] = current->next;

                delete current;
                removed = true;
            }

            previous = current;
            current = current->next;

            return removed;
        }
    }

    Node* find(T data)
    {
        int hashcode = this->hash(data);
        Node* current = this->hash_table[hashcode];

        while (current)
        {
            if (compare(current->data, data))
                return current;

            current = current->next;
        }
    }
};

int main()
{
    cout << "Hello, world!" << endl;
    return 0;
}
