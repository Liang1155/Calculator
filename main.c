#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include"./stack.h"
#include<math.h>


#define DOUBLE_SIZE 8
//double 类型一个字符占8个字节
#define CHAR_SIZE 1
//char 类型一个字符占1个字节
#define MAX_EXPRESSION_LENGTH 100
//输入的字符串的长度的最大值为100
#define PI 3.1415926
#define e 2.718281828
int OpPriority(char op);
//该函数用于定义运算符的优先级，op是传入的运算符
void cal(Stack* numStack,Stack* opStack);
//该函数用于计算两个数字加减乘除的结果，只能计算两个数字！
void Welcome();
//这个函数用于开头的欢迎，无实际用途


int OpPriority(char op){
    switch(op){

        case '(':return 0;
        //括号的优先级为0
        case ')':return 0;
        //括号的优先级为0
        case '+':return 1;
        //加法的优先级为1
        case '-':return 1;
        //减法的优先级为1
        case '*':return 2;
        //乘法的优先级为2
        case '/':return 2;
        //除法的优先级为2
        case 's':return 3;
        //sin的优先级为3
        case 'c':return 3;
        //cos的优先级为3
        case 't':return 3;
        //tan的优先级为3
        case '^':return 4;
        //乘方的优先级为4
        default :return -1;
        //遇到非法字符变成-1
    }
}


void cal(Stack* numStack,Stack* opStack){
    //numStack是数字栈，opStack是运算符栈
    char op;
    StackPeek(opStack,&op);
    //从符号栈顶取出一个符号op
    StackPop(opStack);
    //从符号栈顶弹出一个符号op
    if(isalpha(op)){
        double num;
        StackPeek(numStack,&num);
        //取出栈顶数字，作为三角函数计算的底数
        StackPop(numStack);
        //弹出这个数字
        double exeNum;
        //该数字用于储存经过三角函数变化后的数字
        switch(op){
            case 's':exeNum=sin(num);break;//sin
            case 'c':exeNum=cos(num);break;//cos
            case 't':exeNum=tan(num);break;//tan
        }
        StackPush(numStack,&exeNum);
        //将经过三角函数变化后的数字再还回numStack中去
    }
    else{
        //如果不是三角函数相关的，而只是普通加减乘除，则回到这里
        double num2;
        StackPeek(numStack,&num2);
        //从数字栈顶取出一个数字，存储在num2
        StackPop(numStack);
        //从数字栈顶弹出这个数字

        double num1;
        StackPeek(numStack,&num1);
        //从数字栈顶取出一个数字，存储在num1
        StackPop(numStack);
        //从数字栈顶弹出这个数字


        if(op=='+'){
            double result=(num1+num2);
            StackPush(numStack,&result);
            //符号是加号，两个数字相加，并入栈
        }
        else if(op=='-'){
            double result=num1-num2;
            StackPush(numStack,&result);
            //符号是减号，两个数字相减，并入栈
        }
        else if(op=='*'){
            double result=(num1)*(num2);
            StackPush(numStack,&result);
            //符号是乘号，两个数字相乘，并入栈
        }
        else if(op=='/'){
            double result=(num1)/(num2);
            StackPush(numStack,&result);
            //符号是除号，两个数字相除，并入栈
        }
        else if(op=='^'){
            double result=pow(num1,num2);
            StackPush(numStack,&result);
            //符号是乘方，则为两个数的pow
        }

    }
}


void Welcome(){
    printf("欢迎使用梁宸滔的计算器!\n");
    printf("本计算器支持加减乘除,三角函数,乘方计算,并且可以通过括号改变计算顺序\n");
    printf("请输入表达式:\n");
}

