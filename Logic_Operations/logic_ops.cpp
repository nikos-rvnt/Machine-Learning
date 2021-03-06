// logic_ops.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
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

	//cout << " Sto perceptron ta varh: " << wght_p[0] << endl;

	return out;
}

int and_gate( vector<int> inps, vector<double> &wght, float thita, double ita) {

	int and_out, and_out_des;

	and_out_des = inps[0] && inps[1];
	and_out = perceptron(inps, wght, thita, ita, and_out_des);
	//cout << "Ta varh sthn AND" << wght[0] << endl;

	return and_out;
}

void and_eval(vector< int > &bts) {

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
		//y_real = perceptron(input, wght_and, thita, ita, y_desired);
		y_real = and_gate(input, wght_and, thita, ita);

		//cout << "AND_w : " << wght_and[0] << wght_and[1] << endl;

		mse = mse + pow((y_real - y_desired), 2);
		input.clear();
	}

	mse = mse / (bts.size()/2);
	cout << " Mean Square Error of the logic AND operation was : " << mse << endl << endl;

}

int or_gate(vector<int> inps, vector<double> &wght, float thita, double ita) {

	int or_out, or_out_des;

	or_out_des = inps[0] || inps[1];
	or_out = perceptron(inps, wght, thita, ita, or_out_des);

	return or_out;
}

void or_eval(vector< int > &bts) {

	// weight initialization
	static vector<double> wght_or = { -0.001, 0.0035};

	// weight changing rate
	double ita = 0.21;

	// threshold
	float thita = 0.5;
	int y_desired = 0;

	vector<int> input(2);
	double mse = 0;
	int y_real = 0;
	for (unsigned int i = 0; i < bts.size(); i += 2) {

		input[0] = (bts[i]);
		input[1] = (bts[i + 1]);
		y_desired = input[0] || input[1];
		//y_real = perceptron(input, wght_or, thita, ita, y_desired);
		y_real = or_gate(input, wght_or, thita, ita);

		mse = mse + pow((y_real - y_desired), 2);
		//input.clear();
	}

	mse = mse / (bts.size() / 2);
	cout << " Mean Square Error of the logic OR operation is : " << mse << endl << endl;

}


vector<int> xor_indirect( int bit1, int bit2, vector<double> &wght_andx, vector<double> &wght_orx) {

	// weight changing rate
	double ita = 0.21;

	// threshold
	float thita_and = 1.5;
	float thita_or = 0.5;
	int y_desired = 0;
	int y_desired_and = 0;
	int y_desired_or = 0;

	vector<int> input;
	//double mse = 0;
	int y_real = 0;
	int y_real_and = 0;
	int y_real_or = 0;

	
	input.push_back(bit1);
	input.push_back(bit2);

	y_desired_and = input[0] && input[1];
	//y_real_and = perceptron(input, wght_andx, thita_and, ita, y_desired);
	y_real_and = and_gate(input, wght_andx, thita_and, ita);

	y_desired_or = input[0] || input[1];
	//y_real_or = perceptron(input, wght_orx, thita_or, ita, y_desired);
	y_real_or = or_gate(input, wght_orx, thita_or, ita);

	// ( (AND') && (OR) )
	//input.clear();
	if (y_real_and == 0)
		y_real_and = 1;
	else
		y_real_and = 0;

	input[0] = y_real_and;
	input[1] = y_real_or;
	y_desired = input[0] && input[1];
	//y_real = perceptron(input, wght_andx, thita_and, ita, y_desired);
	y_real = and_gate(input, wght_andx, thita_and, ita);

	//mse = mse + pow((y_real - y_desired), 2);

	vector<int> y_back(2);
	y_back[0] = y_real;
	y_back[1] = y_desired;
	//cout << "Ind real: " << y_back[0] << " des: " << y_back[1] << endl;

	return y_back;

}

void xor_eval(vector< int > &bts) {

	// weight initialization
	static vector<double> wght_andx = { -0.002, 0.004 };
	static vector<double> wght_orx = { -0.001, 0.005 };

	int y_desired = 0;
	double mse = 0;
	vector<int> xor_res;

	for (unsigned int i = 0; i < bts.size(); i += 2) {

		xor_res = xor_indirect(bts[i], bts[i + 1], wght_andx, wght_orx);

		y_desired = !(bts[i] && bts[i+1]) && (bts[i] || bts[i+1]) ;
		//cout << " real: " << xor_res[0] << " des: " << xor_res[1] << endl;

		mse = mse + pow((xor_res[0] - xor_res[1]), 2);
		
	}

	mse = mse / (bts.size() / 2);
	cout << " Mean Square Error of the logic XOR operation is : " << mse << endl << endl;

}


