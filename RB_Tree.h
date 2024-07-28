#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// #define DEBUG

// 声明颜色枚举变量：包含RED和BLACK两种
enum COLOR
{   
    RED, BLACK
};

// RB_Tree树结构体
struct RB_Tree 
{
    // 树的根结点
    struct RB_TreeNode* root;
    // 树上所有叶子结点的左右子结点和根结点的父结点都指向这个空结点
    struct RB_TreeNode* nilPtr;
    // 树的结点个数
    int size;
};

// 声明RB_Tree树结点结构体
// 一棵红黑树结点应该包含以下信息
/**
 * @param color 代表这个结点当前的颜色
 * @param val 代表这个结点当前的值
 * @param parent 代表这个结点当前的父结点
 * @param left 代表这个结点当前的左子结点
 * @param right 代表这个结点当前的右子结点
 */
struct RB_TreeNode
{
    enum COLOR color;
    int val;
    struct RB_TreeNode* parent;
    struct RB_TreeNode* left;
    struct RB_TreeNode* right;
};

// 一个全局的"空结点"对象，所有叶子结点都指向这个结点
// 一个知识盲点：加深一下对于全局变量的概念理解
//          全局变量本身就是存储在全局/静态数据区的变量，这一点和变量本身是常规数据类型还是结构体类型并无关联
//          而C语言本身对于静态/全局数据的初始化就是在编译时进行的，这时编译器并不会对赋值语句中的变量名/动态内存分配操作进行解析
//          而是会直接跳过，这样的话整个数据就是未初始化的了，运行时运行器也不会再去管这个全局变量，因此程序会出现未定义的问题，因此C语言要求对于静态/全局变量的初始化必须使用编译器可以解析的常量值
#ifdef DEBUG
const struct RB_TreeNode nilPtr = {BLACK, 0, NULL, NULL, NULL}; 
const struct RB_TreeNode test;
#else

// 初始化一棵红黑树的函数，返回值为初始化好了的红黑树的树结构体指针
void RB_TreeInit(struct RB_Tree* rb_tree);
// 向红黑树中插入val对应的结点
bool RB_insert(struct RB_Tree* rb_tree, struct RB_TreeNode* z);
// 从红黑树中删除val对应的结点
bool RB_delete(struct RB_Tree* rb_tree, struct RB_TreeNode* z);
// 在红黑树中搜索值为val的结点
struct RB_TreeNode* RB_search(struct RB_Tree* rb_tree, int val);
// 清空红黑树
void RB_destroy(struct RB_Tree* rb_tree);
// 把v移植到u的位置
void RB_transplant(struct RB_Tree* rb_tree, struct RB_TreeNode* u, struct RB_TreeNode* v);
// 红黑树的插入修复函数
void RB_insert_fixup(struct RB_Tree* rb_tree, struct RB_TreeNode* z);
// 红黑树的删除修复函数
void RB_delete_fixup(struct RB_Tree* rb_tree, struct RB_TreeNode* x);
// 右旋函数
void RB_right_rotate(struct RB_Tree* rb_tree, struct RB_TreeNode* y);
// 左旋函数
void RB_left_rotate(struct RB_Tree* rb_tree, struct RB_TreeNode* x);
// 找出node为根的子树中最小值所在的结点
struct RB_TreeNode* RB_tree_minimum(struct RB_Tree* rb_tree, struct RB_TreeNode* node);
// 修改红黑树中值为old_val的结点修改为new_val
struct RB_TreeNode* RB_modify(struct RB_Tree* rb_tree, int old_val, int new_val);
// 可视化整棵树(用横板实现)
void RB_visualize(struct RB_Tree* rb_tree, struct RB_TreeNode* root, unsigned int depth);
// 打印树中的某个结点
void RB_printNode(struct RB_TreeNode* node, unsigned int depth);

#endif