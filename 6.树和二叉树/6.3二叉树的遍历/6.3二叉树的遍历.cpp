//
// Created by leo on 24-11-7.
//

#include<iostream>
#include<queue>

typedef int Ty;

struct node {
    Ty data;
    node* lchild;
    node* rchild;
};

//先序遍历  根->左->右
void preorder(node* u) {
    if(u == nullptr)return;
    std::cout << u->data << '\n';
    preorder(u->lchild);
    preorder(u->rchild);
}

//中序遍历  左->根->右
void inorder(node* u) {
    if(u == nullptr)return;
    inorder(u->lchild);
    std::cout << u->data << '\n';
    inorder(u->rchild);
}

//后序遍历  左->右->根
void postorder(node* u) {
    if(u == nullptr)return;
    postorder(u->lchild);
    postorder(u->rchild);
    std::cout << u->data << '\n';
}

//层序遍历
void levelorder(node* u) {
    std :: queue<node*> q;
    q.push(u);
    while(!q.empty()) {
        node* cur = q.front();q.pop();
        if(cur == nullptr)continue;
        std :: cout << cur->data;
        q.push(cur->lchild);
        q.push(cur->rchild);
    }
}

