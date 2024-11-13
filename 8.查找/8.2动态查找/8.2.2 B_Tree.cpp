//
// Created by ElegyNine on 24-11-7.
//


#include<stdio.h>
#include<stdlib.h>

#define t 3

typedef int Ty;
typedef struct BTreeNode {
    int n;          //当前关键字数量
    Ty* keys;       //关键字数组
    BTreeNode** child;  //孩子指针数组
    bool leaf;
}node,*BTree;

node* BTreeSearch(node* u,Ty val) {
    int i = 0;
    //遍历该节点的键
    while(i < u->n && val > u->keys[i]) {
        i++;
    }
    //如果该节点有这个关键字则返回该节点
    if(i < u->n && val == u-> keys[i]) {
        return u;
    }
    //如果在叶子节点中无法找到关键字，则关键字val不在这个B树中，返回NULL。
    if(u->leaf) {
        return NULL;
    }
    //其他情况则搜索该节点相应的子树
    return BTreeSearch(u->child[i],val);
}


void splitChild(BTreeNode* tar,int i,BTreeNode * y) {
    //分裂tar节点，y为tar节点的一个孩子

    //创建一个节点。
    BTreeNode* p = (BTreeNode*)malloc(sizeof BTreeNode);
    p->leaf = y->leaf;
    p->n = t - 1;
    //复制最后 t-1 个 y 的关键字给 p
    for(int j = 0;j < t - 1;j++) {
        p->keys[j] = y->keys[j + t];
    }
    if(y->leaf == false)
        //复制最后t个y的孩子给p
        for(int j = 0;j < t;j++) {
            p->child[j] = y->child[j + t];
        }
    //减少y节点的关键字数量
    y->n = t - 1;
    for(int j = tar->n;j >= i + 1;j--) {
        //在中间为孩子移出一个新位置
        tar->child[j + 1] = tar->child[j];
    }
    //将创建的 p 插入移出的新位置
    tar->child[i + 1] = p;
    for(int j = tar->n - 1;j >= i;j--) {
        //在中间移出一个空位
        tar->keys[j + 1] = tar->keys[j];
    }
    //将y中间的关键字给tar节点
    tar->keys[i] = y->keys[t - 1];
    tar->n ++;
}

//将val关键字插入节点中
void insertNonFull(BTreeNode*p ,int val) {
    int i = p->n - 1;
    if(p->leaf) {
        //如果是叶子节点
        //移出一个key可以插入的位置
        while(i >= 0 && p->keys[i] > val) {
            p->keys[i + 1] = p->keys[i];
            i--;
        }
        //将key插入p节点中
        p->keys[i + 1] = val;
        p->n++;
    }
    else {
        //如果不是叶子节点

        //找一个可以插入val关键字的孩子
        while(i >= 0 && p->keys[i] > val) {
            i--;
        }

        if(p->child[i + 1]->n == 2 * t - 1) {
            //如果这个节点满了，则分裂这个节点
            splitChild(p,i + 1,p->child[i + 1]);

            //分裂完后，chlid被分为两部分，查看哪一部分可以插入val关键字
            if(p->keys[i + 1] < val) {
                i++;
            }
        }
        insertNonFull(p->child[i + 1],val);
    }
}



void insert(BTree root,Ty val) {
    if(root == NULL) {
        //如果是空树，则创建节点
        root = (BTreeNode*)malloc(sizeof BTreeNode);
        root->leaf = true;
        root->keys[0] = val;
        root->n = 1;
    }
    else {
        if(root -> n == 2 * t - 1) {
            //如果根节点满了，则增加树高

            //创建一个节点
            BTreeNode* p = (BTreeNode*)malloc(sizeof BTreeNode);
            p->leaf = false;
            p->child[0] = root;
            splitChild(p,0,root);
            int i = 0;
            if(p->keys[0] < val)i++;
            insertNonFull(p->child[i],val);
            root = p;
        }
        else {
            //如果节点没有满，则将val关键字插入root节点
            insertNonFull(root,val);
        }


    }
}

