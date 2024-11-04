//
// Created by leo on 24-11-4.
//
#include<stdlib.h>

typedef int Ty;

struct node {
	Ty key;             //数据
	int factor;         //平衡因子
	node* lson, *rson;
};

node* root;             //根节点

template<class Ty>
Ty max(Ty a, Ty b) {
    return a > b ? a : b;
}

//获取节点高度
int height(node* p){
    if (p == nullptr)return 0;
    return p->factor;
}

//更新节点高度
void updateHeight(node* p) {
    p->factor = max(height(p->lson), height(p->rson)) + 1;
}

//获取平衡因子
int balanceFactor(node* p) {
    if (p == nullptr) {
        return 0;
    }
    return height(p->lson) - height(p->rson);
}

//创建一个节点
node* initNode(Ty val) {
    node* p = new node;
    p->key = val;
    p->factor = 1;
    p->lson = nullptr;
    p->rson = nullptr;
    return p;
}

//左旋转
node* lrotate(node* p) {
    // clang-format off
    //     |                       |
    //     N                       S
    //    / \     l-rotate(N)     / \
    //   L   S    ==========>    N   R
    //      / \                 / \
    //     M   R               L   M
    node* child = p->rson;
    node* grandchild = child->lson;
    child->lson = p;
    p->rson = grandchild;
    updateHeight(p);
    updateHeight(child);
    return child;
}

//右旋转
node* rrotate(node* p) {
    // clang-format off
    //       |                   |
    //       N                   S
    //      / \   r-rotate(N)   / \
    //     S   R  ==========>  L   N
    //    / \                     / \
    //   L   M                   M   R
    node* child = p->lson;
    node* grandchild = child->rson;
    child->rson = p;
    p->lson = grandchild;
    updateHeight(p);
    updateHeight(child);
    return child;
}

//旋转的判断
node* rotate(node* p) {
    //获取节点的平衡因子
    int _bf = balanceFactor(p);

    //左边失衡
    if (_bf > 1) {
        if (balanceFactor(p->lson) >= 0) {
            //RR 型旋转
            return rrotate(p);
        }
        else {
            //LR 型旋转
            p->lson = lrotate(p->lson);
            return rrotate(p);
        }
    }

    //右边失衡
    if (_bf < -1) {
        if (balanceFactor(p->rson) <= 0) {
            //LL 型旋转
            return lrotate(p);
        }
        else {
            //RL 型旋转
            p->rson = rrotate(p->rson);
            return lrotate(p);
        }
    }
    return p;
}

//插入操作实现
node* insert_imp(node* p, Ty val) {
    if (p == nullptr) {
        return initNode(val);
    }

    //遍历二叉树，在二叉树中查找到相应的位置
    //若插入元素已存在，则不做插入操作
    if (val < p->key) {
        p->lson = insert_imp(p->lson, val);
    }
    else if (val > p->key) {
        p->rson = insert_imp(p->rson, val);
    }
    else return p;
    updateHeight(p);
    p = rotate(p);
    return p;
}

//删除操作实现
node* remove_imp(node* p, Ty val) {
    if (p == nullptr) {
        return nullptr;
    }
    if (val < p->key) {
        p->lson = remove_imp(p->lson, val);
    }
    else if (val > p->key) {
        p->rson = remove_imp(p->rson, val);
    }
    else {
        if (p->lson == nullptr || p->rson == nullptr) {
            node* child = p->lson != nullptr ? p->lson : p->rson;
            if (child == nullptr) {
                //被删除节点左右子树均为空
                delete p;
                return nullptr;
            }
            else {
                //被删除节点有一个孩子
                delete p;
                p = child;
            }
        }
        else {
            //被删除节点左右孩子均不为空。
            //找到右子树中最小的节点（中续后继节点），替换当前节点
            //原因：当前节点右子树中值最小的节点既大于当前节点左子树中的所有节点，也小于当前节点右子树中所有节点（当前除了选中的这个最小值节点）
            node* tmp = p->rson;
            while (tmp->lson != nullptr) {
                tmp = tmp->lson;
            }
            int key = tmp->key;
            p->rson = remove_imp(p->rson, tmp->key);
            p->key = key;
        }
    }
    updateHeight(p);
    p = rotate(p);
    return p;
}


//查找操作实现
//与插入删除差不多
node* find_imp(node* p, Ty val) {
    if (p == nullptr) {
        return nullptr;
    }

    if (val < p->key) {
        p->lson = insert_imp(p->lson, val);
    }
    else if (val > p->key) {
        p->rson = insert_imp(p->rson, val);
    }
    else return p;
}

void insert(Ty val) {
    root = insert_imp(root, val);
}

void remove(Ty val) {
    root = remove_imp(root, val);
}

node* find(Ty val) {
    return find_imp(root, val);
}


