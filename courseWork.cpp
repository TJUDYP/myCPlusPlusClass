#include <iostream>
#include <string>
#include <fstream>
using namespace std;


// =======================================================================
// =======================================================================
// Base and Derived Class
// =======================================================================
// =======================================================================
class Person
{
    protected:
        string name;
        char sex;
        int age;
        long int ID_number;

    public:
        Person():name("n"),sex('n'),age(0),ID_number(0){};
        Person(string p_name, char p_sex, int p_age, long int p_ID_number):\
               name(p_name),sex(p_sex),age(p_age),ID_number(p_ID_number){};
        
        virtual ~Person(){};

        virtual void displayData()=0;

        virtual string getName()=0;

        virtual void fileWriting()=0;

};

class UnderGraduate: public Person
{
    private:
        int scores;

    public:
        UnderGraduate():Person("n", 'n', 0, 0), scores(0) {};
        UnderGraduate(string p_name, char p_sex, int p_age, long int p_ID_number, int p_scores):\
               Person(p_name, p_sex, p_age, p_ID_number), scores(p_scores) {};
        ~UnderGraduate(){};

        void displayData()
        {
            cout<<name<<" "<<sex<<" "<<age<<" "<<ID_number<<" "<<scores<<endl;
        }

        string getName()
        {
           return this->name; 
        }

        void fileWriting()
        {
            ofstream myFile;
            myFile.open("studentFile.bin", ios_base::app | ios_base::binary);  //use binary file here for the following write and read function

            if(myFile.is_open())
            {
                cout<<"File Writing: studentFile.bin open successfully."<<endl;

                myFile.write((char*) this, sizeof(*this));
                myFile.close();

                cout<<"Finieshed writing to studentFile.bin, will close now."<<endl;

            }
        }

};

class Teacher: public Person
{
    private:
        int salary;

    public:
        Teacher():Person("0", '0', 0, 0), salary(0) {};
        Teacher(string p_name, char p_sex, int p_age, long int p_ID_number, int p_salary):\
               Person(p_name, p_sex, p_age, p_ID_number), salary(p_salary) {};
        ~Teacher(){};
        
        void displayData()
        {
            cout<<name<<" "<<sex<<" "<<age<<" "<<ID_number<<" "<<" "<<salary<<endl;
        }

        string getName()
        {
           return this->name; 
        }

        void fileWriting()
        {
            ofstream myFile;
            myFile.open("teacherFile.bin", ios_base::app | ios_base::binary);  //use binary file here for the following write and read function

            if(myFile.is_open())
            {
                cout<<"File Writing: teacherFile.bin open successfully."<<endl;

                myFile.write((char*) this, sizeof(*this));
                myFile.close();

                cout<<"Finieshed writing to teacherFile.bin, will close now."<<endl;

            }
        }

};

class Graduate: public Person
{
    private:
        long int student_number;
        string college_major;
        int salary;

    public:
        Graduate():Person("n", 'n', 0, 0), student_number(0), college_major(" "), salary(0) {};
        Graduate(string p_name, char p_sex, int p_age, long int p_ID_number, long int p_sn, string p_cm, int p_s):\
               Person(p_name, p_sex, p_age, p_ID_number), student_number(p_sn), college_major(p_cm), salary(p_s) {};
        ~Graduate(){};

        void displayData()
        {
            cout<<name<<" "<<sex<<" "<<age<<" "<<ID_number<<" "<<student_number<<" "<<college_major<<" "<<salary<<endl;
        }

        string getName()
        {
           return this->name; 
        }

        void fileWriting()
        {
            ofstream myFile;
            myFile.open("graduateFile.bin", ios_base::app | ios_base::binary);

            if(myFile.is_open())
            {
                cout<<"File Writing: graduateFile.bin open successfully."<<endl;

                myFile.write((char*) this, sizeof(*this));
                myFile.close();

                cout<<"Finieshed writing to graduateFile.bin, will close now."<<endl;

            }
        }

};


