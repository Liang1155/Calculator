# 创作者：梁宸滔
**本项目为大一上学期期末程序设计与算法基础大作业**  
本项目可以实现**加减乘除四则运算，可以使用左右括号改变计算顺序，可以计算乘方，各种三角函数。计算式可带小数点，精确度为double**  
另外本项目添加了**调试模式**，修改stack.h的DEBUG参数可以调节是否开启DEBUG模式，**1为开启，0为关闭**  
**此外本项目使用的是批量计算**。你需要创建两个txt文件，一个用于提供你的表达式，另一个用于存储结果  
注意，你会被要求提供两个参数，一个是表达式的地址，一个是存储结果的地址  
**此处的地址，在windows版本需要用如下格式，请务必注意！**  
D://desk//Calculator_All_version//Calculator_Version11//expr.txt  
D://desk//Calculator_All_version//Calculator_Version11//resul.txt  
**请注意需要使用//，并且头尾不要添加""**  
## 2025.12.10更新
应老师要求更改成**链表实现栈**的功能，故添加LinkedList,LinkedStack等文件
由于原本的main.c太长，已经拆分出body.c
body.c主要负责进行单个表达式运算，main.c实现读取输入输出文件，并传入body.c中计算，从而实现批量计算
Linux版本随意

