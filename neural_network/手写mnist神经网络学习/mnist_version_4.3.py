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

def ReLU(x):
    # return np.maximum(x, 0)
    return x

def der_ReLU(x):
    x[x > 0] = 1
    x[x <= 0] = 1
    return x


def softmax(x):
    x = x - np.max(x)
    exp_x = np.exp(x)
    return exp_x / np.sum(exp_x)

def predict(w0, w1, img, b0, b1, stride1, stride2, cov_size, pool_size):

    num_filters = len(w0)
    row, col = img.shape
    cov_row = int((row - cov_size) / stride1 + 1)
    cov_col = int((col - cov_size) / stride1 + 1)
    pool_row = int((cov_row - pool_size) / stride2 + 1)
    pool_col = int((cov_col - pool_size) / stride2 + 1)

    cov1 = np.zeros((num_filters, cov_row, cov_col))
    pool1 = np.zeros((num_filters, pool_row, pool_col))

    # concolution
    for k in range(num_filters):
        for i in range(cov_row):
            for j in range(cov_col):
                temp = np.multiply(w0[k], img[i*stride1:i*stride1 + cov_size, j*stride1:j*stride1 + cov_size])
                cov1[k][i, j] = sum(sum(temp)) + b0[k]

    conv1_out = ReLU(cov1)

    # mean pooling
    for k in range(num_filters):
        for i in range(pool_row):
            for j in range(pool_col):
                temp = np.mean(conv1_out[k][i*stride2:i*stride2+pool_size, j*stride2:j*stride2+pool_size])
                pool1[k][i, j] = temp

    # fully connected layer
    pool1 = pool1.reshape(pool_row * pool_col * num_filters, 1)
    fc = np.dot(w1, pool1) + b1
    score = softmax(fc)
    pre_val = np.argmax(score)
    return pre_val



def back_propogation(w0, w1, img, b0, b1, label, stride1, stride2, cov_size, pool_size):

    num_filters = len(w0)
    row, col = img.shape
    cov_row = int((row - cov_size) / stride1 + 1)
    cov_col = int((col - cov_size) / stride1 + 1)
    pool_row = int((cov_row - pool_size) / stride2 + 1)
    pool_col = int((cov_col - pool_size) / stride2 + 1)

    cov1 = np.zeros((num_filters, cov_row, cov_col))
    dloss_conv1_out = np.zeros((num_filters, cov_row, cov_col))
    pool1 = np.zeros((num_filters, pool_row, pool_col))
    dw0 = np.zeros((num_filters, cov_size, cov_size))
    db0 = np.zeros((num_filters, 1))

    # concolution
    for k in range(num_filters):
        for i in range(cov_row):
            for j in range(cov_col):
                temp = np.multiply(w0[k], img[i*stride1:i*stride1 + cov_size, j*stride1:j*stride1 + cov_size])
                cov1[k][i, j] = sum(sum(temp)) + b0[k]

    conv1_out = ReLU(cov1)

    # pooling
    for k in range(num_filters):
        for i in range(pool_row):
            for j in range(pool_col):
                temp = np.mean(conv1_out[k][i*stride2:i*stride2+pool_size, j*stride2:j*stride2+pool_size])
                pool1[k][i, j] = temp


    # fully connected layer
    pool1 = pool1.reshape(pool_row * pool_col * num_filters, 1)
    fc = np.dot(w1, pool1) + b1
    score = softmax(fc)

    dloss_out = score
    dloss_out[label] -= 1
    dw1 = dloss_out * pool1.T
    db1 = dloss_out

    dloss_pool1 = np.dot(w1.T, dloss_out)

    # reshape and derivate mean pooling
    dloss_pool1 = dloss_pool1.reshape(num_filters, pool_row, pool_col)
    dloss_pool1 = dloss_pool1 * 1.0 / 4

    for k in range(num_filters):
        for i in range(pool_row):
            for j in range(pool_col):
                dloss_conv1_out[k][i*stride2: i*stride2+pool_size, j*stride2: j*stride2+pool_size] = dloss_pool1[k][i, j]

    # dloss_cov1 = np.multiply(der_ReLU(conv1_out), dloss_conv1_out)
    dloss_cov1 = dloss_conv1_out

    for k in range(num_filters):
        for i in range(0, cov_size, stride1):
            for j in range(0, cov_size, stride1):
                x = img[i*stride1: i*stride1 + cov_row, j*stride1: j*stride1 + cov_col]
                temp = np.multiply(x, dloss_cov1[k])
                dw0[k, i, j] = sum(sum(temp))
        db0[k] = sum(sum(dloss_cov1[k]))

    return dw0, dw1,  db0, db1

