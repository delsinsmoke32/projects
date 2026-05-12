import numpy as np
 
def sigmoid(x):
    #valori molto bassi per x -> inf, alti per x -> -inf
    return 1 / (1 + np.exp(-x))

class Neuron:
    def __init__(self, weights, bias):
        self.weights = weights
        self.bias = bias
    
    def feedforward(self, inputs):
        #weigth inputs, add bias, call activation function
        #dot = dot product (prodotto fra vettori ez)
        total = np.dot(self.weights, inputs) + self.bias
        return sigmoid(total)
    

weights = np.array([0,1])
bias = 4
n = Neuron(weights, bias)

x = np.array([2,3])
print(n.feedforward(x))