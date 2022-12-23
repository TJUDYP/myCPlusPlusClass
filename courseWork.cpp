#include <iostream>
#include <string>
using namespace std;

class Person
{
    protected:
        string name;
        char sex;
        int age;
        long int ID_number;

    public:
        Person(string p_name, char p_sex, int p_age, long int p_ID_number):\
               name(p_name),sex(p_sex),age(p_age),ID_number(p_ID_number){};
        
        virtual ~Person(){};

        virtual void displayData()=0;

};

class UnderGraduate: public Person
{
    private:
        int scores;

    public:
        UnderGraduate(string p_name, char p_sex, int p_age, long int p_ID_number, int p_scores):\
               Person(p_name, p_sex, p_age, p_ID_number), scores(p_scores) {};
        ~UnderGraduate(){};

        void displayData()
        {
            cout<<name<<endl;
            cout<<sex<<endl;
            cout<<age<<endl;
            cout<<ID_number<<endl;
            cout<<scores<<endl;
        }

};

class Teacher: public Person
{
    private:
        double salary;

    public:
        Teacher(string p_name, char p_sex, int p_age, long int p_ID_number, double p_salary):\
               Person(p_name, p_sex, p_age, p_ID_number), salary(p_salary) {};
        ~Teacher(){};
        
        void displayData()
        {
            cout<<name<<endl;
            cout<<sex<<endl;
            cout<<age<<endl;
            cout<<ID_number<<endl;
            cout<<salary<<endl;
        }

};

template<typename T1> class LinkedList;

template<typename T1>
class Node
{
    private:
        friend class LinkedList<T1>;
        T1 *data;  //using pointer here to escape instantiation, because of the pure virtual function in class Person
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
        
        //void build();
        void append(T1* append_node);
        void print();

};

template<typename T1>
void LinkedList<T1>::append(T1* append_node)
{

    Node<T1>* newnode = new Node<T1>(append_node);
    //Node<T1>* newnode = NULL;

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
        for(Node<T1>* tmp = head; tmp!= NULL; tmp=tmp->next)
        {
            tmp->data->displayData();
        }
    }
}

int main()
{
    UnderGraduate p1("dyp", 'f', 22, 430424199912093814, 650);
    //p1.displayData();
    
    Teacher p2("ypd", 'f', 32, 430424198912093814, 65000);
    //p2.displayData();

    LinkedList<Person> myList;
    myList.append(&p1);
    myList.append(&p2);

    myList.print();

}