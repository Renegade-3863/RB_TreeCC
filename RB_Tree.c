#include "RB_Tree.h"

void RB_TreeInit(struct RB_Tree* rb_tree)
{
    // 空树的大小为0
    rb_tree->size = 0;
    // 空树的根节点为nilPtr
    rb_tree->root = rb_tree->nilPtr;
}

// 红黑树的左旋函数
void RB_left_rotate(struct RB_Tree* rb_tree, struct RB_TreeNode* x)
{
    // 记录x的右子结点
    struct RB_TreeNode* y = x->right;
    // 把y的左子树移植到x的右子树上
    x->right = y->left;
    // 如果y的左子树有结点(红黑树中体现为左子树不是对应树的空结点)
    // 就把左子树根结点的父结点设为x
    if(y->left != rb_tree->nilPtr)
    {
        y->left->parent = x;
    }
    // 把y的父结点设为x的父结点
    y->parent = x->parent;
    // 如果x本身就是整棵树的根结点，那么就把树的根结点修改为y
    if(x->parent == rb_tree->nilPtr)
    {
        rb_tree->root = y;
    }
    // 否则如果x是其父结点的左子树，那么就把y设为x父结点的左子树
    else if(x == x->parent->left)
    {
        x->parent->left = y;
    }
    // 否则如果x是其父结点的右子树，那么就把y设为x父结点的右子树
    else
    {
        x->parent->right = y;
    }
    // 把x放到y的左子树位置上
    y->left = x;
    x->parent = y;
}

// 红黑树的右旋函数
void RB_right_rotate(struct RB_Tree* rb_tree, struct RB_TreeNode* y)
{
    // 获取y的左子结点
    struct RB_TreeNode* x = y->left;
    // 先把y的左子树替换为x的右子树
    y->left = x->right;
    // 如果x的右子树不为空，就把该子树根结点的父结点设为y
    if(x->right != rb_tree->nilPtr)
    {
        x->right->parent = y;
    }
    // 把x的父结点设为y的父结点
    x->parent = y->parent;
    // 如果y是根结点，那么要修改树的根结点信息
    if(y->parent == rb_tree->nilPtr)
    {
        rb_tree->root = x;
    }
    // 否则如果y是其父结点的左子树，那么就把x设为y父结点的左子树
    else if(y == y->parent->left)
    {
        x->parent->left = x;
    }
    // 否则如果y是其父结点的右子树，那么就把x设为y父结点的右子树
    else 
    {
        x->parent->right = x;
    }
    // 把y放到x的右子树位置上
    x->right = y;
    y->parent = x;
}

// 向红黑树中插入val对应的结点
bool RB_insert(struct RB_Tree* rb_tree, struct RB_TreeNode* z)
{
    struct RB_TreeNode* y = rb_tree->nilPtr;
    struct RB_TreeNode* x = rb_tree->root;
    while(x != rb_tree->nilPtr)
    {
        y = x;
        if(z->val < x->val)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    z->parent = y;
    if(y == rb_tree->nilPtr)
    {
        rb_tree->root = z;
    } 
    else if(z->val < y->val)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }
    z->left = rb_tree->nilPtr;
    z->right = rb_tree->nilPtr;
    z->color = RED;
    RB_insert_fixup(rb_tree, z);
    // 更新树的大小值
    rb_tree->size += 1;
    return true;
}

/*
    红黑树的五条基本性质
    - 1. 每个结点或是红色的，或是黑色的
    - 2. 根结点是黑色的
    - 3. 每个叶结点(rb_tree->nulPtr)是黑色的
    - 4. 如果一个结点是红色的，则它的两个子结点都是黑色的
    - 5. 对每个结点，从该结点到其所有后代叶结点的简单路径上，均包含相同数目的黑色结点
 */
