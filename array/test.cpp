/* --sum.cpp-- 可变参数宏实现求任意个整形值得和 */
#include <stdarg.h>
#include<iostream>
int sum(int count, ...);   

int sum(int count, ...){    
    va_list ap;
    va_start(ap, count);

    int sum = 0;  
    for(int i = 0; i < count; i++)          
        sum += va_arg(ap, int); 

    va_end(ap);         
    return sum;
}

int main()
{
    int res = (sum(3,1,2,3));
    std::cout<<res<<std::endl;

    return 0;

}