int main(){
    Stack opStack;    
    //声明运算符栈opStack
    Stack numStack;   
    //声明数字栈numStack

    #if DEBUG
    printf("\n栈创建成功");
    #endif
    //调试模式
    StackInit(&opStack,CHAR_SIZE);
    //初始化符号栈,并定义符号栈中每个元素占1个字节(char类型)
    StackInit(&numStack,DOUBLE_SIZE);
    //初始化数字栈，并定义数字栈中每个元素占8个字节(double类型)

    #if DEBUG
    printf("\n栈初始化成功\n");
    #endif

    char s[MAX_EXPRESSION_LENGTH];
    //声明一个字符串，也就是输入的表达式，长度为MAX_EXPRESSION_LENGTH
    Welcome();
    //欢迎函数
    scanf("%s",s);
    //获取输入的字符串


    for(int i=0;i<(int)(strlen(s));i++){
        //遍历整个字符串
        if(isdigit(s[i])||(s[i]=='.' && i+1<(int)(strlen(s))&&isdigit(s[i+1]))){
            //如果当前字符是数字或者小数点，并且下一个字符也是数字
            int digitIndex=i;
            //定义一个digitIndex，从i开始遍历整个数字部分
            double parsedNum=0;
            //parsedNum用于存储整个数字，也就是把小数点后面和前面的全部存起来变成一个double数字，比如12.3
            int hasDecimal=0;
            //hasDecimal变量用于存储是否包含小数点
            double Decimal=0.1;
            //小数点后有几位就乘以几位的0.1

            while(digitIndex<(int)(strlen(s))&&(isdigit(s[digitIndex])||s[digitIndex]=='.')){
                if(s[digitIndex]=='.'){
                    hasDecimal=1;
                    //遇到小数点，标记有小数点
                    digitIndex++;
                    //进入下一位
                }

                else{
                    if(hasDecimal){
                        parsedNum+=(s[digitIndex]-'0')*Decimal;
                        //遇到小数点后，每个数字都要乘以相应的倍数
                        Decimal*=0.1;
                        //每一位数乘以的倍数是前一位数字的0.1倍
                    }
                    else{
                        parsedNum=parsedNum*10+(s[digitIndex]-'0');
                        //如果没有小数点，就是前面的数字乘以10加上后面的数字
                    }
                    digitIndex++;
                    //进入下一位
                }
            }
            #if DEBUG
            printf("\n现在到第%d位(防止while死循环)",digitIndex);
            #endif
            //调试模式看此处while是否正常运行


            StackPush(&numStack,&parsedNum);
            //将转化后的数字入栈
            i=digitIndex-1;
            //回到当前是数字而下一位是符号的那个地方

            #if DEBUG
            printf("\n此处i的值是%d,digitIndex的值是%d,这两个相差1",i,digitIndex);
            #endif
            //调试模式看此处是否正常
        }

        else if(i>=1&&s[i]=='-'&&s[i-1]=='('){
            //如果出现负号，并且是符号前面是左括号的情况
            double zero=0;
            StackPush(&numStack,&zero);
            //在符号前面加上0，变成0-x，然后把0入栈
            StackPush(&opStack,&s[i]);
            //接下来符号入栈

            
        }

        else if(s[i]=='-'&&i==0){
            //如果出现负号，并且负号前面没有东西，是第一个字符
            double zero=0;
            StackPush(&numStack,&zero);
            //在符号前面加上0，变成0-x,然后把0入栈
            StackPush(&opStack,&s[i]);
            //接下来符号入栈
        }

        else if(s[i]=='('){
            //出现左括号，直接入栈
            StackPush(&opStack,&s[i]);
        }


        else if(s[i]==')'){
            //出现右括号，先去匹配左括号
            char elem;
            //用于遍历右括号前面的符号
            StackPeek(&opStack,&elem);
            while(elem!='('){
                cal(&numStack,&opStack);
                //当没有遇到右括号，就需计算两个括号中间的数字
                StackPeek(&opStack,&elem);
                //更新elem
                }
                StackPop(&opStack);
                //遇到了右括号，将右括号出栈

        }

        else if(isalpha(s[i])){
            //用于检测是否出现三角函数，因为三角函数都是字母
            int alphaIndex = i;
            // 读取连续的字母（函数名）
        while(alphaIndex<(int)strlen(s)&&isalpha(s[alphaIndex])){
            alphaIndex++;
        }
        char trigonometricFunctions[4];
        //三角函数
        strncpy(trigonometricFunctions,s+i,alphaIndex-i);
        trigonometricFunctions[alphaIndex-i]='\0';
        //添加结束符

        #if DEBUG
        printf("\n此处的三角函数字符串是%s",trigonometricFunctions);
        #endif
        //调试模式看此处trigonometricFunction是否正确复制了三角函数

        char op;
        //用于加入到opStack中
        if (strcmp(trigonometricFunctions, "sin") == 0) {
            op='s';
            //识别到sin，在opStack中加入s
        }
        else if (strcmp(trigonometricFunctions, "cos") == 0) {
            op='c';
            //识别到cos，在opStack中加入c
        }
        else if (strcmp(trigonometricFunctions, "tan") == 0) {
            op='t';
            //识别到tan，在opStack中加入t
        }
        StackPush(&opStack,&op);
        i=alphaIndex-1;
        #if DEBUG
        printf("\n此处的op是%c,i是%d",op,i);
        #endif
        //调试模式看此处的op是否正确，i是否回到数字位
        }


        else{
            //遇到运算符的情况
            char topElem;
            //用于获取符号栈栈顶元素
            StackPeek(&opStack,&topElem);
            while(!StackIsEmpty(&opStack)&&(topElem)!='('&&OpPriority(topElem)>OpPriority(s[i])){
                //如果当前的符号优先级低于符号栈栈顶的优先级，那么需要先计算栈顶的符号
                StackPeek(&opStack,&topElem);
                cal(&numStack,&opStack);//计算
            }
            StackPush(&opStack,&s[i]);
            //然后当前符号入栈
        }
    }
    while(!StackIsEmpty(&opStack)){
        cal(&numStack,&opStack);
        //如果最后栈不为空，那么计算剩下的元素
    }
    double result;
    //这个是最终的结果
    StackPeek(&numStack,&result);
    //最终数字栈内只有一个数字，这个数字就是最终结果
    printf("\nThe result is %lf,thanks!",result);
    //输出最终结果
    StackFree(&opStack);
    //释放op栈内存
    StackFree(&numStack);
    //释放num栈内存
    
    #if DEBUG
    printf("\nStackFree is done!");
    #endif
    //调试模式看此处是否释放了栈内存

    return 0;
}