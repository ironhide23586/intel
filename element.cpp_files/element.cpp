//#include "element.h"
#include "mkl.h"
#include <iostream>

#define OMP_NUM_THREADS 256
#define AVX_SIZE 512
#define NUM_DOUBLES AVX_SIZE/sizeof(double)
#define NUM_BLOCKS OMP_NUM_THREADS/NUM_DOUBLES


class element
{
    int M, N;
    double *arr;

    public:

        element(int M_, int N_)
        {
            init(M_, N_);
        }

        element(int M_, int N_, double *inp)
        {
            init(M_, N_);
            int idx;
            #pragma omp parallel
            for (int i = 0; i < M_; i++)
            {
                for (int j = 0; j < N_; j++)
                {
                    idx = i * N_ + j;
                    arr[idx] = *(inp + idx);
                }
            }
        }

        ~element()
        {
            mkl_free(arr);
        }

        element operator+=(const double *c)
        {
            /*
            #pragma omp parallel
            for (int i = 0; i < NUM_BLOCKS; i++)
                for (int j = 0; j < BLOCK_SIZE; j++)
                    this[i * BLOCK_SIZE + j] += c[i * BLOCK_SIZE + j];
            */
        }

        void print_elems()
        {
            for (int i = 0; i < M; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    std::cout << arr[i * N + j] << "[" << i << "," << j << "], ";
                }
                std::cout << std::endl;
            }
        }

        void init(int M_, int N_)
        {
            M = M_;
            N = N_;
            arr = (double *) mkl_malloc(M_ * N_ * sizeof(double), 64);
        }

        element operator+=(element &el)
        {
            /* BLAS for adding matrices */
            #pragma omp parallel
            for (int i = 0; i < M; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    arr[i * N + j] += el.arr[i * N + j];
                }
            }
        }

        element operator*=(element &el)
        {
            double *tmp = (double *) mkl_malloc(M * el.N * sizeof(double), 64);
            cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, M, el.N, N, 1, arr, N, el.arr, el.N, 0, tmp, el.N);
            mkl_free(arr);
            arr = tmp;
            N = el.N;
        }

};

// objective: create a programming abstraction using OOP which hides the details of calling blas routines
// performance: trade off between performance and convenience of simple
void main(int argc, int* argv)
{
    /*
    double k1[3][3] =
    {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    double k2[3][4] =
    {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    */

    double k1[2][3] =
    {
        {3, 4, 2},
        {9, 2, 6}
    };

    double k2[3][4] =
    {
        {13, 9, 7, 15},
        {8, 7, 4, 6},
        {6, 4, 0, 3}
    };

    element A(2, 3, *k1);

    element B(3, 4, *k2);

    A.print_elems();
    std::cout << std::endl;
    B.print_elems();
    std::cout << std:: endl;
    A *= B;
    A.print_elems();
}
