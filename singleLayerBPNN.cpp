#include <iostream>
#include <cstdlib>	//for random value 

using namespace std;

int main(int argc, char* argv[])
{
	int h = 4;	//default number of units in hidden layer
	int n = 2;	//default number of units in input layer
	int m = 1;	//default number of units in output layer

	if(argc==4)
	{
		n = atoi(argv[2]);
		h = atoi(argv[3]);
		m = atoi(argv[4]);
	}else if (argc>1)
	{
		cout<<"Using Default values"<<endl;
	}
	
	cout<<"Your values for "<<endl;
	cout<<".. no of units in Input layer is "<<n<<endl;
        cout<<".. no of units in Hidden layer is "<<h<<endl;        
	cout<<".. no of units in Output layer is "<<m<<endl;

	return 0;
}
