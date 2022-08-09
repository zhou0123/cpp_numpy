
#include <stdarg.h>
#include <immintrin.h>
template <class T>
int len(T &array)
{
    return  sizeof(array)/(array[0]);
}


class  array
{
private:
    int *shape;
    int num{0};//元素个数
    float *nums;//储存元素
    int len_shape;//shape的len
    float dim_x ();
    float* dim_0();
public:
     array(int dim,...);
    ~ array();

    void construct(...);
    float sum(int dim =-1);
    int len();

};
int array::len()
{
    return len_shape;
}
 array:: array(int dim,...)
{
    shape = new int(dim);
    len_shape =dim;
    va_list ap;
    va_start(ap, dim);

    for (int i=0;i<dim;i++)
    {
        shape[i] = va_arg(ap,int);
        num +=va_arg(ap,int);
    }
}
void array::construct(...)
{
    nums = new float(num);
    va_list ap;
    va_start(ap, num);

    for (int i=0;i<num;i++)
    {
        nums[i] = va_arg(ap,float);
    }
}
float array::dim_x()
{
     float result =0;
        if (num >4)
        {
            __m128 res = _mm_set_ps1(0.f);
            __m128 temp;
            float *res_ptr;
            
            for (int i=0;i<num;i+=4)
            {
                temp =_mm_load_ps(nums+i);
                res = _mm_add_ps(res,temp);
            }
            _mm_store1_ps(res_ptr,res);

            for (int i=0;i<4;i++)
            {
                result += res[i];
            }

        }
        for (int i=(num/4)*4;i<num;i++)result += nums[i];
        return result;
}
float* array::dim_0()
{
    float * result = new float[shape[1]]();
   
    for (int j=0;j<shape[1];j+=4)
    {
        __m128 res = _mm_set_ps1(0.f);
        __m128 temp = _mm_set_ps1(0.f);
        for (int i=0;i<shape[0]-1;i++)
        {
            _mm_prefetch(nums+4*j+shape[1]*(i+1),_MM_HINT_ET0);
            temp = _mm_load_ps(nums+4*j+shape[1]*i);
            res = _mm_add_ps(res,temp);
        }
        temp = _mm_load_ps(nums+4*j+shape[1]*(shape[0]-1));
        res  = _mm_add_ps(res,temp);
        _mm_stream_ps(result+4*j,res);
    }
    
    for (int i=0;i<shape[0]-1;i++)
    {
        for (int j=(shape[1]/4)*4;j<shape[1];j++)
        {
            _mm_prefetch(nums+j+shape[1]*(i+1),_MM_HINT_ET0);
        }
        
    }
    
}
float array::sum(int dim =-1)
{
    if (dim =-1)
    {
         return dim_x();
    }

    else if (dim =0)
    {
        if (len_shape ==1) dim_x();

    }
    
}
 array::~ array()
{
}

