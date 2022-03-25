import csv
import numpy as np
def load_data_set(file_name):

    data_mat = []
    with open(file_name) as file_obj:
        Voice_GET = csv.DictReader(file_obj)
        list_class = []
        # headf
        label_name = list(Voice_GET.fieldnames)
        num = len(label_name) - 1

        for l in Voice_GET.reader:
            data_mat.append(l[:num])
            if l[-1] == 'male':gender = 1
            else :gender=0
            list_class.append(gender)

        # average
        data_mat = np.array(data_mat).astype(float)
        count_v = np.count_nonzero(data_mat, axis=0)
        sum_v = np.sum(data_mat, axis=0)
        mean_v = sum_v/ count_v

        # 数据缺失的地方 用 平均值填充
        for row in range(len(data_mat)):
            for col in range(num):
                if data_mat[row][col] == 0.0:
                    data_mat[row][col] = mean_v[col]

        # 连续型的数据特征值离散化处理

        diff_vector = (data_mat.max(axis=0) - data_mat.min(axis=0))/9

        min_vector = data_mat.min(axis=0)
        max_vector = data_mat.max(axis=0)
        new_data_set = []
        for i in range(len(data_mat)):
            line = np.array((data_mat[i] - min_vector) / diff_vector).astype(int)
            new_data_set.append(line)

        # 我们这里按照7：3划分训练集和测试集
        test_set = list(range(len(new_data_set)))
        train_set = []
        for i in range(2000):
            random_index = int(np.random.uniform(0, len(test_set)))
            train_set.append(test_set[random_index])
            del test_set[random_index]

        # 训练数据集
        # Train_mat：离散化的训练数据集
        #  Train_classes： 训练数据集所属的分类
        Train_Mat = []
        Train_Classes = []
        for index in train_set:
            Train_Mat.append(new_data_set[index])
            Train_Classes.append(list_class[index])

        # 测试数据集
        #Test_mat：离散化的测试数据集
        #Test_classes：测试数据集所述的分类
        Test_Mat = []
        Test_Classes = []
        for index in test_set:
            Test_Mat.append(new_data_set[index])
            Test_Classes.append(list_class[index])

    return Train_Mat, Train_Classes, Test_Mat, Test_Classes, label_name

    #label_name：特征的名称
