#include <iostream>

class Node
{
public:
    int data;
    Node *next;

    Node(int data, Node *next)
    {
        this->data = data;
        this->next = next;
    }
};

class Stack
{
private:
    Node *top;
    Node *bot;

    int size = 0;

public:
    Stack() {}

    void push(int data)
    {
        if (!this->size)
        {
            this->top = new Node(data, nullptr);
            this->bot = this->top;
        }
        else
        {
            this->top->next = new Node(data, nullptr);
            this->top = this->top->next;
        }

        this->size++;
    }

    int pop()
    {
        if (!this->size)
            return 0;

        int data = this->top->data;

        Node *node = this->bot;
        while (node->next != this->top)
            node = node->next;

        node->next = nullptr;
        delete top;
        this->top = node;

        this->size--;

        return data;
    }

    bool isempty()
    {
        if (this->size == 0)
            return true;
        return false;
    }

    int count()
    {
        return this->size;
    }

    void print()
    {
        dfs(this->bot);
    }

    void dfs(Node *root)
    {
        if (root == nullptr)
            return;
        dfs(root->next);
        std::cout << root->data << std::endl;
    }
};

int main()
{
    Stack s = Stack();
    s.push(2);
    s.push(1);
    s.push(15);

    std::cout << s.count();

    s.print();
}