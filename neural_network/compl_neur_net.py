import numpy as np
#import matplotlib.pyplot as plt

def sigmoid(x):
    #valori molto bassi per x -> inf, alti per x -> -inf
    return 1 / (1 + np.exp(-x))

def derivative_sigmoid(x):
    #derivata della sigmoid, easy enough
    return sigmoid(x) * (1 - sigmoid(x))

def mse_loss(y_true, y_pred):
    return np.mean(((y_true - y_pred) ** 2))


class Neuron:
    def __init__(self, weights, bias):
        self.weights = weights
        self.bias = bias
    
    def feedforward(self, inputs):
        #weigh inputs, add bias, call activation function
        #dot = dot product (prodotto fra vettori ez)
        total = np.dot(self.weights, inputs) + self.bias
        return sigmoid(total)

class ComplNeuralNetwork:
    """
    Questo network avrà:
    2 input
    un layer nascosto con 2 neuroni
    un layer di output con un neurone
    ogni neuron avrà gli stessi pesi e bias
    w = [0,1]
    b = 0

    DISCLAIMER: NON E' OTTIMIZZATO, SERVE SOLO
    PER CAPIRE COME FUNZIONANO I NETWORK NEURALI
    """
    def __init__(self):
        #weights
        self.w1 = np.random.normal()
        self.w2 = np.random.normal()
        self.w3 = np.random.normal()
        self.w4 = np.random.normal()
        self.w5 = np.random.normal()
        self.w6 = np.random.normal()

        #biases
        self.b1 = np.random.normal()
        self.b2 = np.random.normal()
        self.b3 = np.random.normal()
        
    
    def feedforward(self, x):
        #x è un array numpy con 2 elementi
        h1 = sigmoid(self.w1 * x[0] + self.w2 * x[1] + self.b1)
        h2 = sigmoid(self.w3 * x[0] + self.w4 * x[1] + self.b2)
        o1 = sigmoid(self.w5 * h1 + self.w6 * h2 + self.b3)
        return o1
    
    def train(self, data, all_y_trues):
        """
        data è array np (n x 2),
        dove n è il numero di sample nel dataset
        all_y_trues è un array numpy con n elementi
        gli elementi in all_y_trues corrispondono
        a quelli in data.
        """
        losses = []
        epochs1 = []
        learn_rate = 0.1
        epochs = 1000 #numero di loop

        for epoch in range(epochs):
            for x, y_true in zip(data, all_y_trues):
                #fai feedforward
                sum_h1 = self.w1 * x[0] + self.w2 * x[1] + self.b1
                h1 = sigmoid(sum_h1)

                sum_h2 = self.w3 * x[0] + self.w4 * x[1] + self.b2
                h2 = sigmoid(sum_h2)

                sum_o1 = self.w5 * h1 + self.w6 * h2 + self.b3
                o1 = sigmoid(sum_o1)

                y_pred = o1

                #calcolo derivate parziali
                #d_Ld_w1 rappresenta "parziale L / parziale w1"

                d_L_d_ypred = -2 * (y_true - y_pred)

                #Neuron o1

                d_ypred_d_w5 = h1 * derivative_sigmoid(sum_o1)
                d_ypred_d_w6 = h2 * derivative_sigmoid(sum_o1)
                d_ypred_d_b3 = derivative_sigmoid(sum_o1)

                d_ypred_d_h1 = self.w5 * derivative_sigmoid(sum_o1)
                d_ypred_d_h2 = self.w6 * derivative_sigmoid(sum_o1)

                #Neuron h1
                d_h1_d_w1 = x[0] * derivative_sigmoid(sum_h1)
                d_h1_d_w2 = x[1] * derivative_sigmoid(sum_h1)
                d_h1_d_b1 = derivative_sigmoid(sum_h1)

                #Neuron h2

                d_h2_d_w3 = x[0] * derivative_sigmoid(sum_h2)
                d_h2_d_w4 = x[1] * derivative_sigmoid(sum_h2)
                d_h2_d_b2 = derivative_sigmoid(sum_h2)

                #update di pesi e bias

                #Neuron h1
                self.w1 -= learn_rate * d_L_d_ypred * d_ypred_d_h1 * d_h1_d_w1
                self.w2 -= learn_rate * d_L_d_ypred * d_ypred_d_h1 * d_h1_d_w2
                self.b1 -= learn_rate * d_L_d_ypred * d_ypred_d_h1 * d_h1_d_b1
                
                #Neuron h2
                self.w3 -= learn_rate * d_L_d_ypred * d_ypred_d_h2 * d_h2_d_w3
                self.w4 -= learn_rate * d_L_d_ypred * d_ypred_d_h2 * d_h2_d_w4
                self.b2 -= learn_rate * d_L_d_ypred * d_ypred_d_h2 * d_h2_d_b2

                #Neuron o1
                self.w5 -= learn_rate * d_L_d_ypred * d_ypred_d_w5
                self.w6 -= learn_rate * d_L_d_ypred * d_ypred_d_w6
                self.b3 -= learn_rate * d_L_d_ypred * d_ypred_d_b3

                #calcolo perdita totale alla fine di ogni epoch
                if epoch % 10 == 0:
                    y_preds = np.apply_along_axis(self.feedforward, 1, data)
                    loss = mse_loss(all_y_trues, y_preds)
                    print("Epoch %d loss: %.3f" % (epoch, loss))
                    epochs1.append(epoch)
                    losses.append(loss)
        
        #fig, axis = plt.subplots()
        #axis.plot(epochs1, losses)
        #plt.show()



#definiamo dataset
data = np.array([
    [-2, -1], #Alice
    [25, 6], #Bob
    [17, 4], #Charlie
    [-15, -6], #Diana
])
all_y_trues = np.array([
    1, #Alice
    0, #Bob
    0, #Charlie
    1, #Diana
])
network = ComplNeuralNetwork()
network.train(data, all_y_trues)

#ora che è allenato, usiamolo per fare delle predizioni!
#ricordiamoci: donna = 1, uomo = 0
emily = np.array([-7, -3])
frank = np.array([20, 2])

print("Emily: " + str(network.feedforward(emily)))
print("Frank: " + str(network.feedforward(frank)))