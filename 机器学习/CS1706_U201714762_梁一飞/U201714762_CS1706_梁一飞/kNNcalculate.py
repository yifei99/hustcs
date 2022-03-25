from numpy import *
import operator
import kNNBase
import imgReader


class kNNcalculate(kNNBase.KnnBase):
    def __init__(self, kval):
        kNNBase.KnnBase.__init__(self)
        self.k = kval
        self.imgReader = ""

    def create_data_set(self, train_images_file, train_label_file, test_images_file, test_label_file):#创建数据集
        self.imgReader = imgReader.TrainDataSet(train_images_file, train_label_file, test_images_file, test_label_file)
        self.imgReader.read_train_img()
        self.imgReader.read_train_label()
        self.imgReader.read_test_img()
        self.imgReader.read_test_label()

    def classfy(self, inX, trainset, labels):#数据处理
        dataSetSize = len(trainset)
        diffMat = tile(inX, (dataSetSize, 1)) - trainset
        sqDiffMat = diffMat ** 2
        sqDistance = sqDiffMat.sum(axis=1)
        distances = sqDistance ** 0.5
        sortedDistanceIndicies = distances.argsort()
        classCount = {}
        for i in range(self.k):#k邻近处理
            voteILabel = labels[sortedDistanceIndicies[i]]
            classCount[voteILabel] = classCount.get(voteILabel, 0) + 1
        sortedClassCount = sorted(classCount.items(),
                                  key=operator.itemgetter(1),
                                  reverse=True)
        return sortedClassCount[0]
