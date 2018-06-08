## Logic Operations Implementation through Perceptron

Logic Gates AND, OR, XOR are implemented through Perceptron.

Firstly, a random bernulli binary sequence of 256 bits is generated for training each logic gate, that is for optimizing the weights of perceptron for each case. Weights are initialised with values nearly zero (e.g. -0.002). The learning rate is fixed as 0.21 and a thita (θ) parameter for the perceptron gets values 1.5, 0.5, 1.0.

As a second stage, for testing the functionality of the logic gates, a random bernuli binary sequence of 1024 bits this time, is generated. Weights keep their trained values from training stage (static vectors). 

After each operation for the whole binary sequence, either training or testing, the MSE ( MSE = (1/Ν)Σ(y_desired - y_real)^2 ) is evaluated and printed on the screen for comparison among the logic operations through perceptron.

Also and because of doubtful XOR MSE results (about 0.5), an indirect implementation of XOR is implemented by the algebra bool equation, (AND_output)' * (OR_output). This implementation gives far better results by the previous one and the reason is that it was difficult to estimate an optimum thita parameter for straight XOR operation, in order to take the best discriminant function for the results.

In conclusion, the MSE results for training and teting are as follows :

  - Training:
     Mean Square Error for the binary sequence on logic AND operation was : 0.03125
     Mean Square Error for the binary sequence on logic OR operation is : 0.046875
     Mean Square Error for the binary sequence on logic XOR operation is : 0.460938
     Mean Square Error for the binary sequence on logic (indirect) XOR operation is : 0.0859375
  
  - Testing:
     Mean Square Error for the binary sequence on logic AND operation was : 0
     Mean Square Error for the binary sequence on logic OR operation is : 0
     Mean Square Error for the binary sequence on logic XOR operation is : 0.5
     Mean Square Error for the binary sequence on logic (indirect) XOR operation is : 0
    
Implemented on Visual Studio 2017
