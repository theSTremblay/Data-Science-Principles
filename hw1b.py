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


plt.figure(1)
plt.title("Scatter Plot 1")


Xtrain_transpose = Xtrain.transpose()
Xtest_transpose = Xtest.transpose()

plt.scatter(Xtrain, Ytrain, c='r', label= 'train')

plt.scatter(Xtest, Ytest, c='y', label= 'test')

plt.legend()
# PART B
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error


reg = LinearRegression(fit_intercept=True).fit(Xtrain, Ytrain)

R_squared_train = reg.score(Xtrain, Ytrain)

reg2 = reg.predict(Xtest)

test_score_R2 = reg.score(reg2, Ytest)
mse_lin = mean_squared_error(reg2, Ytest)
print(test_score_R2)
plt.figure(2)


plt.scatter(Xtrain, Ytrain, c='r', label= 'train')

plt.scatter(Xtest, Ytest, c='y', label= 'test')

plt.plot(Xtrain,reg.predict(Xtrain),color='k')

plt.plot(Xtest,reg.predict(Xtest),color='b')

plt.show()
plt.title("Scatter plot of linear regression line")
plt.legend(loc='upper left')
print("Betas are:" + str(reg.coef_))

# Need to calulate average MSE^2

from sklearn.preprocessing import PolynomialFeatures

from sklearn import linear_model
plt.figure(3)

plt.scatter(Xtrain, Ytrain, c ='r')

plt.scatter(Xtest, Ytest, c= 'y')



def polyFeature(degree, X, x_test, Y, poly, colors):
    X_ = poly.fit_transform(X)

    predictp = poly.fit_transform(x_test)
    clf = linear_model.LinearRegression()
    clf.fit(X_, Y)

    return clf.predict(predictp), clf.coef_

def MLR(X, y, regressor):
    regressor.fit(X, y)
    return regressor

# import statsmodels.api as sm
#
# def OLS_mult(Y, X):
#     model = sm.OLS(Y,X)
#     result = model.fit()
#     print result.summary()

colors= ['b', 'g','r','c','m', 'y', 'k']
from sklearn.preprocessing import PolynomialFeatures
from sklearn.linear_model import Ridge
from sklearn.linear_model import Perceptron
from sklearn.pipeline import make_pipeline
# PART 3
lw = 2

#X = Xtrain[:, np.newaxis]
#X_plot = Xtest[:, np.newaxis]
import operator
from sklearn.metrics import mean_squared_error, r2_score
Xtrain2 = Xtrain
Xtest2 = Xtest
for i in range(2,8):
    polynomial_features = PolynomialFeatures(degree=i)
    x_poly = polynomial_features.fit_transform(Xtrain2)
    x_poly_test = polynomial_features.fit_transform(Xtest2)

    model = LinearRegression()
    model.fit(x_poly, Ytrain)
    y_poly_pred = model.predict(x_poly_test)

    sort_axis = operator.itemgetter(0)
    sorted_zip = sorted(zip(Xtest, y_poly_pred), key=sort_axis)
    x, y_poly_pred = zip(*sorted_zip)
    plt.plot(x, y_poly_pred, color=colors[i-2], label="degree %d" % i)

    rmse = np.sqrt(mean_squared_error(Ytest, y_poly_pred))
    r2 = r2_score(Ytest, y_poly_pred)
    print("Degree " + str(i) + " RMSE: " + str(rmse))
    print("Degree " + str(i) +  " R2: " + str(r2))
    #plt.show()
    # Xtrain2 = Xtrain2[:, np.newaxis]
    # Xtest2 = Xtest[:, np.newaxis]


    # model = make_pipeline(PolynomialFeatures(i), Ridge())
    # model.fit(Xtrain, Ytrain)
    # y_plot = model.predict(Xtest)
    # plt.plot(Xtest, y_plot, color=colors[i-2], linewidth=lw,
    #          label="degree %d" % i)

    # poly = PolynomialFeatures(degree=i)
    # X_ = poly.fit_transform(Xtrain)
    # predict_ = poly.fit_transform(Ytest)
    # regressor = LinearRegression()
    # X_evaluate = poly_feature(Xtrain, i)
    # #OLS_mult(Ytrain, X_evaluate)
    # reg_mult = MLR(X_evaluate, Ytrain, regressor=regressor)
    # coef = reg_mult.coef_
    # X_evaluate_test = poly_feature(Xtest, i)
    #
    # y_value = np.dot( X_evaluate_test, coef.T)
    # #X_evaluate_test = poly_feature(Xtest, i)
    # #y_evaluate_test = reg_mult.predict(X_evaluate_test)
    # plt.plot(Xtest, y_value, color = colors[i]) #regressor.predict(Xtest), color = colors[i])


plt.legend(loc='upper left')
print("0")







