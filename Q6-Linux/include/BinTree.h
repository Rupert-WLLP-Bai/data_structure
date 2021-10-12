
#include <cstdlib>
#include <deque>
#include <iostream>
#include <stack>
using namespace std;

template <class T>
struct BinTreeNode  //二叉树节点类的定义，使用二叉链表
{
    T data;
    BinTreeNode<T>*leftChild, *rightChild;
    BinTreeNode()
        : leftChild(NULL), rightChild(NULL) {}
    BinTreeNode(T x, BinTreeNode<T>* l = NULL, BinTreeNode<T>* r = NULL)
        : data(x), leftChild(l), rightChild(r) {}
};

template <class T>
class BinaryTree  //二叉树的模板类
{
   public:
    BinaryTree()
        : root(NULL) {}
    BinaryTree(char x)
        : root(NULL), RefValue(x) {}
    BinaryTree(const BinaryTree<T>& rhs) { root = copy(rhs.root); }  //copy构造函数
    BinaryTree<T>& operator=(const BinaryTree<T>& rhs);              //copy 赋值运算符;析构+copy构造函数
    ~BinaryTree() { destroy(root); }                                 //析构函数
    bool isEmpty() const { return root != NULL ? false : true; }
    BinTreeNode<T>* leftChild(BinTreeNode<T>* current) const { return current != NULL ? current->leftChild : NULL; }                    //获取左子节点
    BinTreeNode<T>* rightChild(BinTreeNode<T>* current) const { return current != NULL ? current->rightChild : NULL; }                  //获取右子节点
    BinTreeNode<T>* parent(BinTreeNode<T>* current) const { return (root == NULL || current == root) ? NULL : parent(root, current); }  //寻找其父节点
    BinTreeNode<T>* getRoot() const { return root; }                                                                                    //获取根节点
    bool Insert(BinTreeNode<T>* ins, BinTreeNode<T>* pos, int side);                                                                    //插入节点到某一节点的左或者右子节点
    bool Remove(BinTreeNode<T>* del);                                                                                                   //递归删除某一节点
    BinTreeNode<T>* Search(const T key);                                                                                                //查找某一数值 返回节点地址或者NULL
    bool Rename(BinTreeNode<T>* node, T newkey);                                                                                        //修改某一节点的值为Newkey
    void inOrder(void (*visit)(BinTreeNode<T>* p)) { inOrder(root, visit); }                                                            //中序递归遍历
    void preOrder(void (*visit)(BinTreeNode<T>* p)) { preOrder(root, visit); }                                                          //前序递归
    void postOrder(void (*visit)(BinTreeNode<T>* p)) { postOrder(root, visit); }                                                        //后序递归
    void levelOrder(void (*visit)(BinTreeNode<T>* p));                                                                                  //使用队列的层次遍历
    int size() const { return size(root); }                                                                                             //使用后序递归遍历求节点个数
    int height() const { return height(root); }                                                                                         //使用后序递归遍历求二叉树的高度
   protected:
    BinTreeNode<T>* root;
    char RefValue;                                                                   //数据输入停止标志
    void destroy(BinTreeNode<T>* subTree);                                           //递归删除二叉树节点，后序遍历删除
    BinTreeNode<T>* copy(const BinTreeNode<T>* orignode);                            //copy构造;前序
    BinTreeNode<T>* parent(BinTreeNode<T>* subTree, BinTreeNode<T>* current) const;  //返回父节点
    void traverse(BinTreeNode<T>* subTree, ostream& out) const;                      //按前序方式遍历输出每个节点的值
    void createBinTree(istream& in, BinTreeNode<T>*& subTree);                       //采用广义表表示的二叉树创建方法
    void inOrder(BinTreeNode<T>* subTree, void (*visit)(BinTreeNode<T>* p));         //中序遍历
    void preOrder(BinTreeNode<T>* subTree, void (*visit)(BinTreeNode<T>* p));        //前序遍历
    void postOrder(BinTreeNode<T>* subTree, void (*visit)(BinTreeNode<T>* p));       //后序遍历
    int size(BinTreeNode<T>* subTree) const;                                         //使用后序递归遍历求节点个数
    int height(BinTreeNode<T>* subTree) const;                                       //使用后序递归遍历求二叉树的高度
    friend ostream& operator<<<T>(ostream& out, const BinaryTree<T>& rhs);           //add <T> 前序输出二叉树
    friend istream& operator>><T>(istream& in, BinaryTree<T>& rhs);                  //add <T> 采用广义表表示方式创建二叉树
};

