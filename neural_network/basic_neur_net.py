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

class BasicNeuralNetwork:
    """
    Questo network avrà:
    2 input
    un layer nascosto con 2 neuroni
    un layer di output con un neurone
    ogni neuron avrà gli stessi pesi e bias
    w = [0,1]
    b = 0
    """
    def __init__(self):
        weights = np.array([0,1])
        bias = 0
        self.h1 = Neuron(weights, bias)
        self.h2 = Neuron(weights, bias)
        self.o1 = Neuron(weights, bias)
    
    def feedforward(self, x):
        out_h1 = self.h1.feedforward(x)
        out_h2 = self.h2.feedforward(x)
        out_o1 = self.o1.feedforward(np.array([out_h1, out_h2]))
        return out_o1

network = BasicNeuralNetwork()
x = np.array([2,3])
print(network.feedforward(x))