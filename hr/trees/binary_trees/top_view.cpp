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
    Node *insert(Node *root, int data)
    {
        if (root == NULL)
        {
            return new Node(data);
        }
        else
        {
            Node *cur;
            if (data <= root->data)
            {
                cur = insert(root->left, data);
                root->left = cur;
            }
            else
            {
                cur = insert(root->right, data);
                root->right = cur;
            }

            return root;
        }
    }

    /*
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

    class Node2
    {
    public:
        int data;
        Node2 *left;
        Node2 *right;
        int height;
        int x;
    };

    void print_2(Node2 *root)
    {
        if (root == nullptr)
            return;

        cout << root->data << " " << root->height << " " << root->x << endl;
        print_2(root->left);
        print_2(root->right);
    }

    void print_1(Node *root)
    {
        if (root == nullptr)
            return;

        cout << root->data << " " << endl;
        print_1(root->left);
        print_1(root->right);
    }

    int getX(Node *root, Node *node, int x)
    {
        queue<Node *> q;
        queue<int> xq;
        q.push(root);
        xq.push(x);
        while (!q.empty())
        {
            Node *cur = q.front();
            q.pop();
            int cur_x = xq.front();
            xq.pop();
            if (cur == node)
            {
                return cur_x;
            }

            if (cur->left != nullptr)
            {
                q.push(cur->left);
                xq.push(cur_x - 1);
            }
            if (cur->right != nullptr)
            {
                q.push(cur->right);
                xq.push(cur_x + 1);
            }
        }

        return 0;
    }

    int getLevel(Node *root, Node *node, int level)
    {
        if (root == nullptr)
        {
            return 0;
        }

        if (root == node)
        {
            return level;
        }

        int next_level_left = getLevel(root->left, node, level + 1);

        if (next_level_left != 0)
        {
            return next_level_left;
        }
        else
        {
            int next_level_right = getLevel(root->right, node, level + 1);

            return next_level_right;
        }
    }

    Node2 *insert_height_x(Node2 *root, int value, int height, int x)
    {
        if (root == nullptr)
        {
            root = new Node2();
            root->data = value;
            root->height = height;
            root->x = x;
            root->left = nullptr;
            root->right = nullptr;

            return root;
        }
        else
        {
            Node2 *cur;
            if (value <= root->data)
            {
                cur = insert_height_x(root->left, value, height, x);
                root->left = cur;
            }
            else
            {
                cur = insert_height_x(root->right, value, height, x);
                root->right = cur;
            }

            return root;
        }
    }

    void heights(Node *root)
    {

        if (root == nullptr)
            return;

        node2 = insert_height_x(node2, root->data, getLevel(original_root, root, 0), getX(original_root, root, 0));
        heights(root->left);
        heights(root->right);

        // queue<Node *> q;
        // q.push(root);
        // while (!q.empty())
        // {
        //     Node *node = q.front();
        //     q.pop();
        //     node2 = insert_height_x(node2, node->data, getLevel(original_root, node, 0), getX(original_root, node, 0));

        //     if (node->left != nullptr)
        //         q.push(node->left);
        //     if (node->right != nullptr)
        //         q.push(node->right);
        // }
    }

    class Result
    {
    public:
        int value;
        int height;
        int x;

        Result(int value, int height, int x) : value(value), height(height), x(x)
        {
        }
    };

    vector<Result *> results;
    void results_vector(Node2 *node2)
    {
        if (node2 == nullptr)
            return;

        results.push_back(new Result(node2->data, node2->height, node2->x));
        results_vector(node2->left);
        results_vector(node2->right);
    }

    Node *original_root;
    Node2 *node2 = nullptr;

    vector<int> final_result;
    void topView(Node *root)
    {
        original_root = root;
        heights(root);

        // print_1(root);
        // print_2(node2);

        results_vector(node2);

        for (int i = results.size() - 1; i > 0; i--)
        {
            for (int y = 0; y < i; y++)
            {
                if (results[y]->x > results[y + 1]->x)
                {
                    Result *cache = results[y];
                    results[y] = results[y + 1];
                    results[y + 1] = cache;
                }
            }
        }

        for (int i = 0; i < results.size(); i++)
        {
            int value = results[i]->value;
            int height = results[i]->height;
            int x = results[i]->x;

            bool succ = true;
            for (int y = 0; y < results.size(); y++)
            {
                if (i == y)
                    continue;

                int height_y = results[y]->height;
                int x_y = results[y]->x;

                if (height_y < height)
                {
                    if (x == x_y)
                    {
                        succ = false;
                        break;
                    }
                }
            }

            if (succ)
                final_result.push_back(value);
        }

        for (int i = 0; i < final_result.size(); i++)
        {
            cout << final_result[i] << " ";
        }
    }

}; //End of Solution

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

    myTree.topView(root);
    return 0;
}
