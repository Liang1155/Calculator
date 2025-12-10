#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include"./LinkedStack.h"
//注意，上面的#include"LinkedStack.h"改成#include"Stack.h"功能不变
#include<math.h>


#define DOUBLE_SIZE 8
//double 类型一个字符占8个字节
#define CHAR_SIZE 1
//char 类型一个字符占1个字节
#define MAX_EXPRESSION_LENGTH 1000
//输入的字符串的长度的最大值为100

int OpPriority(char op);
//该函数用于定义运算符的优先级，op是传入的运算符
void CalculateNeighborNums(Stack* numStack,Stack* opStack);
//该函数用于计算两个数字加减乘除的结果，只能计算两个数字！
void Welcome();
//这个函数用于开头的欢迎，无实际用途
double CalculateExpression(char s[MAX_EXPRESSION_LENGTH]);
//这个函数用于计算给的表达式，一次计算一个表达式