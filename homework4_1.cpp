#include <iostream>
#include <algorithm>
#include <fstream>
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

    void fileWriting()
    {
        ofstream myFile;
        myFile.open("HelloFile.txt", ios_base::out);

        if(myFile.is_open())
        {
            cout<<"File Writing: File open successfully."<<endl;

             for(int i=0; i<N; ++i)
             {
                for(int j=0; j<M; ++j)
                {
                    myFile<<(*(*(matrix+i)+j))<<" ";
                }
                myFile<<endl;
             }

            cout<<"Finieshed writing to file, will close now."<<endl;

            myFile.close();
        }
    }

    void fileReading()
    {
        ifstream myFile;
        myFile.open("HelloFile.txt", ios_base::in);

        if(myFile.is_open())
        {
            cout<<"File Reading: File open successfully. It contains:"<<endl;

            string fileContents;
            while(myFile.good())
            {
                getline(myFile, fileContents);
                cout<<fileContents<<endl;
            }

            cout<<"Finished reading file, will close now."<<endl;
            myFile.close();
        }
        else
        {
            throw "open() failed: check if file exist or not.";
        }
    }

};

int main()
{
    myMatrix<int>    tmpMatrix(2, 2);
    //myMatrix<double> tmpMatrix(2, 2);
    //myMatrix<char>     tmpMatrix(2, 2);
    tmpMatrix.inputMatrixValue();
    tmpMatrix.outputMatrixValue(); 
    
    //tmpMatrix.fileWriting();
/*     try
    {
        tmpMatrix.fileReading();
    }
    catch(const char* exp)
    {
        cout<<"Exception: "<<exp<<endl;
    } */
        
}