template <class T>
void BinaryTree<T>::destroy(BinTreeNode<T>* subTree) {
    if (subTree != NULL) {
        destroy(subTree->leftChild);
        destroy(subTree->rightChild);
        delete subTree;
    }
}

template <class T>
BinTreeNode<T>* BinaryTree<T>::parent(BinTreeNode<T>* subTree, BinTreeNode<T>* current) const {
    if (subTree == NULL)
        return NULL;
    if (subTree->leftChild == current || subTree->rightChild == current)
        return subTree;

    BinTreeNode<T>* p;
    if ((p = parent(subTree->leftChild, current)) != NULL)
        return p else return parent(subTree->rightChild, current);
}

template <class T>
void BinaryTree<T>::traverse(BinTreeNode<T>* subTree, ostream& out) const {
    if (subTree != NULL) {
        out << subTree->data << " ";
        traverse(subTree->leftChild, cout);
        traverse(subTree->rightChild, out);
    }
}

template <class T>
void BinaryTree<T>::createBinTree(istream& in, BinTreeNode<T>*& subTree) {
    stack<BinTreeNode<T>*> s;
    subTree = NULL;
    BinTreeNode<T>*p, *t;
    unsigned int k;
    T ch;
    in >> ch;  //虽然是模板类，但是目前只支持字符型，不然会报错
    while (ch != RefValue) {
        switch (ch) {
            case '(':
                s.push(p);
                k = 1;
                break;
            case ')':
                s.pop();
                break;
            case ',':
                k = 2;
                break;
            default:
                p = new BinTreeNode<T>(ch);
                if (subTree == NULL)
                    subTree = p;
                else if (k == 1) {
                    t = s.top();
                    t->leftChild = p;
                } else {
                    t = s.top();
                    t->rightChild = p;
                }
        }
        in >> ch;
    }
}

template <class T>
ostream& operator<<(ostream& out, const BinaryTree<T>& rhs) {
    rhs.traverse(rhs.root, out);
    out << endl;
    return out;
}
template <class T>
istream& operator>>(istream& in, BinaryTree<T>& rhs) {
    rhs.createBinTree(in, rhs.root);
    return in;
}
template <class T>
void BinaryTree<T>::inOrder(BinTreeNode<T>* subTree, void (*visit)(BinTreeNode<T>* p)) {
    if (subTree != NULL) {
        inOrder(subTree->leftChild, visit);
        visit(subTree);
        inOrder(subTree->rightChild, visit);
    }
}

template <class T>
void BinaryTree<T>::preOrder(BinTreeNode<T>* subTree, void (*visit)(BinTreeNode<T>* p)) {
    if (subTree != NULL) {
        visit(subTree);
        inOrder(subTree->leftChild, visit);
        inOrder(subTree->rightChild, visit);
    }
}

template <class T>
void BinaryTree<T>::postOrder(BinTreeNode<T>* subTree, void (*visit)(BinTreeNode<T>* p)) {
    if (subTree != NULL) {
        inOrder(subTree->leftChild, visit);
        inOrder(subTree->rightChild, visit);
        visit(subTree);
    }
}

template <class T>
int BinaryTree<T>::size(BinTreeNode<T>* subTree) const {
    if (subTree == NULL)
        return 0;
    else
        return 1 + size(subTree->leftChild) + size(subTree->rightChild);
}

template <class T>
int BinaryTree<T>::height(BinTreeNode<T>* subTree) const {
    if (subTree == NULL)
        return 0;
    else {
        int i = height(subTree->leftChild);
        int j = height(subTree->rightChild);
        return (i > j) ? i + 1 : j + 1;
    }
}

template <class T>
BinTreeNode<T>* BinaryTree<T>::copy(const BinTreeNode<T>* orignode) {
    if (orignode == NULL)
        return NULL;
    BinTreeNode<T>* temp = new BinTreeNode<T>;
    temp->data = orignode->data;
    temp->leftChild = copy(orignode->leftChild);
    temp->rightChild = copy(orignode->rightChild);
    return temp;
}

template <class T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& rhs) {
    this->destroy(this->root);
    this->root = copy(rhs.root);
    return *this;
}

template <class T>
void BinaryTree<T>::levelOrder(void (*visit)(BinTreeNode<T>* p)) {
    deque<BinTreeNode<T>*> dq;
    BinTreeNode<T>* p = root;
    dq.push_back(p);
    while (!dq.empty()) {
        p = dq.front();
        visit(p);
        dq.pop_front();

        if (p->leftChild != NULL)
            dq.push_back(p->leftChild);
        if (p->rightChild != NULL)
            dq.push_back(p->rightChild);
    }
}
