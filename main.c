#include"./body.h"

int main(){
    Welcome();
    //欢迎函数

    char inputFile[MAX_EXPRESSION_LENGTH];
    //inputFile是表达式文件
    char outputFile[MAX_EXPRESSION_LENGTH];
    //outputFile是输出结果的文件


    printf("输入表达式文件");
    scanf("%s",inputFile);
    //获得表达式文件
    printf("输入输出文件");
    scanf("%s",outputFile);
    //获得输出结果的文件
    FILE* fin=fopen(inputFile,"r");
    //fin就是输入表达式的文件，用read模式打开
    FILE* fout=fopen(outputFile,"w");
    //fout就是输出结果的文件，用write模式打开

    if(fin==NULL){
    perror("文件打开失败");
    return 1;
    }


    char expression[MAX_EXPRESSION_LENGTH];
    //expression为单个的表达式
    while (fgets(expression,MAX_EXPRESSION_LENGTH,fin)!=NULL) {
    //处理换行符：去除字符串末尾的'\n'或'\r'
    expression[strcspn(expression, "\n\r")] = '\0';

    if(strlen(expression)==0){
        continue;
    }
    //跳过空行
    
    double result=CalculateExpression(expression);
    // 计算表达式结果

    fprintf(fout, "%s =%lf\n",expression,result);
    //写入结果到输出文件(格式:表达式=结果)
    printf("已处理 %s=%lf\n",expression,result);
    //显示目前计算的表达式是哪一个，结果是多少
    }

    fclose(fin);
    fclose(fout);
    //释放资源
    printf("批量计算完成，结果已写入到%s\n", outputFile);
    return 0;
}