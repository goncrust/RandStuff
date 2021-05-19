node *insert(node *root, int val)
{
    if (!root)
        return (create(val));
    if (val < root->val)
    {
        if (!root->left)
            root->left = create(val);
        root->left = insert(root->left, val);
    }
    if (val > root->val)
    {
        if (!root->right)
            root->right = create(val);
        root->right = insert(root->right, val);
    }
    else
        return root;

    root = rebalance(root);
    return root;
}
int height(node *root)
{
    if (!root)
        return -1;
    return root->ht;
}
int bf(node *root)
{
    if (!root)
        return -1;
    return (height(root->left) - height(root->right));
}
int updateHeight(node *root)
{
    return 1 + max(height(root->left), height(root->right));
}
node *left_rotate(node *old_root)
{
    auto *new_root = old_root->right;
    old_root->right = new_root->left;
    new_root->left = old_root;
    //update heights
    old_root->ht = updateHeight(old_root);
    new_root->ht = updateHeight(new_root);
    return new_root;
}

node *right_rotate(node *old_root)
{
    auto *new_root = old_root->left;
    old_root->left = new_root->right;
    new_root->right = old_root;
    //update heights
    old_root->ht = updateHeight(old_root);
    new_root->ht = updateHeight(new_root);
    return new_root;
}

node *rebalance(node *root)
{
    //update height
    root->ht = updateHeight(root);
    if (bf(root) < -1)
    {
        if (bf(root->right) > 0)
        { //val < root->right->val
            //double rotation case
            root->right = right_rotate(root->right);
        }
        return left_rotate(root);
    }
    else if (bf(root) > 1)
    {
        if (bf(root->left) > 0)
        {
            //double rotation case
            root->left = left_rotate(root->left);
        }
        return right_rotate(root);
    }
    return root;
}

node *create(int newVal)
{
    node *newNode = new node;
    newNode->val = newVal;
    newNode->ht = 0;
    newNode->left = newNode->right = nullptr;
    return newNode;
}