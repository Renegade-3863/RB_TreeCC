# RB_TreeCC
### 一个用纯C语言实现的红黑树(包含可视化方法)
### README文档后续会找时间完善，本人也不能保证一次就完全弄懂红黑树的插入删除操作

### 编译测试方法很简单
#### 终端使用
``` shell
gcc RB_Test.cc -O0 -g -fsanitize=undefined,address,leak -o RB_Test
```
#### 命令进行编译后直接执行即可
```
./RB_Test
```

函数内部各参数(RB_Test.c文件中)可以根据需要自行修改相关信息，原函数创建的结点个数为30个随机值