// 红黑树的插入修复函数
void RB_insert_fixup(struct RB_Tree* rb_tree, struct RB_TreeNode* z)
{
    // 循环不变式
    // 1. 结点z是红结点
    // 2. 如果z.p是根结点，则z.p是黑结点
    // 3. 如果有任何性质被破坏，则至多只有一条被破坏，或是性质2，或是性质4
    
    // 循环的退出条件为：性质4没有被破坏
    while(z->parent->color == RED)
    {
        // 如果z的父结点是z的祖父结点的左孩子
        // 右孩子的情况和左孩子是对称的，代码稍加修改即可
        if(z->parent == z->parent->parent->left)
        {
            // 获取z的父结点的兄弟结点
            struct RB_TreeNode* y = z->parent->parent->right;
            // 情况1：z的叔结点y是红色的
            // 此时把z的父结点和叔结点y都着为黑色
            // 把z的祖父结点着为红色(为了确保性质5成立 -> 如果z的祖父结点不是根结点，那么不修改祖父结点的颜色会导致性质5被破坏)
            // 同时把z设为其原本的祖父结点(祖父结点下面的子树都已经满足了红黑树的五条性质，现在只有祖父结点和它的父结点 (如果存在) 可能会不满足红黑性质)
            // 把z设其原本的祖父结点不会破坏循环不变式的条目1
            // 条目2也成立
            // 条目3同样成立
            // 如果此时性质2被违反了，那么一定是因为z原本的祖父结点就是根结点，此时性质4不会被违反，因为在当前循环已经把这个祖父结点的两个子结点都设为黑色了
            // 如果此时性质4被违反了，那么一定是因为z原本的祖父结点不是根结点，其父结点也是红结点，否则性质4不会被违反，此时这个祖父结点一定不是根结点，也就是说，根结点始终是黑色的(性质2成立)
            if(y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }   
            // 情况2：z的叔结点是黑色的，并且z是一个右孩子
            else if(z == z->parent->right)
            {
                z = z->parent;
                // 左旋
                // 旋转前后，z->parent->parent仍然是同一个结点，其颜色仍然是黑色
                // 同时由于调整的是红色结点，性质5没有被破坏
                // 性质1和3显然不会被破坏
                // 此时z仍然代表了两个连续红结点中靠下的那一个结点，性质4仍然是被破坏的
                // 性质2不可能被破坏，因为修改不涉及根结点
                RB_left_rotate(rb_tree, z);
            }
            // 情况3：z的叔结点是黑色的，并且z是一个左孩子
            else
            {
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                RB_right_rotate(rb_tree, z->parent->parent);
            }
        }
        // 否则，如果z的父结点是z的祖父结点的右孩子
        else
        {
            struct RB_TreeNode* y = z->parent->parent->left;
            if(y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }   
            else if(z == z->parent->left)
            {
                z = z->parent;
                RB_right_rotate(rb_tree, z);
            }
            else
            {
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                RB_left_rotate(rb_tree, z->parent->parent);
            }
        }
    }
    // 因为退出条件是性质4得到了满足，那么唯一仍然可能被破坏的就只有性质2，这里做一次保证
    // 维护性质2
    rb_tree->root->color = BLACK;
}

