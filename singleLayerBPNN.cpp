#include <iostream>
#include <cstdlib>	//for random value 
#include <time.h>

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

	srand(time(NULL));
	
	cout<<"Your values for "<<endl;
	cout<<".. no of units in Input layer is "<<n<<endl;
        cout<<".. no of units in Hidden layer is "<<h<<endl;        
	cout<<".. no of units in Output layer is "<<m<<endl;

//Giving names to the input and output of the units in different layers
	float *X;	//the values in the input layer, input and output are same at the input layer
	float *Z_in;	//the values in the hidden layer, input
	float *Z_out;	//the values in the hidden layer, output
	float *Y_in;	//the values in the output layer, input
	float *Y_out;	//the values in the output layer, output
//Initializing the arrays
	X = new float[n];
	Z_in = new float[h];
	Z_out = new float[h];
	Y_in = new float[m];
	Y_out = new float[m];
//Declaring the connections between the layers
	//Connections between the layer input and hidden are called V
	//There are n+1 X h connections between the input and hidden layer
	float **V = new float*[n+1];
	for(int i;i<=n;i++)
		*(V+i) = new float[h];
	//Connection between the layers: hidden and output are called W
	//There are h+1 X m connections between the hidden and output layer
	float **W = new float*[h+1];
	for(int i=0;i<=h;i++)
		*(W+i) = new float[m];

//initializing the connection values to some random values

	cout<<"The initial weights of the connections are :"<<endl;
	for(int i=0;i<=n;i++)
		for(int j=0;j<h;j++)
		{
			V[i][j] = ((((float)rand()))/RAND_MAX)-.5;
			cout<<V[i][j]<<endl;
		}
	for(int i=0;i<=h;i++)
		for(int j=0;j<m;j++)
		{
			W[i][j] = ((((float)rand()))/RAND_MAX)-.5;
			cout<<W[i][j]<<endl; 
		}

//freeing memory for the array initialized above
	delete[] X;
	delete[] Z_in;
	delete[] Z_out;
	delete[] Y_in;
	delete[] Y_out;
	for(int i=0;i<=n;i++)
		delete[] *(V+i);
	delete[] V;

	for(int i=0;i<=h;i++)
		delete[] *(W+i);
	delete[] W;

	return 0;
}
