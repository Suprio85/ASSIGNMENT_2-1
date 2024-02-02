#include <bits/stdc++.h>
#include "color.hpp"
using namespace std;

#define red 0
#define black 1

template <typename T>
struct node
{
    int key;
    T value;
    node<T> *left;
    node<T> *right;
    node<T> *parent;
    int color;

    node(int key, T value)
    {
        this->key = key;
        this->value = value;
        this->left = NULL;
        this->right = NULL;
        this->parent = NULL;
        this->color = red;
    }

    node()
    {
        this->left = NULL;
        this->right = NULL;
        this->parent = NULL;
        this->color = red;
    }

    void moveDown(node<T> *nParent)
    {
        if (parent != NULL)
        {
            if (this == parent->left)
            {
                parent->left = nParent;
            }
            else
            {
                parent->right = nParent;
            }
        }
        nParent->parent = parent;
        parent = nParent;
    }
};

template <typename T>
class Red_Black_Tree
{

private:
    node<T> *root;
    int size;
    bool ll;
    bool rr;
    bool lr;
    bool rl;

    node<T> *right_rotate(node<T> *curr)
    {
        auto temp = curr->left;
        node<T> *x = temp->right;
        curr->left = x;
        temp->right = curr;
        curr->parent = temp;

        if (x != NULL)
        {
            x->parent = curr;
        }
        // cout << "right rotate" << endl;

        return temp;
    }

    node<T> *left_rotate(node<T> *curr)
    {
        auto temp = curr->right;
        node<T> *x = temp->left;
        curr->right = x;
        temp->left = curr;
        curr->parent = temp;

        if (x != NULL)
        {
            x->parent = curr;
        }

        return temp;
    }

    void rightRotate(node<T> *x)
    {
        node<T> *nParent = x->left;
        if (x == root)
            root = nParent;

        x->moveDown(nParent);
        x->left = nParent->right;
        if (nParent->right != NULL)
            nParent->right->parent = x;
        nParent->right = x;
    }

    void leftRotate(node<T> *x)
    {
        node<T> *nParent = x->right;
        if (x == root)
            root = nParent;

        x->moveDown(nParent);
        x->right = nParent->left;
        if (nParent->left != NULL)
            nParent->left->parent = x;
        nParent->left = x;
    }

    node<T> *insert_help(node<T> *curr, int key, T value)
    {

        bool red_red_conflict = false;

        if (curr == NULL)
        {
            this->size++;
            return new node<T>(key, value);
        }
        if (curr->key == key)
        {
            curr->value = value;
            return curr;
        }

        else if (curr->key > key)
        {
            curr->left = insert_help(curr->left, key, value);
            curr->left->parent = curr;
            if (curr->color == red and curr->left->color == red)
            {
                red_red_conflict = true;
            }
        }

        else if (curr->key < key)
        {
            curr->right = insert_help(curr->right, key, value);
            curr->right->parent = curr;
            if (curr->color == red and curr->right->color == red)
            {
                red_red_conflict = true;
            }
        }

        if (rr)
        {
            curr = left_rotate(curr);
            curr->color = black;
            curr->left->color = red;
            rr = false;
        }

        else if (ll)
        {
            curr = right_rotate(curr);
            curr->color = black;
            curr->right->color = red;
            ll = false;
        }

        else if (lr)
        {
            curr->left = left_rotate(curr->left);

            curr = right_rotate(curr);
            curr->color = black;
            curr->right->color = red;
            lr = false;
        }

        else if (rl)
        {
            curr->right = right_rotate(curr->right);

            curr = left_rotate(curr);
            curr->color = black;
            curr->left->color = red;
            rl = false;
        }

        if (red_red_conflict)
        {
            if (curr->parent->right == curr)
            {
                if (curr->parent->left != NULL and curr->parent->left->color == red)
                {
                    curr->parent->left->color = black;
                    curr->color = black;

                    if (curr->parent != this->root)
                        curr->parent->color = red;
                    // cout << "resolved with color change";
                }
                else
                {
                    if (curr->left != NULL and curr->left->color == red)
                    {
                        rl = true;
                    }
                    else if (curr->right != NULL and curr->right->color == red)
                    {
                        rr = true;
                    }
                }
            }

            else
            {
                if (curr->parent->right != NULL and curr->parent->right->color == red)
                {
                    curr->parent->right->color = black;
                    curr->color = black;

                    if (curr->parent != this->root)
                        curr->parent->color = red;
                }
                else
                {
                    if (curr->right != NULL and curr->right->color == red)
                    {
                        lr = true;
                    }
                    else if (curr->left != NULL and curr->left->color == red)
                    {
                        ll = true;
                    }
                }
            }

            red_red_conflict = false;
        }

        return curr;
    }

    node<T> *Successor(node<T> *curr)
    {
        auto temp = curr->right;
        while (temp->left != NULL)
        {
            temp = temp->left;
        }
        return temp;
    }

    node<T> *sibling(node<T> *curr)
    {
        if (curr->parent == NULL)
            return NULL;
        if (curr->parent->left == curr)
            return curr->parent->right;

        return curr->parent->left;
    }

