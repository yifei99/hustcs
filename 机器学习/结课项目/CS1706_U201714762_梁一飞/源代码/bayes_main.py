import numpy as np
from voice_bayes_base import load_data_set
import voice_bayes
import csv
import math



def voicebayes():# p1class 样本分类为1的概率  feature0,feature1 分别为0 1的概率


    file_name = 'voice.csv'
    TrainMat, TrainClasses, TestMat, TestClasses, labelname = load_data_set(file_name)

    feature0, feature1, pclass = voice_bayes.natibayes(TrainMat, TrainClasses)
    correct_count = 0.0
    correct_count0 = 0.0
    correct_count1 = 0.0
    count = 0
    count1= 0
    count0= 0


    for i in list(range(len(TestMat))):
        test_vector = TestMat[i]
        result = voice_bayes.classbayes(test_vector, feature0, feature1, pclass)
        if result == TestClasses[i]:
            correct_count += 1
            if result==0 : correct_count0+=1
            else :correct_count1+=1
        print(" the num is {}: reality:{} theory:{}".format(count, result, TestClasses[i]))
        count += 1
        if TestClasses[i]==0:
            count0 +=1
        else :count1+=1
    print(" the total is {}: femalerate:{} malerate:{}".format(correct_count / count,correct_count1 / count1,correct_count0 / count0))

voicebayes()