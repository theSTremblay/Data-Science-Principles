import numpy as np
import matplotlib.pyplot as plt
import scipy.io as sio

# setting seed, DON'T modify
np.random.seed(10)
from pylab import rcParams
rcParams['figure.figsize'] = 10, 7

# no need to modify this
def poly_feature(X,poly = 1):
    # expects an array (X) of shape (n,1)
    newX = []
    for i in range(poly+1):
        newX.append(X**i)
    return np.concatenate(newX, axis=1)

dataset = np.load('ps01.data')

item_dataset = dataset.item()

Xtrain = item_dataset['Xtrain']
Xtest = item_dataset['Xtest']
Ytrain = item_dataset['Ytrain']
Ytest = item_dataset ['Ytest']

X = dataset[:,0:99]
Y = dataset[:, 100]

xt = X[1]
xl = X[:,1]

plt.figure(1)
plt.title("Scatter Plot")

plt.scatter(Xtrain, Ytrain, 'r')

plt.scatter(Xtest, Ytest, 'g')

plt.legend()

# PART B
from sklearn.linear_model import LinearRegression

reg = LinearRegression().fit(Xtrain, Ytrain)

R_squared_train = reg.score(Xtrain, Ytrain)

reg2 = LinearRegression().predict(Xtest)

reg2.score(Xtest, Ytest)
plt.figure(2)


plt.scatter(Xtrain, Ytrain, 'r')

plt.scatter(Xtest, Ytest, 'g')

plt.plot(Xtrain,reg2.predict(Xtrain),color='k')

plt.plot(Xtest,reg2.predict(Xtest),color='b')

# Need to calulate average MSE^2

from sklearn.preprocessing import PolynomialFeatures

from sklearn import linear_model
plt.figure(3)


plt.scatter(Xtrain, Ytrain, 'r')

plt.scatter(Xtest, Ytest, 'g')


def polyFeature(degree, X, x_test, Y, poly):
    X_ = poly.fit_transform(X)
    predict_ = poly.fit_transform(x_test)
    clf = linear_model.LinearRegression()
    clf.fit(X_, Y)
    print clf.predict(predict_)
    return clf.predict(predict_)


# PART 3
for i in range(2,7):
    poly = PolynomialFeatures(degree=i)
    prediction = polyFeature(i,Xtrain,Xtest,Ytrain, poly)
    plt.plot(Xtest, prediction, color='k')







