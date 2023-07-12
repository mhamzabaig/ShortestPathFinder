#include<iostream>
#include<fstream>                       //     for file handling....
#include<sstream>                       //     for Stringstream function to convert string to integer...
using namespace std;

int get_Prev_ID()  //                          To get the ID of last registered student to for entering other students....
{
    string last_id;                            

    ifstream fin("std_username.txt");
    
    while(!fin.eof())       //                 eof func to get a the end of file while last_id will have the last id assigned to std..
    {
        fin>>last_id;
    }
    fin.close();

    //                                         Using stringstream to convert string(ID of student) into integer_ID...

    int to_int = 0;
    stringstream geek(last_id);
    geek >>to_int;

    return to_int;
}

void Sign_up() // 
{

    int prev_id = get_Prev_ID();
    prev_id++; //                              Increment for Making NEW ID.......
    
    string usrname;cout<<"Enter your username : ";cin>>usrname;

    

    if(prev_id-1==0)                        // base case just for the first student record....
    {
        ofstream out("std_username.txt");
        
        out<< usrname +  "        " + to_string(prev_id)<<endl;
        out.close();    
    }
    else
    {
        ofstream out("std_username.txt", ios::app);
        
        out<< usrname +  "        " + to_string(prev_id)<<endl;
        out.close();
    }    
}

int main()
{
    
    Sign_up();

    
    
}