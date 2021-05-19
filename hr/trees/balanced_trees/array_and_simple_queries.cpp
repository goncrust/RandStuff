#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Node
{
public:
    int data;
    Node *next;

    Node(int data, Node *next) : data(data), next(next) {}
};

class LinkedList
{
private:
    Node *last;
    Node *first;

public:
    LinkedList() {}

    void insert(int data)
    {
        if (last == nullptr)
        {
            last = new Node(data, nullptr);
            first = last;
        }
        else
        {
            last->next = new Node(data, nullptr);
            last = last->next;
        }
    }

    void insert_back(int data)
    {
        first = new Node(data, first);
    }

    vector<int> remove(int first, int second)
    {
        Node *pre_first_node;
        Node *first_node = this->first;
        vector<int> numbers;

        for (int i = 0; i < first - 1; i++)
        {
            first_node = first_node->next;
        }
        pre_first_node = first_node;
        if (first != 0)
        {
            first_node = first_node->next;
        }
        else
        {
            pre_first_node = nullptr;
        }

        Node *second_node;
        for (int i = 0; i < second - first + 1; i++)
        {
            second_node = first_node->next;
            numbers.push_back(first_node->data);
            delete first_node;
            first_node = second_node;
        }

        if (second_node == nullptr)
        {
            this->last = pre_first_node;
        }
        else if (pre_first_node == nullptr)
        {
            this->first = second_node;
        }
        else
        {
            pre_first_node->next = second_node;
        }

        return numbers;
    }

    void add_to_front(int first, int second)
    {
        vector<int> numbers = remove(first, second);

        for (int i = numbers.size(); i > 0; i--)
        {
            insert_back(numbers[i - 1]);
        }
    }

    void add_to_back(int first, int second)
    {
        vector<int> numbers = remove(first, second);

        for (int n : numbers)
            insert(n);
    }

    void print()
    {
        Node *node = this->first;
        while (node != nullptr)
        {
            cout << node->data << " ";
            node = node->next;
        }
    }

    int getResult()
    {
        int result = this->first->data - this->last->data;

        if (result < 0)
            result = -result;

        return result;
    }
};

int main()
{
    int N;
    int M;
    scanf("%d %d", &N, &M);

    LinkedList A;
    while (N--)
    {
        int n;
        scanf("%d", &n);
        A.insert(n);
    }

    vector<vector<int>> queries;
    while (M--)
    {
        int q;
        int i;
        int j;
        vector<int> query;
        scanf("%d %d %d", &q, &i, &j);
        query.push_back(q);
        query.push_back(i);
        query.push_back(j);

        queries.push_back(query);
    }

    for (vector<int> query : queries)
    {
        int i = query[1];
        int j = query[2];

        i--;
        j--;

        if (query[0] == 1)
        {
            A.add_to_front(i, j);
        }
        else if (query[0] == 2)
        {
            A.add_to_back(i, j);
        }
    }

    cout << A.getResult() << endl;
    A.print();

    return 0;
}
