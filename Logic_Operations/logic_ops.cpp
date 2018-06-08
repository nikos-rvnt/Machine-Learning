// logic_ops.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <random>

using namespace std;

int perceptron(vector<int> inp, vector<double> &wght_p, float thita, double ita, int des) {

	int out = 0;

	float sum = 0.0;
	sum = inp[0] * wght_p[0] + inp[1] * wght_p[1];

	if ((sum - thita) > 0)
		out = 1;
	else
		out = 0;

	// error correction learning
	wght_p[0] = wght_p[0] - ita*(out - des)*inp[0];
	wght_p[1] = wght_p[1] - ita*(out - des)*inp[1];

	return out;
}

void and_gate(vector< int > &bts) {

	// weight initialization
	static vector<double> wght_and = { -0.002, 0.004};

	// weight changing rate
	double ita = 0.21;

	// threshold
	float thita = 1.5;
	int y_desired = 0;

	vector<int> input;
	double mse = 0;
	int y_real = 0;
	for (unsigned int i = 0; i < bts.size(); i += 2) {

		input.push_back(bts[i]);
		input.push_back(bts[i + 1]);
		y_desired = input[0] && input[1];
		y_real = perceptron(input, wght_and, thita, ita, y_desired);
		//cout << "AND_w : " << wght_and[0] << wght_and[1] << endl;

		mse = mse + pow((y_real - y_desired), 2);
		input.clear();
	}

	mse = mse / (bts.size()/2);
	cout << " Mean Square Error for the binary sequence on logic AND operation was : " << mse << endl << endl;

}

void or_gate(vector< int > &bts) {

	// weight initialization
	static vector<double> wght_or = { -0.001, 0.0035};

	// weight changing rate
	double ita = 0.21;

	// threshold
	float thita = 0.5;
	int y_desired = 0;

	vector<int> input;
	double mse = 0;
	int y_real = 0;
	for (unsigned int i = 0; i < bts.size(); i += 2) {

		input.push_back(bts[i]);
		input.push_back(bts[i + 1]);
		y_desired = input[0] || input[1];
		y_real = perceptron(input, wght_or, thita, ita, y_desired);

		mse = mse + pow((y_real - y_desired), 2);
		input.clear();
	}

	mse = mse / (bts.size() / 2);
	cout << " Mean Square Error for the binary sequence on logic OR operation is : " << mse << endl << endl;

}

void xor_gate(vector< int > &bts) {

	// weight initialization
	static vector<double> wght = { -0.0015, 0.0025};

	// weight changing rate
	double ita = 0.21;

	// threshold
	float thita = .5;
	int y_desired = 0;

	vector<int> input;
	double mse = 0;
	int y_real = 0;
	for (unsigned int i = 0; i < bts.size(); i += 2) {

		input.push_back(bts[i]);
		input.push_back(bts[i + 1]);
		y_desired = input[0] ^ input[1];
		y_real = perceptron(input, wght, thita, ita, y_desired);

		mse = mse + pow((y_real - y_desired), 2);
		input.clear();
	}

	mse = mse / (bts.size() / 2);
	cout << " Mean Square Error for the binary sequence on logic XOR operation is : " << mse << endl << endl;

}

void xor_indirect(vector< int > &bts) {
	// weight initialization
	static vector<double> wght_andx = { -0.002, 0.004};
	
	static vector<double> wght_orx = { -0.001, 0.005};

	// weight changing rate
	double ita = 0.21;

	// threshold
	float thita_and = 1.5;
	float thita_or = 0.5;
	int y_desired = 0;
	int y_desired_and = 0;
	int y_desired_or = 0;

	vector<int> input;
	double mse = 0;
	int y_real = 0;
	int y_real_and = 0;
	int y_real_or = 0;

	for (unsigned int i = 0; i < bts.size(); i += 2) {

		input.push_back(bts[i]);
		input.push_back(bts[i + 1]);
		
		y_desired_and = input[0] && input[1];
		y_real_and = perceptron(input, wght_andx, thita_and, ita, y_desired);
		y_desired_or = input[0] || input[1];
		y_real_or = perceptron(input, wght_orx, thita_or, ita, y_desired);

		// ( (AND') && (OR) )
		input.clear();
		if (y_real_and == 0)
			y_real_and = 1;
		else
			y_real_and = 0;
		input.push_back(y_real_and);
		input.push_back(y_real_or);
		y_desired = input[0] ^ input[1];
		y_real = perceptron(input, wght_andx, thita_and, ita, y_desired);
		
		mse = mse + pow((y_real - y_desired), 2);
		input.clear();
	}

	mse = mse / (bts.size() / 2);
	cout << " Mean Square Error for the binary sequence on logic (indirect) XOR operation is : " << mse << endl << endl;

}

template <typename OutputIt, typename Engine = std::mt19937>
void bin_seq(OutputIt elem, OutputIt end)
{
	// static so each time different sequence
	static Engine engine;
	std::bernoulli_distribution distribution;

	while (elem != end)
	{
		*elem++ = distribution(engine);
	}
}

int main()
{

	// create a random binary sequence of 256 bits for training. two-by-two bits as an input in each logic gate 
	vector< int > bits_train;
	bits_train.resize(256);
	bin_seq(bits_train.begin(), bits_train.end());

	cout << "The random binary sequence is formed as :" << endl;
	for (const auto& elem : bits_train)
	{
		cout << elem << ' ';
	}
	cout << endl << endl;
	

	// training AND, OR, XOR
	and_gate( bits_train );
	or_gate( bits_train );
	xor_gate( bits_train );
	// training xor through ( (AND') && (OR) ) equation to get a better MSE
	xor_indirect(bits_train);

	// create a random binary sequence of 256 bits for testing. two-by-two bits as an input in each logic gate 
	vector< int > bits_test;
	bits_test.resize(1024);
	bin_seq(bits_test.begin(), bits_test.end());

	cout << endl << "The random testing binary sequence is formed as :" << endl;
	for (const auto& elem : bits_test)
	{
	cout << elem << ' ';
	}
	cout << endl;
	
	cout << endl << "After trained weights, MSE for the 3 logic gates results as : " << endl << endl;
	// testing AND, OR, XOR
	and_gate(bits_test);
	or_gate(bits_test);
	xor_gate(bits_test);
	// testing xor through ( (AND') && (OR) ) equation to get a better MSE
	xor_indirect(bits_test);

	return 0;

}
