#ifndef STATUS_H  // 头文件保护：防止重复包含
#define STATUS_H

#define C24_VERSION 202311L
#if __STDC_VERSION__ < C24_VERSION
    #define alignas _Alignas
    #define alignof _Alignof
    #define noreturn _Noreturn
    #define nullptr NULL
    typedef enum{false=0,true=1}bool;
#endif

typedef enum {ERROR=0,OK=1} Status;
//定义返回类型，Status，如果失败返回ERROR，成功返回OK
#endif