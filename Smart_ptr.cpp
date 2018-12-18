#include <iostream>
using namespace std;
class Temp
{
	int TEMP;
	public:

		Temp(){TEMP=25;}
		void TempFunction(){
			cout<<"TEMP = "<<TEMP<<"\n\n";
		}

		void TempSet(int T){
			TEMP=T;
		}
};
class SmartPointer
{

	Temp*ptr;
    int count_copy;

public:
	SmartPointer (Temp*p=NULL){
		count_copy=0;
		ptr=p;
	}

	SmartPointer (const SmartPointer&obj){
		ptr=obj.ptr;
		count_copy++;
	}
	SmartPointer operator=(const SmartPointer&obj){
		ptr=obj.ptr;
		ptr=obj.ptr;
		count_copy++;
		return *this;
	}
	~SmartPointer(){
		if(ptr!=NULL&&count_copy==0){
			cout<<"\n~Delete Object\n";
			delete[]ptr;
		}
		else{
			count_copy--;
			cout<<"\n~Delete Copy\n";
		}

	}

	Temp* operator->(){
		return ptr;
	}

};

int main(){
    SmartPointer <Temp> main_ptr(new Temp);
	Temp*main_ptr=new Temp;
	SmartPointer PTR(main_ptr);

	PTR->TempSet(100);
	PTR->TempFunction();

	SmartPointer PTR2=PTR;
}


