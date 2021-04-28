#include <iostream>

class Node
{
public:
    int value;
    Node *next;

    Node(int value, Node *next)
        : value(value), next(next)
    {
    }
};

class LinkedList
{
private:
    Node *first = nullptr;
    Node *last = nullptr;

public:
    LinkedList()
    {
    }

    void addFirst(int item)
    {
        this->first = new Node(item, this->first);

        if (this->last == nullptr)
            this->last = this->first;
    }

    void addLast(int item)
    {
        if (this->last != nullptr)
        {
            this->last->next = new Node(item, nullptr);
            this->last = this->last->next;
        }
        else
        {
            this->last = new Node(item, nullptr);
        }

        if (this->first == nullptr)
        {
            this->first = this->last;
        }
    }

    void insert(int index, int item)
    {
        Node *node = this->first;

        if (index < 0)
        {
            return;
        }

        if (index == 0)
        {
            this->addFirst(item);
            return;
        }

        for (int i = 0; i < index - 1; i++)
        {
            if (node == nullptr)
            {
                return;
            }

            node = node->next;
        }

        if (node == nullptr)
        {
            return;
        }

        if (node->next == nullptr)
        {
            this->addLast(item);
            return;
        }

        node->next = new Node(item, node->next);
    }

    void deleteAt(int index)
    {
        Node *node = first;

        if (index < 0)
        {
            return;
        }

        if (index == 0)
        {
            this->deleteFirst();
            return;
        }

        for (int i = 0; i < index - 1; i++)
        {
            if (node == nullptr)
            {
                return;
            }

            node = node->next;
        }

        if (node == nullptr)
        {
            return;
        }

        if (node->next == nullptr)
        {
            return;
        }

        if (node->next->next == nullptr)
        {
            this->deleteLast();
            return;
        }

        Node *new_referenced = node->next->next;
        delete node->next;
        node->next = new_referenced;
    }

    void deleteFirst()
    {
        if (this->first == nullptr)
        {
            return;
        }

        Node *new_first = this->first->next;

        delete this->first;
        this->first = new_first;

        if (this->first == nullptr)
        {
            this->last == nullptr;
        }
    }

    void deleteLast()
    {
        if (first == nullptr)
        {
            return;
        }

        Node *node = first;
        if (node == this->last)
        {
            delete this->last;
            this->last = nullptr;
            this->first = nullptr;

            return;
        }

        while (node->next != this->last)
        {
            node = node->next;
        }

        delete this->last;

        this->last = node;
        this->last->next = nullptr;
    }

    bool contains(int item)
    {
        if (this->first == nullptr)
        {
            return false;
        }

        Node *node = this->first;
        while (node != this->last)
        {
            if (node->value == item)
                return true;

            node = node->next;
        }

        if (node->value == item)
            return true;

        return false;
    }

    int indexOf(int item)
    {
        if (this->first == nullptr)
        {
            return -1;
        }

        Node *node = this->first;

        int i = 0;
        while (node != this->last)
        {
            if (node->value == item)
                return i;

            node = node->next;

            i++;
        }

        if (node->value == item)
            return i;

        return -1;
    }

    void consolePrintList()
    {
        if (this->first == nullptr)
        {
            std::cout << "[]";
            return;
        }

        std::cout << "[";

        Node *node = this->first;
        while (node != this->last)
        {
            std::cout << node->value;
            std::cout << ", ";

            node = node->next;
        }

        std::cout << node->value;
        std::cout << "]" << std::endl;
    }

    void reverse()
    {
        Node *head = first;

        this->last = head;

        Node *node = head;
        Node *cache = nullptr;
        Node *next_node;

        while (true)
        {
            next_node = node->next;

            node->next = cache;
            cache = node;

            if (next_node == nullptr)
            {
                break;
            }

            node = next_node;
        }

        this->first = node;
    }
};

main()
{
    LinkedList ll = LinkedList();
    ll.addFirst(1);
    ll.addLast(2);
    ll.addLast(3);
    ll.reverse();
    ll.consolePrintList();
}