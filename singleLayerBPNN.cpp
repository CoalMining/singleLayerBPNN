#include <iostream>
#include <cstdlib>	//for random value 
#include <time.h>
#include <cmath>

#define alpha 0.1

using namespace std;

//Giving names to the input and output of the units in different layers
	float *X;	//the values in the input layer, input and output are same at the input layer
	float *Z_in;	//the values in the hidden layer, input
	float *Z_out;	//the values in the hidden layer, output
	float *Y_in;	//the values in the output layer, input
	float *Y_out;	//the values in the output layer, output

//following is the squashing function
	//sigmoid function is used
inline float squashing(float inVal)
{
	return (1/(1+exp(-1*inVal)));
}

inline float derSquashing(float inVal)
{
	return (squashing(inVal)*(1-(squashing(inVal))));
}

void calcHiddenInput()
{
//calculating the inputs to the hidden layer
	for(int j=1;j<=h;j++)
	{
		Z_in[j] = 0;
		for(int i=0;i<=n;i++)
			Z_in[j] += (X[i]*V[i][j]); 
	}
}

void calcHiddenOutput()
{
	Z_out[0] = 1;
	for(int j=1;j<=h;j++)
	{
		Z_out[j] = squashing(Z_in[j]);
	}
}

void calcOutputInput()
{
	// there are only m units in the output layer
		//no bias
	for(int k=0;k<m;k++)
	{
		Y_in[k] = 0;

		// input is impacted from all the units in the hidden layer
		for(int j=0;j<=h;j++)
			Y_in[k]+=Z_out[j]*W[j][k];
	}
}

void calcOutputOutput()
{
	for(int k=0;k<m;k++)
	{
		Y_out[k] = squashing(Y_in[k]);
	}
}

/**HERE**/
//change the following arrays for your use
	//input array
float inputArray[] [] = {{0,0},
						 {0,1},
						 {1,0},
						 {1,1}};
	//output Array
float outPutArray[] = {0,1,1,0};						 

int main(int argc, char* argv[])
{
	int h = 4;	//default number of units in hidden layer
	int n = 2;	//default number of units in input layer
	int m = 1;	//default number of units in output layer
	bool condition = false;
	long long iterCnt = 0;

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

//Initializing the arrays
	//for input layer, although there are n units, n+1 is the number with a bias
	X = new float[n+1];
	//for hidden layer, although there are h units, h+1 is the number with a bias
		//Z_in[0] will  be unused
	Z_in = new float[h+1];
	Z_out = new float[h+1];
	//but for output layer, the number of units is equal to the number of actual outputs, no bias
	Y_in = new float[m];
	Y_out = new float[m];
	Act_out = new float[m];


	float *ek = new float[m];
	float *dk = new float[m];
	float *dj = new float[j+1];


//Declaring the connections between the layers
	//Connections between the layer input and hidden are called V
	//There are n+1 X h connections between the input and hidden layer
	float **V = new float*[n+1];
	float **dV = new float*[n+1];
	for(int i;i<=n;i++)
	{
		*(V+i) = new float[h];
		*(dV+i) = new float[h];
	}
	//Connection between the layers: hidden and output are called W
	//There are h+1 X m connections between the hidden and output layer
	float **W = new float*[h+1];
	float **dW = new float*[h+1];
	for(int i=0;i<=h;i++)
	{
		*(W+i) = new float[m];
		*(dW+i) = new float[m];
	}


//initializing the connection values to some random values
	cout<<"The initial weights of the connections are :"<<endl;
	for(int i=0;i<=n;i++)
		for(int j=0;j<h;j++)
		{
			V[i][j] = ((((float)rand()))/RAND_MAX)-.5;
			//cout<<V[i][j]<<endl;
		}
	for(int i=0;i<=h;i++)
		for(int j=0;j<m;j++)
		{
			W[i][j] = ((((float)rand()))/RAND_MAX)-.5;
			//cout<<W[i][j]<<endl; 
		}

//loop until convergence condition
//if condition is true, loop out
while(iterCnt<2500000)
{
	//initialize the first element of the input layer as 1, which is the bias
	X[0] = 1;

/**Here**/
	//feed the input and output of training values right here
	for(int i = 1;i<=n;i++)
		X[i] = inputArray[iterCnt%4][i];
	for(int i=0;i<m;i++)
		Act_out = outPutArray[iterCnt%4];


	//calculate input to the hidden layer
	calcHiddenInput();
	//calculate output of the hidden layer
	calcHiddenOutput();
	//calculate input to the output layer
	calcOutputInput();
	//calculate output of the output layer
	calcOutputOutput();


//propagation part
	//calculate error in the output
	for(int k=0;k<m;k++)
	{
		ek[k] = Act_out[k]-Y_out[k];
		dk[k] = ek[k]*derSquashing(Y_in[k]);
	}
	//adjust the weight joining hidden and output layer based on this error value
	for(int j=0;j<=h;j++)
	{
		for(int 0;k<m;k++)
			dW[j][k]  = alpha*dk[k]*Z_out[j];
	}

	//Propagate error from the output layer to the hidden layer
	//this propagated error will affect the value of connection of previous layer
	//we need to calculate dj value for all the units in the hidden layer except the bias
	for(int j=1;j<=h;j++)
	{
		float sumVal = 0;
		//but for each dj we need to calculate the weighted sum of the error at input of previous layer
		//which is the actual propagation
		for(int k=1;k<=m;k++)
		{	
			sumVal+=dk[k]*W[j][k];
		}
		dj[j] = sumVal*derSquashing(Z_in[j]);
	}

	//change the weights of V based on this
	for(int i=0;i<=n;i++)
	{
		for(int j=1;j<=h;j++)
			dV[i][j] = alpha*dj[j]*X[i];
	}
	iterCnt++;
}

//freeing memory for the array initialized above
	delete[] X;
	delete[] Z_in;
	delete[] Z_out;
	delete[] Y_in;
	delete[] Y_out;
	delete[] Act_out;
	for(int i=0;i<=n;i++)
		delete[] *(V+i);
	delete[] V;

	for(int i=0;i<=h;i++)
		delete[] *(W+i);
	delete[] W;

	return 0;
}
