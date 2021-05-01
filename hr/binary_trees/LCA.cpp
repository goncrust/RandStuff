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

    /*The tree node has data, left child and right child 
class Node {
    int data;
    Node* left;
    Node* right;
};

*/

    int findDepth(Node *root, int value, int level)
    {
        if (root == nullptr)
        {
            return 0;
        }

        if (root->data == value)
        {
            return level;
        }

        int next_level_left = findDepth(root->left, value, level + 1);
        if (next_level_left != 0)
        {
            return next_level_left;
        }
        else
        {
            int next_level_right = findDepth(root->right, value, level + 1);
            if (next_level_right != 0)
            {
                return next_level_right;
            }
        }

        return 0;
    }

    Node *lca(Node *root, int v1, int v2)
    {
        Node *result;
        int min_v1;
        int min_v2;
        bool first_time = true;

        queue<Node *> q;
        q.push(root);
        while (!q.empty())
        {
            Node *node = q.front();
            q.pop();

            int depth_v1 = findDepth(node, v1, 1);
            int depth_v2 = findDepth(node, v2, 1);

            if (depth_v1 != 0 && depth_v2 != 0)
            {
                if (first_time)
                {
                    min_v1 = depth_v1;
                    min_v2 = depth_v2;
                    result = node;
                    first_time = false;
                }
                else
                {
                    if (depth_v1 <= min_v1 && depth_v2 <= min_v2)
                    {
                        min_v1 = depth_v1;
                        min_v2 = depth_v2;
                        result = node;
                    }
                }
            }

            if (node->left != nullptr)
                q.push(node->left);
            if (node->right != nullptr)
                q.push(node->right);
        }

        return result;
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

    int v1, v2;
    std::cin >> v1 >> v2;

    Node *ans = myTree.lca(root, v1, v2);

    std::cout << ans->data;

    return 0;
}
