#include <bits/stdc++.h>

using namespace std;

class Node
{
public:
    int data;
    Node *left;
    Node *right;
    Node(int d)
    {
        data = d;
        left = NULL;
        right = NULL;
    }
};

class Solution
{
public:
    void preOrder(Node *root)
    {

        if (root == NULL)
            return;

        std::cout << root->data << " ";

        preOrder(root->left);
        preOrder(root->right);
    }

    /*
Node is defined as 

class Node {
    public:
        int data;
        Node *left;
        Node *right;
        Node(int d) {
            data = d;
            left = NULL;
            right = NULL;
        }
};

*/

    Node *insert(Node *root, int data)
    {

        Node *node = root;

        if (root == nullptr)
        {
            root = new Node(data);
            return root;
        }

        while (true)
        {
            if (node->data > data)
            {
                if (node->left == nullptr)
                {
                    node->left = new Node(data);
                    break;
                }

                node = node->left;
            }
            else
            {
                if (node->right == nullptr)
                {
                    node->right = new Node(data);
                    break;
                }

                node = node->right;
            }
        }

        return root;
    }
};

int main()
{

    Solution myTree;
    Node *root = NULL;

    int t;
    int data;

    std::cin >> t;

    while (t-- > 0)
    {
        std::cin >> data;
        root = myTree.insert(root, data);
    }

    myTree.preOrder(root);

    return 0;
}
