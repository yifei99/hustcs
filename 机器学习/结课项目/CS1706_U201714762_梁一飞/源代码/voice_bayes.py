import numpy as np


def natibayes(train_Matrix, list_classes):#nativebayes fun


    num_train_data = len(train_Matrix)
    num_feature = len(train_Matrix[0])
    # Trainmatrix: 训练样本矩阵
    # Listclasses: 训练样本分类向量
    # 分类为1的样本占比 pclass 样本分类为1的概率
    pclass = sum(list_classes) / float(num_train_data)

    n = 10


    list_classes_1 = []
    train_data_1 = []

    for i in list(range(num_train_data)):
        if list_classes[i] == 1:
            list_classes_1.append(i)
            train_data_1.append(train_Matrix[i])

    # 分类为1 情况下的各特征的概率  feature0,feature1 分别为0 1的概率
    train_data_1 = np.matrix(train_data_1)
    feature1 = {}
    for i in list(range(num_feature)):
        feature_values = np.array(train_data_1[:, i]).flatten()

        feature_values = feature_values.tolist() + list(range(n))
        p = {}
        count = len(feature_values)
        for value in set(feature_values):
            p[value] = np.log(feature_values.count(value) / float(count))
        feature1[i] = p

    # 所有分类下的各特征的概率
    feature0 = {}
    train_matrix = np.matrix(train_Matrix)
    for i in list(range(num_feature)):
        feature_values = np.array(train_matrix[:, i]).flatten()
        feature_values = feature_values.tolist() + list(range(n))
        p = {}
        count = len(feature_values)
        for value in set(feature_values):
            p[value] = np.log(feature_values.count(value) / float(count))
        feature0[i] = p

    return feature0, feature1, pclass #feature0,feature1 分别为0 1的概率


def classbayes(test, feature0, feature1, pclass):
    """
     1 =male 0 =female
    """
    # 计算每个分类的概率
    sum = 0.0
    for i in list(range(len(test))):#test: 要分类的测试向量
        sum += feature1[i][test[i]]#feature1: 类别为1的情况下的概率
        sum -= feature0[i][test[i]] #feature0: 所有分类的情况下的概率
    p1 = np.log(pclass)+sum        #pclass: 任一分类为1的样本概率
    if p1 < 0.5:
        return 0
    else:
        return 1