// 从红黑树中删除结点z
bool RB_delete(struct RB_Tree* rb_tree, struct RB_TreeNode* z)
{
    // 如果z是哨兵结点，直接返回false
    if(z == rb_tree->nilPtr)
        return false;
    // y代表需要被删除或者移动的结点
    struct RB_TreeNode* y = z;
    struct RB_TreeNode* x = NULL;
    enum COLOR y_oiginal_color = y->color;
    if(z->left == rb_tree->nilPtr)
    {
        x = z->right;
        RB_transplant(rb_tree, z, z->right);
    }
    else if(z->right == rb_tree->nilPtr)
    {
        x = z->left;
        RB_transplant(rb_tree, z, z->left);
    }
    else
    {
        y = RB_tree_minimum(rb_tree, z->right);
        y_oiginal_color = y->color;
        x = y->right;
        if(y->parent == z)
        {
            x->parent = y;
        }
        else
        {
            RB_transplant(rb_tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        RB_transplant(rb_tree, z, y);
        y->left = z->left;
        z->left->parent = y;
        y->color = z->color;
    }
    if(y_oiginal_color == BLACK)
    {
        RB_delete_fixup(rb_tree, x);
    }
    // 别忘了把给z动态分配的内存删除
    free(z);
    // 更新树的大小值
    rb_tree->size -= 1;
    return true;
}

void RB_delete_fixup(struct RB_Tree* rb_tree, struct RB_TreeNode* x)
{
    // 如果x不是根结点并且是一个黑黑结点，就要持续旋转或者染色操作以努力把x变成根节点或者红黑结点
    while(x != rb_tree->root && x->color == BLACK)
    {   
        // 如果x是其父结点的左子结点
        if(x == x->parent->left)
        {
            // w指向x的兄弟结点
            struct RB_TreeNode* w = x->parent->right;
            // 情况1：
            // x的兄弟结点为红色
            // 此时要想办法把x的兄弟结点变成黑色，以保证最终能把x变成根结点或者红黑结点
            // 从情况1要转换成情况2、3或者4
            if(w->color == RED)
            {
                // 因为w本身是红色的，那么其左右子结点一定都是黑色的
                // 此时可以通过对x->parent进行左旋把w左孩子这个黑结点挪成x的兄弟结点
                // 可是单纯进行这种旋转会导致多转进来一个黑结点，导致性质5在算上黑黑结点x后不再被满足
                // 故要维护性质5，可以把转进来的黑结点变成红色，把大根处的红色结点变成黑色，此时性质5仍然被满足
                w->color = BLACK;
                x->parent->color = RED;
                RB_left_rotate(rb_tree, x->parent);
                w = x->parent->right;
            }
            // 情况2:
            // x的兄弟结点为黑色，并且其两个子结点都是黑色的
            // 此时很简单，因为x的父结点到x的路径比到w的路径少一个黑结点，那么把w变成红色的就是一种向最终正确性的逼近
            // 变换后，从x->parent结点到其任何叶子结点的简单路径上的黑结点个数就都相同了
            // 但是，因为不能明确x->parent本身是不是根结点，或者它的颜色是红色还是黑色，因而还需要后续判定
            if(w->left->color == BLACK && w->right->color == BLACK)
            {
                // 把w变成红色
                w->color = RED;
                // x指针上移一层
                x = x->parent;
            }
            // 情况3：
            // w是黑色的，并且w的左孩子是红色的，w的右孩子是黑色的
            // 此时想尝试把情况3转换成情况4
            // 因为情况4可以通过染色和旋转操作把x的额外黑色属性去掉
            // 此时想办法把w的右孩子变成红色即可
            // 办法即右旋
            // 同时还应维持在x有双重黑色属性的条件下，性质5成立
            // 依据这个条件进行颜色的修改
            else if(w->right->color == BLACK)
            {
                w->color = RED;
                w->left->color = BLACK;
                RB_right_rotate(rb_tree, w);
                w = x->parent->right;
            }
            // 情况4：
            // w是黑色的，并且w的右孩子是红色的
            // 此时可以通过染色和旋转操作把x多出来的黑色属性去掉
            // 就是从w所在的子树中"转"一个黑结点过去(通过左旋可以实现)
            // 同时还要注意确保在x 不具备 多重黑属性条件下性质5的成立
            else
            {
                w->color = x->parent->color;
                w->right->color = BLACK;
                x->parent->color = BLACK;
                RB_left_rotate(rb_tree, x->parent);
                x = rb_tree->root;
            }
        }
        // 否则，x是其父结点的右子结点
        else
        {
            // w指向x的兄弟结点
            struct RB_TreeNode* w = x->parent->left;
            if(w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                RB_right_rotate(rb_tree, x->parent);
                w = x->parent->left;
            }
            if(w->right->color == BLACK && w->left->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else if(w->left->color == BLACK)
            {
                w->color = RED;
                w->right->color = BLACK;
                RB_left_rotate(rb_tree, w);
                w = x->parent->left;
            }
            else
            {
                w->color = x->parent->color;
                w->left->color = BLACK;
                x->parent->color = BLACK;
                RB_right_rotate(rb_tree, x->parent);
                x = rb_tree->root;
            }
        }
    }
    x->color = BLACK;
}

// 把v移植到u的位置，不对v的子结点做相应处理
void RB_transplant(struct RB_Tree* rb_tree, struct RB_TreeNode* u, struct RB_TreeNode* v)
{
    // 如果u本身就是根结点，那么就把树的根结点设为v
    if(u->parent == rb_tree->nilPtr)
    {
        rb_tree->root = v;
    }
    else if(u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }
    // 无论v是否是叶结点，都对其父结点指针进行修改
    v->parent = u->parent;
}

// 找出node为根的子树中最小值所在的结点
struct RB_TreeNode* RB_tree_minimum(struct RB_Tree* rb_tree, struct RB_TreeNode* node)
{
    // 不断地向左探查
    while(node->left != rb_tree->nilPtr)
    {
        node = node->left;
    }
    return node;
}

// 在红黑树中搜索值为val的结点
// 和正常的BST搜索结点相同的流程
struct RB_TreeNode* RB_search(struct RB_Tree* rb_tree, int value)
{
    struct RB_TreeNode* cur = rb_tree->root;
    while(cur != rb_tree->nilPtr)
    {
        // 当前结点值大于val，说明val只可能存在于cur的左子树中，向左探查
        if(cur->val > value)
        {
            cur = cur->left;
        }
        // 找到了就返回对应结点给调用者
        else if(cur->val == value)
        {
            return cur;
        }
        // 否则向右探查
        else
        {
            cur = cur->right;
        }
#ifdef DEBUG
        printf("cur->val: %d\n", cur->val);
#endif
    }
#ifdef DEBUG
    printf("Not found!\n");
#endif
    // 没找到，返回rb_tree->nilPtr
    return rb_tree->nilPtr;
}

// 清空红黑树
// 就是持续调用RB_delete函数不断删除根结点，直到树的根结点为rb_tree->nilPtr为止
void RB_destroy(struct RB_Tree* rb_tree)
{
    while(rb_tree->root != rb_tree->nilPtr)
    {
        printf("Destroying node with value: %d\n", rb_tree->root->val);
        RB_delete(rb_tree, rb_tree->root);
    }
}

// 修改红黑树中值为old_val的结点修改为new_val
/**
 * @return bool值，代表是否修改成功
 */
struct RB_TreeNode* RB_modify(struct RB_Tree* rb_tree, int old_val, int new_val)
{
#ifdef DEBUG
    printf("The val to be modified is: %d\n", old_val);
#endif
    // 先通过RB_search函数找到要修改的结点指针，如果找不到，就返回false
    struct RB_TreeNode* target = RB_search(rb_tree, old_val);
    // 没找到，返回哨兵结点即可
    if(target == rb_tree->nilPtr)
    {
        return rb_tree->nilPtr;
    }
    // cout << "The val to be modified is: " << target->val;
    // 找到了就直接进行修改即可
    // 先从树中删除这个结点，再插入一个有新值的结点
    RB_delete(rb_tree, target);
    target = (struct RB_TreeNode*)malloc(sizeof(struct RB_TreeNode));
    target->val = new_val;
#ifdef DEBUG
    printf("The val to be added is: %d\n", target->val);
#endif
    RB_insert(rb_tree, target);
    // 返回新指针代表修改成功
    return target;
}

// 可视化整棵树(用横板实现)
void RB_visualize(struct RB_Tree* rb_tree, struct RB_TreeNode* root, unsigned int depth = 0)
{
    // 本质其实就是进行一个中序遍历，把每个遍历到的结点按深度进行打印即可
    if(root != rb_tree->nilPtr)
    {
        RB_visualize(rb_tree, root->left, depth+1);
        RB_printNode(root, depth);
        RB_visualize(rb_tree, root->right, depth+1);
    }
}

// 打印树中的某个结点，depth为该结点在树中的深度(规定根结点的深度为0)
void RB_printNode(struct RB_TreeNode* node, unsigned int depth)
{
    for(int i = 0; i < depth; ++i)
    {
        printf("\t\t");
    }
    // 打印数值+换行即可
    printf("%d\n", node->val);
}