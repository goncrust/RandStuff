#include <bits/stdc++.h>

using namespace std;

class Node
{
public:
    int data;
    Node *left;
    Node *right;

    Node(int data, Node *left, Node *right) : data(data), left(left), right(right)
    {
    }
};

int getDepth(Node *root, Node *node, int level)
{
    if (root == nullptr)
    {
        return 0;
    }

    if (root == node)
    {
        return level;
    }

    int left = getDepth(root->left, node, level + 1);
    if (left != 0)
    {
        return left;
    }
    else
    {
        return getDepth(root->right, node, level + 1);
    }
}

Node *original_root;
void invert_nodes(Node *root, int query)
{

    if (root == nullptr)
        return;

    int depth = getDepth(original_root, root, 1);
    if (depth % query == 0)
    {
        Node *left = root->left;
        root->left = root->right;
        root->right = left;
    }

    invert_nodes(root->left, query);
    invert_nodes(root->right, query);
}

void in_order_vector(Node *root, vector<int> *subvector)
{
    if (root == nullptr)
    {
        return;
    }

    in_order_vector(root->left, subvector);
    subvector->push_back(root->data);
    in_order_vector(root->right, subvector);
}

vector<vector<int>> swapNodes(vector<vector<int>> indexes, vector<int> queries)
{
    Node *root = new Node(1, nullptr, nullptr);
    original_root = root;

    // make tree
    queue<Node *> q;
    q.push(root);
    int index = 0;
    while (!q.empty())
    {
        Node *node = q.front();
        q.pop();

        int left = indexes[index][0];
        int right = indexes[index][1];

        if (left != -1)
        {
            node->left = new Node(left, nullptr, nullptr);
        }

        if (right != -1)
        {
            node->right = new Node(right, nullptr, nullptr);
        }

        index++;

        if (node->left != nullptr)
            q.push(node->left);
        if (node->right != nullptr)
            q.push(node->right);
    }

    // invert nodes (queries)
    vector<vector<int>> result;
    for (int i = 0; i < queries.size(); i++)
    {
        invert_nodes(root, queries[i]);
        vector<int> subvector;
        in_order_vector(root, &subvector);
        result.push_back(subvector);
    }

    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<int>> indexes(n);
    for (int indexes_row_itr = 0; indexes_row_itr < n; indexes_row_itr++)
    {
        indexes[indexes_row_itr].resize(2);

        for (int indexes_column_itr = 0; indexes_column_itr < 2; indexes_column_itr++)
        {
            cin >> indexes[indexes_row_itr][indexes_column_itr];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int queries_count;
    cin >> queries_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> queries(queries_count);

    for (int queries_itr = 0; queries_itr < queries_count; queries_itr++)
    {
        int queries_item;
        cin >> queries_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        queries[queries_itr] = queries_item;
    }

    vector<vector<int>> result = swapNodes(indexes, queries);

    for (int result_row_itr = 0; result_row_itr < result.size(); result_row_itr++)
    {
        for (int result_column_itr = 0; result_column_itr < result[result_row_itr].size(); result_column_itr++)
        {
            fout << result[result_row_itr][result_column_itr];

            if (result_column_itr != result[result_row_itr].size() - 1)
            {
                fout << " ";
            }
        }

        if (result_row_itr != result.size() - 1)
        {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}
