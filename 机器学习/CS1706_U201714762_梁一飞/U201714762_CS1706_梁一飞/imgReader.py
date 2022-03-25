import os
from numpy import *
'''
 读取图片数据
'''


class TrainDataSet:#创建训练集类
    def __init__(self, train_file, train_label_file, test_file, test_label_file):
        self.train_img_file = train_file
        self.test_img_file = test_file

        self.train_label_file = train_label_file
        self.test_label_file = test_label_file

        self.TRAIN_NUM = 60000
        self.TEST_NUM = 10000

        self.HEIGHT = 28
        self.WIDTH = 28

        self.train_data_set = array([[0 for x in range(0, self.HEIGHT * self.WIDTH)] for y in range(0, self.TRAIN_NUM)])
        self.test_data_set = array([[0 for x in range(0, self.HEIGHT * self.WIDTH)] for y in range(0, self.TEST_NUM)])

        self.train_label_set = ['0' for x in range(0, self.TRAIN_NUM)]
        self.test_label_set = ['0' for x in range(0, self.TEST_NUM)]

    def get_train_set(self):
        return self.train_data_set

    def get_train_label(self):
        return self.train_label_set

    def get_test_set(self):
        return self.test_data_set

    def get_test_label(self):
        return self.test_label_set

    def read_test_img(self):
        fr = open(self.test_img_file, "rb")
        #print (self.test_img_file)
        if fr is "":
            return

        self.skip_header(fr)
        for i in range(0, self.TEST_NUM):
            self.test_data_set[i] = fromstring(fr.read(self.HEIGHT * self.WIDTH), uint8)

    def read_train_img(self):
        fr = open(self.train_img_file, "rb")

        if fr is "":
            return

        self.skip_header(fr)
        for i in range(0, self.TRAIN_NUM):
            self.train_data_set[i] = fromstring(fr.read(self.HEIGHT*self.WIDTH), uint8)

    def read_test_label(self):
        fr = open(self.test_label_file, "rb")
        if fr is "":
            return

        self.skip_header(fr, 8)
        self.test_label_set = fromstring(fr.read(self.TEST_NUM), uint8)

    def read_train_label(self):
        fr = open(self.train_label_file, "rb")
        if fr is "":
            return

        self.skip_header(fr, 8)
        self.train_label_set = fromstring(fr.read(self.TRAIN_NUM), uint8)

    def skip_header(self, fr, offset=16):
        fr.seek(offset, os.SEEK_CUR);