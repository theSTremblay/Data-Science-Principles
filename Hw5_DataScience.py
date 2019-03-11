# imports needed
import numpy as np
import matplotlib.pyplot as plt
from PIL import Image
# setting seed, DON'T modify

def reshape_to_Image(arr):
    w, h = 28,28
    #arr = np.random.randint(255, size=(28 * 28))
    #arr = arr *255
    #img = Image.fromarray(arr.reshape(28, 28), 'RGB')
    arr = arr.reshape(28, 28)
    return arr
np.random.seed(10)
from pylab import rcParams
rcParams['figure.figsize'] = 10, 7

dataset = np.load('ps04b/data.npy')

item_dataset = dataset.item()


Xtrain = item_dataset['Xtrain']
Xtest = item_dataset['Xtest']
Ytrain = item_dataset['Ytrain']
Ytest = item_dataset ['Ytest']

from PIL import Image

sampledX = Xtrain[0:5]

images_array = []

for i in range(0,5):
    plt.figure(i)
    images_array.append(reshape_to_Image(sampledX[i]))
    plt.imshow(images_array[i])


i = 0

# Part B
images_array = []
sampledX = Xtrain[0:900]
sampledY = Ytrain[0:900]



# for i in range(0,900):
#     images_array.append(reshape_to_Image(sampledX[i]))

from sklearn.neighbors import KNeighborsClassifier

KNN_neighbors = [1,3,5,7,9]
test_err_list = []

images_array_np = np.asarray(images_array)
for i in KNN_neighbors:
    neigh = KNeighborsClassifier(n_neighbors=i)
    neigh.fit(Xtrain[0:900],sampledY[0:900])
    neigh.predict(Xtest)
    acc = neigh.score(Xtest,Ytest)
    test_err = 1 - acc
    test_err_list.append(test_err)
plt.figure(10)

plt.bar(KNN_neighbors, test_err_list)
plt.title("K_nearest_neighbors vs test error")
plt.xlabel("# Neighbors")
plt.ylabel("Test error")

# Part C

number_of_training_data = [900,1200,1500,1800,2100,2400,2700]

for i in KNN_neighbors:
    neigh = KNeighborsClassifier(n_neighbors=i)
    test_err_list = []
    for j in number_of_training_data:
        neigh.fit(Xtrain[0:j],Ytrain[0:j])
        neigh.predict(Xtest)
        acc = neigh.score(Xtest,Ytest)
        test_err = 1 - acc
        test_err_list.append(test_err)
    plt.figure()
    plt.plot(number_of_training_data, test_err_list)
    plt.title("K_nearest_neighbors vs test error for " + str(i)+ " neighbors")
    plt.xlabel("# ")
    plt.ylabel("Test error")


plt.show()
i = 0