// =======================================================================
// =======================================================================
// Node and LinkedList
// =======================================================================
// =======================================================================
template<typename T1> class LinkedList;

template<typename T1>
class Node
{   
    private:
        friend class LinkedList<T1>;
        T1 *data;  //use pointer here to prevent instantiation, because of the pure virtual function in class Person
        Node<T1>* next;
       
    public:  
        Node(T1* d):data(d), next(NULL){};
};

template<typename T1>
class LinkedList
{
    private:
        Node<T1>* head;
        Node<T1>* tail;

    public:
        LinkedList(): head(NULL), tail(NULL) {};
        ~LinkedList(){};
        
        void append(T1* append_node);
        void print();
        bool find(string f_name);
        void delete_data(string d_name);
        void allFileReading();
        void allFileWriting();

};

template<typename T1>
void LinkedList<T1>::append(T1* append_node)
{

    Node<T1>* newnode = new Node<T1>(append_node);

    if(head==NULL)
    {
        head = newnode;
        tail = newnode;
    }
    else
    {
        tail->next = newnode;
        tail = newnode;
    }

}; 

template <typename T1>
void LinkedList<T1>::print()
{
    if(head==NULL)
    {
        cout<<"The list is empty!"<<endl;
    }
    else
    {   
        cout<<"--------------------------"<<endl;
        cout<<"all the data in the list now: "<<endl;
        for(Node<T1>* tmp = head; tmp!= NULL; tmp=tmp->next)
        {
            tmp->data->displayData();
        }
    }
}

template <typename T1>
bool LinkedList<T1>::find(string f_name)
{
    
    for(Node<T1>* tmp = head; tmp!= NULL; tmp=tmp->next)
    {
        if (tmp->data->getName() == f_name)
        {
            cout<<"The List contains: "<<f_name<<endl;
            return true;      
        }
    }

    cout<<"The List doesn't contains: "<<f_name<<endl;
    return false;
}

template <typename T1>
void LinkedList<T1>::delete_data(string d_name)
{
    if(this->find(d_name))
    {   
        Node<T1>* delete_node_pre = NULL;
        Node<T1>* delete_node = head;

        while((delete_node != NULL) & (delete_node->data->getName() != d_name))
        {
            delete_node_pre = delete_node;
            delete_node = delete_node->next;
        }

        if(delete_node==head)
        {
            head = head->next;
        }
        else
        {
            delete_node_pre->next = delete_node->next;   
        }
        
        cout<<"deleted the data of: "<<d_name<<endl;
    }

}


template <typename T1>
void LinkedList<T1>::allFileWriting()
{
    ofstream myFile;
    myFile.open("studentFile.bin", ios_base::out);
    myFile.close();
    myFile.open("teacherFIle.bin", ios_base::out);
    myFile.close();
    
    for(Node<T1>* tmp = head; tmp!= NULL; tmp=tmp->next)
        {
            tmp->data->fileWriting();;
        }
}

