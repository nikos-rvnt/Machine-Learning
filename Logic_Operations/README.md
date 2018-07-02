## Logic Operations Implementation through Perceptron

In this machine learning project, logic gates AND, OR, XOR and FULL-ADDER are implemented through Perceptron.

Firstly, a random bernulli binary sequence of 256 bits is generated for training each logic gate, that is, for optimizing the weights of perceptron for each case. Weights are initialised with values nearly zero (e.g. -0.002). The learning rate is fixed as 0.21 and a thita (θ) parameter for the perceptron gets values 1.5, 0.5, 1.0 respectively.

As a second stage, for testing the functionality of the logic gates, a random bernuli binary sequence of 1024 bits this time, is generated. Weights keep their trained values from training stage (static vectors). 

After each operation for the whole binary sequence, either training or testing, the MSE ( MSE = (1/Ν)Σ(y_desired - y_real)^2 ) is evaluated and printed on the screen for comparison among the logic operations through perceptron.

Also and because of doubtful XOR MSE results (about 0.5), an indirect implementation of XOR is implemented by the algebra bool equation, (X[i] * X[i+1])' * (X[i] + X[i+1]) (or (AND_output)' * (OR_output)). 

For the Full-Adder operation which receives 3 inputs and takes out 2 outputs, the following circuit was implemented for each full addition, combining the previous implemented and_gate(), or_gate() and xor_gate(). 

# ![Alt text](https://github.com/nikos-rvnt/Machine-Learning/blob/master/Logic_Operations/full_on.jpg) 

In conclusion, the MSE results for training and testing are as follows :

  - Training:
     * Mean Square Error of the logic AND operation was : 0.03125
     * Mean Square Error of the logic OR operation is : 0.046875  
     * Mean Square Error of the logic XOR operation is : 0.0234375
     * Mean Square Error of the full adder operation is : 0
  
  - Testing:
     * Mean Square Error of the logic AND operation was : 0
     * Mean Square Error of the logic OR operation is : 0
     * Mean Square Error of the logic XOR operation is : 0
     * Mean Square Error of the full adder operation is : 0
    
Implemented on Visual Studio 2017
