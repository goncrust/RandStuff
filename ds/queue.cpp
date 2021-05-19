#include <iostream>

// enqueue
// showfront
// dequeue
// isempty
// size

class Node
{
public:
    int data;
    Node *next;
};

class Queue
{
private:
    Node *front;
    Node *rear;

    int size = 0;

public:
    Queue() {}

    void enqueue(int value)
    {
        if (this->size == 0)
        {
            this->front = new Node();
            this->front->data = value;
            this->front->next = nullptr;

            this->rear = this->front;
        }
        else
        {
            this->rear->next = new Node();
            this->rear = this->rear->next;
            this->rear->data = value;
            this->rear->next = nullptr;
        }

        this->size++;
    }

    int showfront()
    {
        if (size != 0)
            return front->data;
    }

    void dequeue()
    {
        if (this->size != 0)
        {
            Node *to_delete = this->front;
            this->front = this->front->next;
            delete to_delete;

            this->size--;
        }
    }

    bool isempty()
    {
        return size == 0;
    }

    int getSize()
    {
        return size;
    }

    void print()
    {
        Node *node = front;

        if (node == nullptr)
            return;

        std::cout << "front ";

        while (node->next != nullptr)
        {
            std::cout << node->data << " <- ";

            node = node->next;
        }

        std::cout << node->data << " rear" << std::endl;
    }
};

int main()
{
    Queue q = Queue();

    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);
    q.enqueue(7);

    q.print();

    std::cout << q.showfront() << std::endl;

    q.dequeue();
    q.dequeue();
    q.dequeue();
    q.dequeue();
    std::cout << q.getSize() << std::endl;
    q.print();
}