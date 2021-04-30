/* Hidden stub code will pass a root argument to the function below. Complete the function to solve the challenge. Hint: you may want to write one or more helper functions.  

The Node struct is defined as follows:
    struct Node {
        int data;
        Node* left;
        Node* right;
    }
*/
vector<int> tree_values;
void tree_values_set(Node *root)
{
    if (root == nullptr)
        return;

    tree_values_set(root->left);
    tree_values.push_back(root->data);
    tree_values_set(root->right);
}

bool checkBST(Node *root)
{

    tree_values_set(root);

    for (int i = 0; i < tree_values.size(); i++)
    {
        if (tree_values[i - 1] >= tree_values[i])
        {
            return false;
        }
    }

    return true;
}

// or

/* Hidden stub code will pass a root argument to the function below. Complete the function to solve the challenge. Hint: you may want to write one or more helper functions.  

The Node struct is defined as follows:
    struct Node {
        int data;
        Node* left;
        Node* right;
    }
*/
bool checkBST_(Node *root, int max, int min)
{
    if (root == nullptr)
        return true;

    if (root->data < max && root->data > min)
    {
        return checkBST_(root->left, root->data, min) && checkBST_(root->right, max, root->data);
    }
    else
        return false;
}

bool checkBST(Node *root)
{

    return checkBST_(root, 2147483647, 0);
}