template <typename T1>
void LinkedList<T1>::allFileReading()
{
    cout<<"--------------------------"<<endl;
    cout<<"reading all the binary file into LinkedList."<<endl;

    ifstream myFile;

    // ==================================================
    // Undergraduate
    // get the rows of data.
    int rows_data(0);
    myFile.open("studentFile.bin", ios_base::in | ios_base::binary);
    if(myFile.is_open())
    {
        UnderGraduate u;
        while(myFile.read((char*) &u, sizeof(u)))
        {
            rows_data += 1;
        } 
        myFile.close();
    }
    cout<<"rows_data(Undergraduate): "<<rows_data<<endl;
    
    UnderGraduate* u_tmp = new UnderGraduate[rows_data];
    myFile.open("studentFile.bin", ios_base::in | ios_base::binary);
    if(myFile.is_open())
    {
        cout<<"File Reading: studentFile.txt open successfully. It contains:"<<endl;

        UnderGraduate u;
        int count(0);
        while(myFile.read((char*) &u, sizeof(u)))
        {        
            u.displayData();

            //myList.append(&u); //this can lead to instantiate a Derived as a Base Class, ridicilous.
            //UnderGraduate u_tmp(u);
            //myList.append(&u_tmp);
            u_tmp[count] = u;
            this->append(&(u_tmp[count]));
            count += 1;     

        }

        cout<<"Finished reading studentFile.txt, will close now."<<endl;
        myFile.close();
    } 

    // ==================================================
    // Teacher
    rows_data = 0;
    myFile.open("teacherFile.bin", ios_base::in | ios_base::binary);
    if(myFile.is_open())
    {
        Teacher t;
        while(myFile.read((char*) &t, sizeof(t)))
        {
            rows_data += 1;
        } 
        myFile.close();
    }
    cout<<"rows_data(Teacher): "<<rows_data<<endl;
    
    Teacher* t_tmp = new Teacher[rows_data];
    myFile.open("teacherFile.bin", ios_base::in | ios_base::binary);
    if(myFile.is_open())
    {
        cout<<"File Reading: teacherFile.txt open successfully. It contains:"<<endl;
        Teacher t;
        int count(0);
        while(myFile.read((char*) &t, sizeof(t)))
        {        
            t.displayData();
            t_tmp[count] = t;
            this->append(&(t_tmp[count]));
            count += 1;     
        }
        cout<<"Finished reading teacherFile.txt, will close now."<<endl;
        myFile.close();
    } 

    // ==================================================
    // Graduate
    rows_data = 0;
    myFile.open("graduateFile.bin", ios_base::in | ios_base::binary);
    if(myFile.is_open())
    {
        Graduate g;
        while(myFile.read((char*) &g, sizeof(g)))
        {
            rows_data += 1;
        } 
        myFile.close();
    }
    cout<<"rows_data(Graduate): "<<rows_data<<endl;
    
    Graduate* g_tmp = new Graduate[rows_data];
    myFile.open("graduateFile.bin", ios_base::in | ios_base::binary);
    if(myFile.is_open())
    {
        cout<<"File Reading: graduateFile.txt open successfully. It contains:"<<endl;
        Graduate g;
        int count(0);
        while(myFile.read((char*) &g, sizeof(g)))
        {        
            g.displayData();
            g_tmp[count] = g;
            this->append(&(g_tmp[count]));
            count += 1;     
        }
        cout<<"Finished reading graduateFile.txt, will close now."<<endl;
        myFile.close();
    } 

    cout<<"--------------------------"<<endl;
    cout<<"finished reading all the binary file into LinkedList."<<endl;
}



// =======================================================================
// =======================================================================
// main function
// =======================================================================
// =======================================================================
int main()
{
    //UnderGraduate u1("dyp", 'm', 22, 430424199912093814, 650);
    //UnderGraduate u2("ddyypp", 'm', 23, 430424199812093814, 660);
    //u1.displayData();
    //u1.fileWriting();
    //u1.fileReading();
    
    //u2.fileWriting();
    
    //Teacher t1("ypd", 'f', 32, 430424198912093814, 65000);
    //Teacher t2("DiPeng", 'm', 20, 430424200010013231, 185000);
    //t1.fileWriting();
    //t1.fileReading();
    //t1.displayData();

    //Graduate g1("Kevin", 'm', 42, 421876197804091273, 22112006, "Computer", 1200);
    //g1.fileWriting();

    LinkedList<Person> myList;
    myList.allFileReading();
    //myList.append(&u2);
    //myList.append(&u2);
    //myList.append(&t1);
    //myList.append(&t2);
    //myList.allFileWriting(); 
    //myList.print();
   
    myList.print();
    myList.delete_data("DiPeng");
    myList.print();
    //myList.allFileWriting();

    //myList.allFileReading();
    //allFileReadToList(&myList);
    //myList.append(&u2);
    //myList.print();

    //UnderGraduate u3;
    //u3.fileReading();
    
    //UnderGraduate u;

    //LinkedList<Person> myList;
}