def mnist_test(test_images, test_labels, w0, w1, b0, b1, stride1, stride2, cov_size, pool_size):

    cnt = 0
    num_test_image = len(test_images)
    for i in range(num_test_image):
        img = test_images[i] * 1.0 / 255
        label = int(test_labels[i])
        label = int(label)
        pre_val = predict(w0, w1, img, b0, b1, stride1, stride2, cov_size, pool_size)
        if pre_val == label:
            cnt += 1
    accuracy = cnt * 1.0 / num_test_image
    return accuracy


def mnist_train(epochs, mini_batch_size, learn_rate, cov_size, pool_size, stride1, stride2):
    # read the mnist data

    images = load_images(train_images_idx3_ubyte_file)
    labels = load_labels(train_labels_idx1_ubyte_file)

    [num_images, row, col] = images.shape

    # the number of neuron
    num_neuron = [20, 10]

    train_images = images[0:32000]
    train_labels = labels[0:32000]
    num_train = len(train_images)

    verified_images = images[50001:50101]
    verified_labels = labels[50001:50101]

    # initiate the weight
    # b0 = np.random.randn(num_neuron[0], 1)
    # w0 = np.random.randn(num_neuron[0], row * col)
    # b1 = np.random.randn(num_neuron[1], 1)
    # w1 = np.random.randn(num_neuron[1], num_neuron[0])


    cov_row = int((row - cov_size) / stride1 + 1)
    cov_col = int((col - cov_size) / stride1 + 1)
    pool_row = int((cov_row - pool_size) / stride2 + 1)
    pool_col = int((cov_col - pool_size) / stride2 + 1)


    w0 = np.random.randn(num_neuron[0], cov_size, cov_size) / sqrt(num_neuron[0]/2)
    w1 = np.random.randn(num_neuron[1], pool_row * pool_col * num_neuron[0]) / sqrt(num_neuron[1]/2)
    b0 = np.random.randn(num_neuron[0], 1) / sqrt(num_neuron[0]/2)
    b1 = np.random.randn(num_neuron[1], 1) / sqrt(num_neuron[1]/2)


    dw0 = np.zeros((num_neuron[0], cov_size, cov_size))
    db0 = np.zeros((num_neuron[0], 1))
    dw1 = np.zeros((num_neuron[1], pool_row * pool_col * num_neuron[0]))
    db1 = np.zeros((num_neuron[1], 1))


    # training by SGD (back propagation)
    for j in range(epochs):
        if j == 2:
            learn_rate = learn_rate * 0.1
        for k in range(0, num_train, mini_batch_size):
            mini_batches_img = train_images[k: k + mini_batch_size]
            mini_batches_label = train_labels[k: k + mini_batch_size]
            for i in range(mini_batch_size):
                img = mini_batches_img[i] * 1.0 / 255
                label = int(mini_batches_label[i])
                [dw0, dw1, db0, db1] = back_propogation(w0, w1, img, b0, b1, label, stride1, stride2, cov_size, pool_size)
                dw0 += dw0
                db0 += db0
                dw1 += dw1
                db1 += db1

            dw0 = dw0 * 1.0 / mini_batch_size
            db0 = db0 * 1.0 / mini_batch_size
            dw1 = dw1 * 1.0 / mini_batch_size
            db1 = db1 * 1.0 / mini_batch_size

            w0 = w0 - learn_rate * dw0  # 注意是-，随机梯度下降法权重的更新是朝着梯度的反方向走的
            b0 = b0 - learn_rate * db0
            w1 = w1 - learn_rate * dw1
            b1 = b1 - learn_rate * db1

            # print(k)
            if ((k + 1) % 100 == 0):
                num = num_train / mini_batch_size
                accuracy = mnist_test(verified_images, verified_labels, w0, w1, b0, b1, stride1, stride2, cov_size,
                                      pool_size)
                # print('the accuracy of %dth iteration in %dth epochs is: %f' % (k/mini_batch_size+1, j, accuracy))
                print('%d / %d, the accuracy  in %dth epochs is: %f' % ((k + 1) / mini_batch_size, num, j, accuracy))

    return w0, w1, b0, b1



if __name__ == '__main__':

    # the parameters of training
    epochs = 3
    mini_batch_size = 1
    learn_rate = 0.01
    stride1 = 1
    stride2 = 2
    cov_size = 9
    pool_size = 2


    # training mnist
    [w0, w1, b0, b1] = mnist_train(epochs, mini_batch_size, learn_rate, cov_size, pool_size, stride1, stride2)

    # test mnist
    test_images = load_images(test_images_idx3_ubyte_file)
    test_labels = load_labels(test_labels_idx1_ubyte_file)
    accuracy = mnist_test(test_images, test_labels, w0, w1, b0, b1, stride1, stride2, cov_size, pool_size)
    print('the test accuracy is %f' % accuracy)