    void delete_helper(node<T> *v)
    {
        node<T> *u = NULL;

        if (v->left != NULL and v->right != NULL)
        {
            u = Successor(v);
        }

        else if (v->left == NULL and v->right == NULL)
        {
            u = NULL;
        }

        else
        {
            if (v->left != NULL)
            {
                u = v->left;
            }
            else
            {
                u = v->right;
            }
        }

        bool uvBlack = ((u == NULL or u->color == black) and (v->color == black));
        node<T> *parent = v->parent;
        node<T> *sib = sibling(v);

        if (u == NULL)
        {
            if (v == this->root)
            {
                this->root = NULL;
            }
            else
            {
                if (uvBlack)
                {
                    fixDoubleBlack(v);
                }
                // else if (sib != NULL)
                // {
                //     sib->color = red;
                // }
            }

            if (v->parent->left == v)
            {
                v->parent->left = NULL;
            }
            else
            {
                v->parent->right = NULL;
            }

            return;
        }

        if (v->left == NULL or v->right == NULL)
        {
            if (v == this->root)
            {
                v->key = u->key;
                v->value = u->value;
                v->left = v->right = NULL;
                delete u;
            }
            else
            {
                if (v->parent->left == v)
                {
                    v->parent->left = u;
                }
                else
                {
                    v->parent->right = u;
                }
                delete v;
                u->parent = parent;
                if (uvBlack)
                {
                    fixDoubleBlack(u);
                }
                else
                {
                    u->color = black;
                }
            }
            return;
        }

        if (v->left != NULL and v->right != NULL)
        {
            swap(u->key, v->key);
            swap(u->value, v->value);
            delete_helper(u);
        }
    }

    void fixDoubleBlack(node<T> *x)
    {
        node<T> *sib = sibling(x);
        node<T> *parent = x->parent;

        if (x == this->root)
        {
            return;
        }

        if (sib == NULL)
        {
            fixDoubleBlack(parent);
        }
        else
        {
            if (sib->color == red)
            {
                parent->color = red;
                sib->color = black;
                if (sib->parent->left == sib)
                {
                     rightRotate(parent);
                }
                else
                {
                     leftRotate(parent);
                }
                // if (parent->parent != nullptr)
                // {
                //     if (parent->parent->left == x->parent)
                //     {
                //         parent->parent->left = parent;
                //     }
                //     else
                //     {
                //         parent->parent->right = parent;
                //     }
                // }
                // else
                // {
                //     this->root = parent;
                // }
                fixDoubleBlack(x);
            }
            else
            {
                if (sib->left != NULL and sib->left->color == red)
                {
                    if (sib->parent->left == sib)
                    {
                        sib->left->color = sib->color;
                        sib->color = parent->color;
                        parent->color = black;
                        rightRotate(parent);
                    }
                    else
                    {
                        sib->left->color = parent->color;
                        parent->color = black;
                        rightRotate(sib);
                        leftRotate(parent);
                    }
                }
                else if (sib->right != NULL and sib->right->color == red)
                {
                    if (sib->parent->left == sib)
                    {
                        sib->right->color = parent->color;
                        parent->color = black;
                             leftRotate(sib);
                             rightRotate(parent);
                    }
                    else
                    {
                        sib->right->color = sib->color;
                        sib->color = parent->color;
                        parent->color = black;
                        leftRotate(parent);
                    }
                }
                else
                {
                    sib->color = red;
                    if (parent->color == black)
                    {
                        fixDoubleBlack(parent);
                    }
                    else
                    {
                        parent->color = black;
                    }
                }
            }
        }
    }

    void print_helper(node<T> *root)
    {
        if (root == NULL)
        {
            return;
        }
        if (root->color == red)
        {
            cout << dye::red_on_black(root->key);
            cout << dye::red_on_black("_");
            cout << dye::red_on_black(root->value);
        }
        else
            cout << root->key << "_" << root->value;

        if (root->left != NULL || root->right != NULL)
        {
            cout << "(";
            print_helper(root->left);
            cout << ",";
            print_helper(root->right);
            cout << ")";
        }
    }

    node<T> *find_helper(node<T> *root, int key)
    {
        if (root == NULL)
        {
            return root;
        }

        else if (root->key > key)
        {
            return find_helper(root->left, key);
        }

        else if (root->key < key)
        {
            return find_helper(root->right, key);
        }

        else
        {
            return root;
        }
    }

    void iterate_helper(node<T> *root)
    {
        if (root == NULL)
            return;

        iterate_helper(root->left);
        if (root->color == red)
        {
            cout << dye::red_on_black(root->key);
            cout << "=> ";
            cout << dye::red_on_black(root->value) << " " << endl;
            ;
        }
        else
        {
            cout << root->key << "=> " << root->value << " " << endl;
        }
        iterate_helper(root->right);
    }

public:
    Red_Black_Tree()
    {
        this->root = NULL;
        this->ll = false;
        this->rr = false;
        this->lr = false;
        this->rl = false;
        size = 0;
    }

    ~Red_Black_Tree()
    {
        clear();
    }

    node<T> *insert(int key, T value)
    {
        if (this->root == NULL)
        {
            this->root = new node<T>(key, value);
            this->root->color = black;
            this->size++;
        }
        else
        {
            this->root = insert_help(this->root, key, value);
        }
        if (root->parent)
        {
            root->parent = NULL;
        }
        return this->root;
    }

    node<T> *delete_node(int key)
    {
        auto temp = find_helper(this->root, key);
        if (temp == NULL)
        {
            return NULL;
        }

        delete_helper(temp);
        this->size--;
        return this->root;
    }

    void print()
    {
        print_helper(this->root);
        cout << endl;
    }

    void iterate()
    {
        iterate_helper(this->root);
    }

    node<T> *find(int key)
    {
        auto temp = find_helper(this->root, key);

        if (temp == NULL)
            return NULL;
        else
            return temp;
    }

    int size_tree()
    {
        return this->size;
    }

    bool isempty()
    {
        return this->size == 0;
    }

    bool clear()
    {
        if (this->root == NULL and size == 0)
            return false;
        else
        {

            delete this->root;
            this->root = NULL;
            size = 0;
            return true;
        }
    }
};
