#include "RB_Tree.cc"
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
// #define DEBUG

int main(int argc, char* argv[])
{
    // 创建一棵红黑树
    struct RB_Tree* rb_tree = (struct RB_Tree*)malloc(sizeof(struct RB_Tree));
    // 初始化空结点
    rb_tree->nilPtr = (struct RB_TreeNode*)malloc(sizeof(struct RB_TreeNode));
    rb_tree->nilPtr->color = BLACK;
    RB_TreeInit(rb_tree);
    printf("------ Beginning of Insertion ------\n\n");
    // 向树中插入结点
    // 尝试插入10个
    struct RB_TreeNode** newNodes;
    // 临时数组记录一下这10个值
    int memo[30];
    newNodes = (struct RB_TreeNode**)malloc(sizeof(struct RB_TreeNode*)*30);
    for(int i = 0; i < 30; ++i)
    {
        newNodes[i] = (struct RB_TreeNode*)malloc(sizeof(struct RB_TreeNode));
    }
    int i = 0, t = 0;
    
    while(i < 30)
    {
        // 设置随机数种子值
        srand(time(0));
        // 把结点的值设定成一个随机值
        newNodes[i]->val = rand() % 1000;
#ifdef DEBUG
        printf("Random number generated is: %d\n", newNodes[i]->val);
#endif
        // 记录
        memo[i] = newNodes[i]->val;
        bool same = false;
        for(int j = 0; j < i; ++j)
        {
            if(memo[i] == newNodes[j]->val)
            {
                same = true;
                break;
            }
        }
        if(same)
            continue;
        // 进行插入即可
        RB_insert(rb_tree, newNodes[i]);
        // 睡眠1秒钟以使得设置的随机数种子有差异
        sleep(1);
        printf("@ Time %d, trying to insert: %d\n", ++t, newNodes[i]->val);
        ++i;
    }
    printf("\n\n------ End of Insertion ------\n\n");
    printf("The Tree created is: \n");
    RB_visualize(rb_tree, rb_tree->root, 0);
    printf("\n\n");
    printf("------ Beginning of Modification ------\n\n");
#ifdef DEBUG
    printf("The insertion array is: \n");
    for(int i = 0; i < 10; ++i)
    {
        printf("%d, ", memo[i]);
    }
    printf("\n");
#endif
    // 进行一些删改操作
    // 尝试删改4次
    // 修改第5次添加的结点的值
    newNodes[4] = RB_modify(rb_tree, newNodes[4]->val, newNodes[5]->val+3);
    // 尝试修改根结点的值
    printf("newNodes[4] successfully modified\n");
    struct RB_TreeNode* tmp = rb_tree->root;
    int idx = -1;
    for(int i = 0; i < 30; ++i)
    {
        if(newNodes[i] == tmp)
        {
            idx = i;
            break;
        }
    }
#ifdef DEBUG
    printf("idx is: %d\n", idx);
#endif
    tmp = RB_modify(rb_tree, rb_tree->root->val, rb_tree->root->val+7);   
    newNodes[idx] = tmp;
#ifdef DEBUG
    printf("rb_tree->root val after modification is: %d\n", rb_tree->root->val);
#endif
    // 修改第1、10次添加的结点的值
    printf("root successfully modified\n");
    newNodes[0] = RB_modify(rb_tree, newNodes[0]->val, newNodes[0]->val * newNodes[1]->val);
    printf("newNodes[0] successfully modified\n");
    newNodes[9] = RB_modify(rb_tree, newNodes[9]->val, newNodes[9]->val - newNodes[3]->val);
    printf("newNodes[9] successfully modified\n");

    printf("\n\n------ End of Modification ------\n\n");
    printf("The Tree after modification is: \n");
    RB_visualize(rb_tree, rb_tree->root, 0);
    printf("\n\n");
    printf("Trying to destroy the whole tree\n");
    // 再尝试把树删掉
    // printf("Trying to destroy the tree\n");
    RB_destroy(rb_tree);
    free(rb_tree->nilPtr);
    free(rb_tree);
    rb_tree = NULL;
    free(newNodes);
    assert(rb_tree == NULL);
    return 0;
}
