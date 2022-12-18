#include <iostream>
#include <algorithm>    // to use copy
#include <cstdlib>      // to use exit
using namespace std;

template<typename T1>
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


    myMatrix operator + (const myMatrix& addMatrix)
    {   
        if((this->N == addMatrix.N) && (this->M == addMatrix.M))
        {
            myMatrix resultMatrix(this->N, this->M);
            for(int i=0; i< this->N; ++i)
            {
                for(int j=0; j< this->M; ++j)
                {
                   //*(*(resultMatrix.matrix+i)+j) = *(*(matrix+i)+j) + *(*(addMatrix.matrix+i)+j);
                    resultMatrix.matrix[i][j] = matrix[i][j] + addMatrix.matrix[i][j];
                }
            }
            cout<<"finished + operation."<<endl;
            return resultMatrix;
        }
        else
        {
            cout<<"dimensions not equal, can't do + operation."<<endl;
            exit(0);
        }
    }


    myMatrix operator * (const myMatrix& multiplyMatrix)
    {
        if(this->M == multiplyMatrix.N)
        {
            myMatrix resultMatrix(this->N, multiplyMatrix.M);
            for(int i=0; i<this->N; ++i)
            {
                for(int j=0; j< multiplyMatrix.M; ++j)
                {
                    resultMatrix.matrix[i][j] = 0;
                    for(int k=0; k<this->M; ++k)
                    {
                        resultMatrix.matrix[i][j] += matrix[i][k]*multiplyMatrix.matrix[k][j];
                    } 
                }
            }
            cout<<"finished * operation."<<endl;
            return resultMatrix;
        }
        else
        {
            cout<<"doesn't satisfy the * operation's requirement."<<endl;
            exit(0);
        }
    }


    myMatrix& operator = (const myMatrix& equalMatrix)
    {
        if(this != &equalMatrix)
        {
            for(int i=0; i<this->N; ++i) delete [] matrix[i];
            delete []matrix;

            this->N = equalMatrix.N;
            this->M = equalMatrix.M;

            matrix = new T1* [this->N];
            for(int i=0; i<this->N; ++i)
            {
                *(matrix+i) = new T1[this->M];
            }

            for(int i=0; i<this->N; ++i)
            {
                for(int j=0; j< this->M; ++j)
                {
                    matrix[i][j] = equalMatrix.matrix[i][j];
                }
            }

            cout<<"finished = operation."<<endl;
            return *this;
        }
        else
        {
            cout<<"equal itself is meaningless."<<endl;
            exit(0);
        }
    }


    myMatrix operator <<(const myMatrix& insertData)
    {
        cout<<"choose to insert in rows or columns."<<endl;
        cout<<"1 in rows, 2 in columns, please cin your number:"<<endl;
        int chooseNumber;
        cin>>chooseNumber;

        if(chooseNumber == 1) //insert in rows
        {
            cout<<"which line of rows do you want to insert?"<<endl;
            int insertLine;
            cin>>insertLine;

            myMatrix resultMatrix(this->N+insertData.N, this->M);
            for(int i=0; i< resultMatrix.N; ++i)
            {
                for(int j=0; j<resultMatrix.M; ++j)
                {
                    if((i >= insertLine) && ( i < (insertLine+insertData.N)))
                    {
                        resultMatrix.matrix[i][j] = insertData.matrix[i-insertLine][j];
                    }
                    else if(i < insertLine)
                    {
                        resultMatrix.matrix[i][j] = matrix[i][j];
                    }
                    else
                    {
                        resultMatrix.matrix[i][j] = matrix[i-insertData.N][j];
                    }
                }
            }
            return resultMatrix;
        }
        else if(chooseNumber ==2) //insert in columns
        {
            cout<<"which line of columns do you want to insert?"<<endl;
            int insertLine;
            cin>>insertLine;

            myMatrix resultMatrix(this->N, this->M+insertData.M);
            for(int j=0; j<resultMatrix.M; ++j)
            {
                for(int i=0; i< resultMatrix.N; ++i)
                {
                    if((j >= insertLine) && ( j < (insertLine+insertData.M)))
                    {
                        resultMatrix.matrix[i][j] = insertData.matrix[i][j-insertLine];
                    }
                    else if(j < insertLine)
                    {
                        resultMatrix.matrix[i][j] = matrix[i][j];
                    }
                    else
                    {
                        resultMatrix.matrix[i][j] = matrix[i][j-insertData.M];
                    }
                }
            }
            return resultMatrix;
        }
        else
        {
            cout<<"number is invalid."<<endl;
            exit(0);
        }
    }

    myMatrix operator >>(const int& getLine)
    {
        cout<<"choose get data in rows or columns."<<endl;
        cout<<"1 in rows, 2 in columns, please cin your number:"<<endl;
        int chooseNumber;
        cin>>chooseNumber;

        if(chooseNumber == 1)
        {   
            myMatrix resultMatrix(1, this->M);
            for (int i=0; i < this->M; ++i) 
            {
                resultMatrix.matrix[0][i] = matrix[getLine][i];
            }
            return resultMatrix;
        }
        else if(chooseNumber == 2)
        {
            myMatrix resultMatrix(this->N, 1);
            for (int i=0; i < this->N; ++i) 
            {
                resultMatrix.matrix[i][0] = matrix[i][getLine];
            }
            return resultMatrix;
        }
        else
        {
            cout<<"number is invalid."<<endl;
            exit(0);
        }
    }

    int& operator()(const int& i, const int& j)
    {
        return matrix[i][j];
    }

};

void useCopyFunc(myMatrix<int> tmpMatrix)
{
    cout<<"using the copy constructor."<<endl;
}

int main()
{
    //myMatrix<int>    originMatrix(2, 2);
    myMatrix<double> originMatrix(2, 1);
    originMatrix.inputMatrixValue();
    originMatrix.outputMatrixValue();

    myMatrix<double> testMatrix(2, 1);
    testMatrix.inputMatrixValue();
    testMatrix.outputMatrixValue();

    myMatrix<double> resultMatrix(originMatrix + testMatrix);  //how did () allocate resultMatrix?
    //myMatrix resultMatrix(originMatrix * testMatrix);
    //myMatrix resultMatrix(originMatrix<<testMatrix);
    //myMatrix resultMatrix(originMatrix>>2);
    resultMatrix.outputMatrixValue();
    
/*     myMatrix<int> testMatrix(1,1);
    testMatrix.inputMatrixValue();
    testMatrix.outputMatrixValue();

    useCopyFunc(originMatrix); */

    //cout<<originMatrix(1,1)<<endl;

}

