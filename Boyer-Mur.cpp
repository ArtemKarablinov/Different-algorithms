#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <mach/mach_time.h>
//#include <Windows.h>

using namespace std;

int main ()
{
    ifstream textfile;
    textfile.open("text.txt");

    string str;
    string str1;
    string pat = "In a statement released last week they said that their engine broke at the end of May. They originally thought they would be able to reach land by relying on wind and their sails.But two months into their journey - and long past their estimated arrival time in Tahiti - they began to issue distress calls, the statement said.Ms Appel said they issued distress signals daily for nearly 100 days but received no response.";


    while (getline(textfile, str1))
    {
        str+=str1;

    };
     textfile.close();
    //string str = "Artemfbdskdjvnkvbsdkvbb Artem";
    int M = pat.length();
    int N = str.length();
    int k, i = M;
    int p;
    cout<<N<<endl;
    int j=M;
    unordered_map<char, int> table;

    //clock_t start_time =  clock();

    //for (int y=0;y<10;y++){
        for (k=0;k<255;k++){
            table[char(k)]=M;
        }


    for (k=0;k<M-1;k++){
        table[pat[k]]=M-k-1;
    };

    k=M-1;
    i=M-1;
    p=-2;
//unsigned long start_time = GetTickCount();
    unsigned long start_time = mach_absolute_time();

    while (k>=0 && i<=N-1){
        j=i;
        k=M-1;
        while (k>=0 && pat[k]==str[j]){
            k--; j--;
            if (k==0){
                p=j-1;
            }
        }
        i+=table[str[i]];
        /*if (table[str[i]]!=0)
            i+=table[str[i]];
        else
            i+=M;
    */
    }
    //unsigned long search_time = GetTickCount() - start_time; //deprecated in OSX
    float search_time = (mach_absolute_time() - start_time)/1e9;
    if (p>=-1){
            p=p+1;
            i=0;
        while (i<M){
            cout<<str[p+i];
            ++i;
        }
    }
    else
        cout<<"Not found";
    cout<<endl<<"Time:"<<search_time;
    ofstream result;
    result.open("Result1(Pat).txt",ios::app);
    result<<N<<' '<<search_time<<endl;;
    result.close();

cout<<endl<<endl;


 // Грубая сила

/*
   k=M-1;
   i=M-1;
   long start_time1 = GetTickCount();
   while(k>=0 && i<=N-1){
        j=i;
        k=M-1;
        while (k>=0 && pat[k]==str[j]){
            k--; j--;
            if (k==0){
                p=j;
            }
        }
        i++;
   }
    long search_time1 = GetTickCount() - start_time1;
   for (i=0;i<M;i++){
        cout<<str[p+i];
   }
    cout<<' '<<N<<' '<<search_time1;
    ofstream result1;
    result1.open("Result(Text) Mad.txt",ios::app);
    result1<<N<<' '<<search_time1<<endl;
    result1.close();
*/
  return 0;
}
