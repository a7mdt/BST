#include "bits/stdc++.h"
using namespace std;

// Binary Search Tree

class BST
{
private:
    struct node
    {
        int data;
        node* leftNode;
        node* rightNode;
    };
    node* root = nullptr;
    int depthHelper(node* checker);
    void preOrderHelper(node* checker);
    void inOrderHelper(node* checker);
    void postOrderHelper(node* checker);
    node* deleteHelper(node* parent, int data) // its type is node* 3ashan e7na 7nrga3 el root w howa pointer asasa.
    {
        if(parent == nullptr)
            return parent;

        /*
            El fayda mn el 2 Lines :
                 parent->leftNode = deleteHelper(parent->leftNode , data);
                 parent->rightNode = deleteHelper(parent->rightNode , data);
            hya eny lma ams7 el address bta3 el parent zy m 7n3ml f el else
            m7tageen n5ly el child bta3aha da howa child mkan elly ms7naa.
         */

        // n Search a7na 7nro7 feen el awl law msh la'yen el data :
        else if(data < parent->data)
            parent->leftNode = deleteHelper(parent->leftNode , data);

        else if(data > parent->data)
            parent->rightNode = deleteHelper(parent->rightNode , data);

        // la'ena el Data 5alas :
        else // ana kda 3and el node elly 3ayez ams7a f3la ==> our 3 Cases
        {
            if(parent->leftNode == nullptr) // el node 3andaha one child -> R
            {
                node* tempRight = parent->rightNode; // ha5ed el address bta3 el Child da f el pointer temp
                delete parent; // nms7 el address with its value bta3 el pointer da
                return tempRight; // na5ed el address bta3 el value el gdeda b2a
            }
            else if(parent->rightNode == nullptr) // el node 3andaha one child -> L
            {
                node* tempLeft = parent->leftNode; // ha5ed el address bta3 el Child da f el pointer temp
                delete parent; // nms7 el current value bta3et el pointer da
                return tempLeft; // na5ed el value el gdeda b2a
            }
            else // The node has 2 children (L and R)
            {
                node* maxLeft = parent->leftNode;

                while(maxLeft->rightNode != nullptr)
                    maxLeft = maxLeft->rightNode;

                parent->data = maxLeft->data; // hn5ly el value elly 7ttms7 btsawy el value elly ana 3ayezha el gdida
                parent->leftNode = deleteHelper(parent->leftNode , maxLeft->data); // w hn3ml el step de 3ashan nms7 el maxLeft mn a5r el Tree.
            }
        }
        return parent;
    }

public:
    bool emptyTree();
    void insertNode(int value);
    int maxNode();
    int minNode();
    int getDepth();
    void preOrder();
    void inOrder();
    void postOrder();
    void deleteNode(int data);
};

int main()
{
    cout<<endl;

    BST obj;

    cout<<"-Is the Tree Empty ? "<<endl;
    cout<<"-> "<<(obj.emptyTree() ? "YES" : "NO")<<endl;
    cout<<endl;

    // Note : its The same nodes of our Discrete Exam.
    obj.insertNode(50);
    obj.insertNode(27);
    obj.insertNode(16);
    obj.insertNode(88);
    obj.insertNode(34);
    obj.insertNode(65);
    obj.insertNode(52);
    obj.insertNode(77);
    obj.insertNode(93);
    obj.insertNode(4);
    obj.insertNode(12);
    obj.insertNode(29);
    obj.insertNode(44);
    obj.insertNode(92);

    cout<<"-InOrder Display : ";
    obj.inOrder();
    cout<<endl;

    cout<<"-PreOrder Display : ";
    obj.preOrder();
    cout<<endl;

    cout<<"-PostOrder Display : ";
    obj.postOrder();
    cout<<endl;

    cout<<"-Now, Is the Tree Empty ? "<<endl;
    cout<<"-> "<<(obj.emptyTree() ? "YES" : "NO")<<endl;
    cout<<endl;

    cout<<"-The Heighest node in the Tree is : "<<obj.maxNode();
    cout<<endl;

    cout<<"-The Lowest node in the Tree is : "<<obj.minNode();
    cout<<endl;

    cout<<"-The Depth of the Tree is : "<<obj.getDepth();
    cout<<endl<<endl;

    obj.deleteNode(12);
    obj.deleteNode(77);

    cout<<"-InOrder Display (after delete 12 , 77) : ";
    obj.inOrder();
    cout<<endl;

    cout<<"-PreOrder Display (after delete 12 , 77) : ";
    obj.preOrder();
    cout<<endl;

    cout<<"-PostOrder Display (after delete 12 , 77) : ";
    obj.postOrder();
    cout<<endl;

    return 0;
}

bool BST::emptyTree()
{
    if(root==nullptr)
        return true;
    else
        return false;
}

void BST::insertNode(int value)
{
    node* newNode = new node;
    newNode->data = value;
    newNode->leftNode = nullptr;
    newNode->rightNode = nullptr;

    if(emptyTree())
        root = newNode;

    else
    {
        node* checker = root;
        node* parent = nullptr; // el ptr da hnshel feh el Node elly hn Add feha

        while(checker != nullptr)
        {
            parent = checker;

            if(value <= checker->data)
                checker = checker->leftNode;
            else
                checker = checker->rightNode;
        }

        if(value <= parent->data)
            parent->leftNode = newNode;
        else
            parent->rightNode = newNode;
    }
}

int BST::maxNode()
{
    node* checker = root;

    while(checker->rightNode != nullptr)
        checker = checker->rightNode;

    return checker->data;
}

int BST::minNode()
{
    node* checker = root;

    while(checker->leftNode != nullptr)
        checker = checker->leftNode;

    return checker->data;
}

int BST::depthHelper(node *checker)
{
    if(checker== nullptr)
        return 0;

    else
    {
        int leftSubTree = depthHelper(checker->leftNode);
        int rightSubTree = depthHelper(checker->rightNode);

        return 1+max(leftSubTree,rightSubTree);
    }
}

int BST::getDepth()
{
    if(emptyTree())
        return 0;

    else
    {
        return depthHelper(root);
    }
}

// inorder : left -> root -> right
void BST::inOrderHelper(node *checker)
{
    // n check feh nodes asln ana h Traverse 3aliha wala laa (SubTree).
    if (checker == nullptr)
        return;

    inOrderHelper(checker->leftNode);
    cout << checker->data << "  ";
    inOrderHelper(checker->rightNode);
}

void BST::inOrder()
{
    inOrderHelper(root);
}

// preorder : root -> left -> right
void BST::preOrderHelper(node *checker)
{
    if (checker == nullptr)
        return;

    cout << checker->data << "  ";
    preOrderHelper(checker->leftNode);
    preOrderHelper(checker->rightNode);
}

void BST::preOrder()
{
    preOrderHelper(root);
}

// postorder : left -> right -> root
void BST::postOrderHelper(node *checker)
{
    if (checker == nullptr)
        return;

    postOrderHelper(checker->leftNode);
    postOrderHelper(checker->rightNode);
    cout << checker->data << "  ";
}

void BST::postOrder()
{
    postOrderHelper(root);
    cout<<endl;
}

/*
-> The Delete Function will have 3 cases :

1- If the node is The last node at the tree (leaf node)
    -- We will delete it and set it as NULL.
2- If the node has 1 child (L or R)
    -- We will delete this node and put its child instead of it.
3- If the node has 2 child (L and R)
    -- We will delete this node and put the heighst node at the left subTree instead of this
        --- Note: Don't forget to delete the heighst node from the subTree.
*/

void BST::deleteNode(int data)
{
    root = deleteHelper(root, data);
}