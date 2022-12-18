#include <iostream>
#include <algorithm>
using namespace std;

template <typename T1>
class myMatrix
{
private:
    int N;
    int M;
    T1 **matrix;

public:
    myMatrix(int row, int column)
    {
        N = row;
        M = column;
        matrix = new T1*[N];
        for(int i=0; i<N; ++i)
        {
            *(matrix+i) = new T1[M];
        }

        cout<<"A null matrix is created."<<endl;
    }
    
    myMatrix(const myMatrix& src)
    {
        cout<<"Copy constructor creating deep copy."<<endl;
        N = src.N;
        M = src.M;
        matrix = new T1*[N];
        for(int i=0; i<N; ++i)
        {
            *(matrix+i) = new T1[M];
        }
        copy(*src.matrix, *(src.matrix+N-1)+M-1, *matrix);
    }

    ~myMatrix()
    {   
        for(int i=0; i<N; ++i)
        {
            delete [] matrix[i];
        }
        delete[] matrix;

        cout<<"The matrix has been deleted."<<endl;
    }

    void inputMatrixValue()
    {   
        for(int i=0; i<N; ++i)
            for(int j=0; j<M; ++j)
            {
                cin>>(*(*(matrix+i)+j));
            }
    }

    void outputMatrixValue()
    {   
         for(int i=0; i<N; ++i)
         {
            for(int j=0; j<M; ++j)
            {
                cout<<(*(*(matrix+i)+j))<<" ";
            }
            cout<<endl;
         }
            
    }

};

int main()
{
    //myMatrix<int>    tmpMatrix(2, 2);
    //myMatrix<double> tmpMatrix(2, 2);
    myMatrix<char>     tmpMatrix(2, 2);
    tmpMatrix.inputMatrixValue();
    tmpMatrix.outputMatrixValue();

}

