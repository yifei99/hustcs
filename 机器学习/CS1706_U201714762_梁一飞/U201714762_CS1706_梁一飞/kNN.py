from numpy import *
import matplotlib.pyplot as plt
import kNNcalculate


Kvalue=[1,3,5,10,15,30,50,75,90,100]
accurancy=[0,0,0,0,0,0,0,0,0,0]
t=0
for ind, k in enumerate(Kvalue):
    knn = kNNcalculate.kNNcalculate(k)
    knn.create_data_set("train-images.idx3-ubyte",
                    "train-labels.idx1-ubyte",
                    "t10k-images.idx3-ubyte",
                    "t10k-labels.idx1-ubyte")

    count = 0
    total = 10000
    start = 0
    for i in range(start,start+total):
        result = knn.classfy(knn.imgReader.get_test_set()[i],
                knn.imgReader.get_train_set(),
                knn.imgReader.get_train_label())

        if knn.imgReader.get_test_label()[i] == result[0] :
            count += 1
    accurancy[t] =((float(count)/total)*100.0)
    print("for k=",Kvalue[t],"accurancy=",accurancy[t])
    t=t+1
plt.plot(Kvalue, accurancy)
plt.ylabel('Accurancy')
plt.xlabel('k values')
plt.savefig('KNN.png')