vector<int> full_adder( int bit1, int bit2, int carry, vector<double> &wght_AND, vector<double> &wght_OR) {

	// weight changing rate
	double ita = 0.21;

	// threshold
	float thita_and = 1.5;
	float thita_or = 0.5;

	vector<int> input(2);
	int and1_real, and2_real, or1_real;
	int and1_des, and2_des, or1_des;
	vector<int> xor1_b(2), xor2_b(2);


	input[0] = (bit1);
	input[1] = (bit2);

	// AND1
	and1_des = input[0] && input[1];
	and1_real = and_gate(input, wght_AND, thita_and, ita);

	// XOR1
	xor1_b = xor_indirect(input[0], input[1], wght_AND, wght_OR);

	// XOR2 --> OUTPUT
	xor2_b = xor_indirect(xor1_b[0], carry, wght_AND, wght_OR);

	// AND2
	and2_des = carry && xor1_b[0];
	input[0] = carry;
	input[1] = xor1_b[0];
	and2_real = and_gate(input, wght_AND, thita_and, ita);

	// OR --> CARRY
	or1_des = and2_real || and1_real;
	input[0] = and2_real;
	input[1] = and1_real;
	or1_real = or_gate(input, wght_OR, thita_or, ita);

	//cout << " X1: " << bit1 << " X2: " << bit2 << " Carry: " << carry << " Output : " << xor2_b[0] << " Carry_Out : " << or1_real << endl;
	carry = or1_real;
	
	vector<int> fa_back(3);
	fa_back[0] = xor2_b[0]; //y_real;
	fa_back[1] = xor2_b[1]; //y_desired;
	fa_back[2] = or1_real;

	return fa_back;

}

void full_adder_eval( vector< int > &bts1, vector< int > &bts2) {

	// weight initialization
	static vector<double> wght_andFA = { -0.002, 0.004 };
	static vector<double> wght_orFA = { -0.001, 0.005 };

	// weight changing rate
	double ita = 0.21;

	// threshold
	float thita_and = 1.5;
	float thita_or = 0.5;

	vector<int> input(2);
	double mse = 0;
	int carry;
	//int and1_real, and2_real, xor1_real, xor2_real, or1_real, temp_or_real;
	//int and1_des, and2_des, xor1_des, xor2_des, or1_des, temp_or_des;
	vector<int> add_out(bts1.size());
	vector<int> xor1_b(2), xor2_b(2);
	vector<int> fa_back(3);

	for (unsigned int i = 0; i < bts1.size(); i++) {

		carry = (i==0) ? 0 : carry;

		fa_back = full_adder( bts1[i], bts2[i], carry, wght_andFA, wght_orFA);

		mse = mse + pow((fa_back[0] - fa_back[1]), 2);

	}

	mse = mse / (bts1.size());
	cout << " Mean Square Error of the full adder operation is : " << mse << endl << endl;

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
	vector< int > bits_train, bits1_train_FA, bits2_train_FA;
	bits_train.resize(256);
	bin_seq(bits_train.begin(), bits_train.end());
	// first sequence for addition
	bits1_train_FA.resize(256);
	bin_seq(bits1_train_FA.begin(), bits1_train_FA.end());
	// second sequence for addition
	bits2_train_FA.resize(256);
	bin_seq(bits2_train_FA.begin(), bits2_train_FA.end());
	/*
	cout << "The random binary sequence is formed as :" << endl;
	for (const auto& elem : bits_train)
	{
		cout << elem << ' ';
	}*/
	cout << endl << endl;
	

	// training AND, OR, XOR, Full-Adder
	cout << " Mean Square Error of training phase of each logic operation. " << endl << endl;
	and_eval( bits_train );
	or_eval( bits_train );
	// training xor through ( (AND') && (OR) ) equation to get a better MSE
	xor_eval(bits_train);
	full_adder_eval( bits1_train_FA, bits2_train_FA);

	// create a random binary sequence of 1024 bits for testing. two-by-two bits as an input in each logic gate 
	vector< int > bits_test, bits1_test_FA, bits2_test_FA;
	bits_test.resize(1024);
	bin_seq(bits_test.begin(), bits_test.end());
	// first sequence for testing full adder
	bits1_test_FA.resize(1024);
	bin_seq(bits1_test_FA.begin(), bits1_test_FA.end());
	// first sequence for testing full adder
	bits2_test_FA.resize(1024);
	bin_seq(bits2_test_FA.begin(), bits2_test_FA.end());
	/*
	cout << endl << "The random testing binary sequence is formed as :" << endl;
	for (const auto& elem : bits_test)
	{
	cout << elem << ' ';
	}*/
	cout << endl;
	
	cout << endl << "After weight training, Mean Square Error of testing phase of each logic operation results as : " << endl << endl;
	// testing AND, OR, XOR
	and_eval(bits_test);
	or_eval(bits_test);
	//xor_gate(bits_test);
	// testing xor through ( (AND') && (OR) ) equation to get a better MSE
	xor_eval(bits_test);
	//xor_indirect(bits_test);
	full_adder_eval( bits1_test_FA, bits2_test_FA);

	return 0;

}
