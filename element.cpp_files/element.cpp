#include "element.h"
#include "mkl.h"

#define OMP_NUM_THREADS = 240
#define AVX_SIZE = 512
#define NUM_DOUBLES = AVX_SIZE/sizeof(double)
#define NUM_BLOCKS = OMP_NUM_THREADS/NUM_DOUBLES


class element {

     int N, M;
      double* array;
    public:
        void element(int N_, int M_)
        {
            N = N_; M= M_;
        array = new double[N*M];
        }
        
        void element~()
        {
            delete array; 
    }

        element operator+=(const double* c)
        {
            #pragma omp parallel
            for (int i=0;i<NUM_BLOCKS;i++)
             for (int j=0;j<BLOCK_SIZE;j++)
               this[i*BLOCK_SIZE + j]+=c[i*BLOCK_SIZE+j]}

    element operator+=(element& el)
    {
      /* BLAS for adding matrices */
    }

    element operator*=(element& el)
    {
        
        /* call MKL_CBLAS_DGEMM(..,A,..B ) - see dgemm_driver.c for how to call dgemm, A*B = A:     this.my_row_major_array, B = el.my_row_major_array */
     return 
    }
    
    element operator[][]()
       /* see example matrix class on web /*

};

// objective: create a programming abstraction using OOP which hides the details of calling blas routines
// performance: trade off between performance and convenience of simple 
void main(int argc, int* argv){
    
    element A = new element();
    element B = new element()
    element C = A*=B;    
}