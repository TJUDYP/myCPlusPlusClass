#include <iostream>
#include <algorithm>
using namespace std;

class myMatrix
{
private:
    int N;
    int M;
    int **matrix;

public:
    myMatrix(int row, int column)
    {
        N = row;
        M = column;
        matrix = new int*[N];
        for(int i=0; i<N; ++i)
        {
            *(matrix+i) = new int[M];
        }

        cout<<"A null matrix is created."<<endl;
    }
    
    myMatrix(const myMatrix& src)
    {
        cout<<"Copy constructor creating deep copy."<<endl;
        N = src.N;
        M = src.M;
        matrix = new int*[N];
        for(int i=0; i<N; ++i)
        {
            *(matrix+i) = new int[M];
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

void copymyMatrix(myMatrix mm)
{
    cout<<"Copied the matrix."<<endl;
}

int main()
{
    myMatrix tmpMatrix(2, 2);
    tmpMatrix.inputMatrixValue();
    tmpMatrix.outputMatrixValue();

    copymyMatrix(tmpMatrix);
}

