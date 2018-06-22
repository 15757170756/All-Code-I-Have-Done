#!/usr/bin/python3
# -*-coding: utf-8-*-

# Writen By Wangru
# Please be kind to my sweet code

import numpy as np
from numpy import *
import struct
import matplotlib.pyplot as plt
from PIL import Image

# training data
train_images_idx3_ubyte_file = '../mnist_data/train-images.idx3-ubyte'
# training labels
train_labels_idx1_ubyte_file = '../mnist_data/train-labels.idx1-ubyte'

# testing data
test_images_idx3_ubyte_file = '../mnist_data/t10k-images.idx3-ubyte'
# testing labels
test_labels_idx1_ubyte_file = '../mnist_data/t10k-labels.idx1-ubyte'

def load_images(image_file):
    """
    [type]           [value]     [description]
    32 bit integer               magic number
    32 bit integer   60000       number of images
    32 bit integer   28          rows

    32 bit integer   28          colswangru
    unsigned byte    ??          pixel
    ....
    unsigned byte    ??          pixel
    pixel values are 0 to 255
    """
    bin_data = open(image_file, 'rb').read()

    # resolve magic_number, num_imgs, rows, cols
    offset = 0
    # '>iiii' means 32 bit integer
    fmt_header = '>iiii'
    magic_number, num_imgs, rows, cols = struct.unpack_from(fmt_header, bin_data, offset)

    size = rows * cols
    offset += struct.calcsize(fmt_header)

    # size of an img '28*28B'
    fmt_img = '>' + str(size) + 'B'
    images = np.empty((num_imgs, rows, cols))
    for i in range(num_imgs):
        images[i] = np.array(struct.unpack_from(fmt_img, bin_data, offset)).reshape(rows, cols)
        offset += struct.calcsize(fmt_img)

    return images

def load_labels(labels_file):
    """
    [type]            [value]          [description]
    32 bit integer                     magic number
    32 bit integer    60000            number of items
    unsigned byte     ??               label
    ....
    The label values are 0 to 9

    """
    bin_data = open(labels_file, 'rb').read()

    # 解析文件头信息，依次为魔数，图片数量，标签
    offset = 0
    fmt_header = '>ii'
    magic_number, num_imgs = struct.unpack_from(fmt_header, bin_data)
    offset += struct.calcsize(fmt_header)

    fmt_label = '>B'  # 一个标签有多少个字节
    labels = np.empty(num_imgs)

    for i in range(num_imgs):
        labels[i] = np.array(struct.unpack_from(fmt_label, bin_data, offset))
        offset += struct.calcsize(fmt_label)

    return labels

def feedforward_net(w, x, b):
    out = np.dot(w, x) + b
    return out

def softmax(x):
    x = x - np.max(x)
    exp_x = np.exp(x)
    return exp_x / np.sum(exp_x)

def predict(w, img, b):
    out1 = feedforward_net(w, img, b)
    score = softmax(out1)
    pre_val = np.argmax(score)
    return score, pre_val


def back_propogation(w, img, b, label):

    [score, pre_val] = predict(w, img, b)

    der_score_out = score
    der_score_out[label] -= 1
    der_w = der_score_out * img.T
    der_b = der_score_out
    if pre_val != label:
        flag = 0
    else:
        flag = 1

    return der_w, der_b, flag

def mnist_train(iter_time, learn_rate):
    # read the mnist data

    train_images = load_images(train_images_idx3_ubyte_file)
    train_labels = load_labels(train_labels_idx1_ubyte_file)

    [num_images, row, col] = train_images.shape

    # the number of neuron
    num_neuron = 10

    # initiate the weight
    # w = np.random.rand(num_neuron, row*col)
    # b = np.random.rand(num_neuron, 1)
    w = np.random.randn(num_neuron, row * col)/sqrt(row * col)
    b = np.random.randn(num_neuron, 1)/sqrt(num_neuron)

    # training by SGD (back propagation)
    cnt = 0
    accurate = 0

    for i in range(iter_time):
        i = i % 60000
        img = train_images[i].reshape(row * col, 1)
        label = int(train_labels[i])
        [der_w, der_b, flag] = back_propogation(w, img, b, label)
        accurate += flag
        cnt += 1
        if cnt % 1000 == 0 and cnt / 1000 != 0:
            print(accurate)
            accuracy = accurate * 1.0 / 1000
            print('the accuracy of %dth iteration is: %f' % (cnt / 100, accuracy))
            accurate = 0
        if cnt % 20000 == 0 and cnt / 20000 != 0:
            learn_rate = learn_rate * 0.1
        w = w - learn_rate * der_w  # 注意是-，随机梯度下降法权重的更新是朝着梯度的反方向走的
        b = b - learn_rate * der_b

    return w, b



if __name__ == '__main__':

    # the iteration time of training
    iter_time = 60000
    # the learning rate
    learn_rate = 0.01

    # training mnist
    [w, b] = mnist_train(iter_time, learn_rate)

    # test mnist
    test_images = load_images(test_images_idx3_ubyte_file)
    test_labels = load_labels(test_labels_idx1_ubyte_file)
    cnt = 0
    [num_test_image, row, col] = test_images.shape
    for i in range(num_test_image):
        img = test_images[i].reshape(row * col, 1)
        label = int(test_labels[i])
        [score, pre_val] = predict(w, img, b)
        if pre_val == label:
            cnt += 1
        # print('the label is %d, and the predict value is %d'% (label, pre_val))
    accuracy = cnt * 1.0 / num_test_image
    print('the test accuracy is %f', accuracy)





