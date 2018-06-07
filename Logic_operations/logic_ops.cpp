// logic_ops.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <random>

using namespace std;

int perceptron(vector<int> inp, vector<float> &wght, float thita, float ita, int des) {

	int out = 0;

	float sum = 0.0;
	sum = inp[0] * wght[0] + inp[1] * wght[1];

	if ((sum - thita) > 0)
		out = 1;
	else
		out = 0;

	// error correction learning
	wght[0] = wght[0] - ita*(out - des)*inp[0];
	wght[1] = wght[1] - ita*(out - des)*inp[1];

	return out;
}

void and_init(vector< vector<int> > &andy) {

	// 0 & 0
	andy[0][0] = 0;
	andy[0][1] = 0;
	andy[0][2] = andy[0][0] && andy[0][1];

	// 0 & 1
	andy[1][0] = 0;
	andy[1][1] = 1;
	andy[1][2] = andy[1][0] && andy[1][1];

	// 1 & 0
	andy[2][0] = 1;
	andy[2][1] = 0;
	andy[2][2] = andy[2][0] && andy[2][1];

	// 1 & 1
	andy[3][0] = 1;
	andy[3][1] = 1;
	andy[3][2] = andy[3][0] && andy[3][1];

}

void and_gate(vector< int > &bts) {

	// weight initialization
	vector<float> wght(2);
	wght[0] = -0.002;
	wght[1] = 0.004;

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
		y_real = perceptron(input, wght, thita, ita, y_desired);
		//cout << wght[0];

		mse = mse + pow((y_real - y_desired), 2);
		input.clear();
	}

	mse = mse / bts.size();
	cout << " Mean Square Error for the current binary sequence on logic AND operation was : " << mse << endl << endl;

}

void or_init(vector< vector<int> > &ory) {

	// 0 || 0
	ory[0][0] = 0;
	ory[0][1] = 0;
	ory[0][2] = ory[0][0] || ory[0][1];

	// 0 || 1
	ory[1][0] = 0;
	ory[1][1] = 1;
	ory[1][2] = ory[1][0] || ory[1][1];

	// 1 || 0
	ory[2][0] = 1;
	ory[2][1] = 0;
	ory[2][2] = ory[2][0] || ory[2][1];

	// 1 || 1
	ory[3][0] = 1;
	ory[3][1] = 1;
	ory[3][2] = ory[3][0] || ory[3][1];

}

void or_gate(vector< int > &bts) {

	// weight initialization
	vector<float> wght(2);
	wght[0] = -0.002;
	wght[1] = 0.004;

	// weight changing rate
	float ita = 0.21;

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
		y_real = perceptron(input, wght, thita, ita, y_desired);

		mse = mse + pow((y_real - y_desired), 2);
		input.clear();
	}

	mse = mse / bts.size();
	cout << " Mean Square Error for the current binary sequence on logic OR operation was : " << mse << endl << endl;

}

void xor_init(vector< vector<int> > &xory) {

	// 0 ^ 0
	xory[0][0] = 0;
	xory[0][1] = 0;
	xory[0][2] = xory[0][0] ^ xory[0][1];

	// 0 ^ 1
	xory[1][0] = 0;
	xory[1][1] = 1;
	xory[1][2] = xory[1][0] ^ xory[1][1];

	// 1 ^ 0
	xory[2][0] = 1;
	xory[2][1] = 0;
	xory[2][2] = xory[2][0] ^ xory[2][1];

	// 1 ^ 1
	xory[3][0] = 1;
	xory[3][1] = 1;
	xory[3][2] = xory[3][0] ^ xory[3][1];

}

void xor_gate(vector< int > &bts) {

	// weight initialization
	vector<float> wght(2);
	wght[0] = -0.002;
	wght[1] = 0.004;

	// weight changing rate
	float ita = 0.21;

	// threshold
	float thita = 1.0;
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

	mse = mse / bts.size();
	cout << " Mean Square Error for the current binary sequence on logic XOR operation was : " << mse << endl << endl;

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
	/*
	// AND truth table
	vector< vector<int> > and_tt( 4, vector< int > (3));
	and_init(and_tt);

	// OR truth table
	vector< vector<int> > or_tt(4, vector< int >(3));
	or_init(or_tt);

	// XOR truth table
	vector< vector<int> > xor_tt(4, vector< int >(3));
	xor_init(xor_tt);
	*/

	// create a random binary sequence of 128 bits. two-by-two bits as an input in each logic gate 
	vector< int > bits;
	bits.resize(128);
	bin_seq(bits.begin(), bits.end());

	cout << "The random binary sequence is generated as follows :" << endl;
	for (const auto& elem : bits)
	{
		cout << elem << ' ';
	}
	cout << endl;

	and_gate( bits);
	or_gate( bits);
	xor_gate( bits);


	return 0;

}

