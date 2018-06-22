#!/usr/bin/python3
# -*-coding: utf-8-*-
import numpy as np
from numpy import *
import struct
import time
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

# def ReLU(x):
#     return np.maximum(x, 0)

def sigmoid(x):
    # print(1.0 / (1 + np.exp(-x)))
    return 1.0 / (1 + np.exp(-x))

def der_sigmoid(x):
    return np.multiply(x, 1-x)

def feedforward_net(w, x, b):

    re = np.dot(w, x) + b
    out = sigmoid(re)

    return out

def softmax(x):
    x = x - np.max(x)
    exp_x = np.exp(x)
    return exp_x / np.sum(exp_x)

def predict(w0, w1, img, b0, b1):
    out0 = feedforward_net(w0, img, b0)
    out1 = np.dot(w1, out0) + b1
    score = softmax(out1)
    pre_val = np.argmax(score)
    return pre_val


def back_propogation(w0, w1, img, b0, b1, label):

    # start1 = time.clock()
    out0 = feedforward_net(w0, img, b0)
    out1 = np.dot(w1, out0) + b1
    score = softmax(out1)
    pre_val = np.argmax(score)

    # break1 = time.clock()
    # print('the feedforward time is: %f' % (break1 - start1))

    dloss_out1 = score
    dloss_out1[label] -= 1
    dw1 = dloss_out1 * out0.T
    db1 = dloss_out1

    dloss_out0 = np.dot(w1.T, dloss_out1)
    dloss_re0 = np.multiply(dloss_out0, der_sigmoid(out0))
    dw0 = dloss_re0 * img.T
    db0 = dloss_re0
    # break2 =  time.clock()
    # print('the bp time is: %f' % (break2 - break1))

    return dw0, db0, dw1, db1

def mnist_test(test_images, test_labels, w0, w1, b0, b1):

    cnt = 0
    [num_test_image, row, col] = test_images.shape
    for i in range(num_test_image):
        img = test_images[i].reshape(row * col, 1) * 1.0 / 255
        label = int(test_labels[i])
        label = int(label)
        pre_val = predict(w0, w1, img, b0, b1)
        if pre_val == label:
            cnt += 1
    accuracy = cnt * 1.0 / num_test_image
    return accuracy


def mnist_train(epochs, mini_batch_size, learn_rate):
    # read the mnist data

    images = load_images(train_images_idx3_ubyte_file)
    labels = load_labels(train_labels_idx1_ubyte_file)

    [num_images, row, col] = images.shape

    # the number of neuron
    num_neuron = [500, 10]

    train_images = images[0:30000]
    train_labels = labels[0:30000]
    num_train = len(train_images)

    verified_images = images[50001:50201]
    verified_labels = labels[50001:50201]

    # initiate the weight
    # b0 = np.random.randn(num_neuron[0], 1)
    # w0 = np.random.randn(num_neuron[0], row * col)
    # b1 = np.random.randn(num_neuron[1], 1)
    # w1 = np.random.randn(num_neuron[1], num_neuron[0])

    w0 = np.random.randn(num_neuron[0], row * col) / sqrt(num_neuron[0])
    w1 = np.random.randn(num_neuron[1], num_neuron[0]) / sqrt(num_neuron[1])

    b0 = mat(zeros((num_neuron[0], 1)))
    b1 = mat(zeros((num_neuron[1], 1)))

    dw0 = mat(zeros((num_neuron[0], row * col)))
    db0 = mat(zeros((num_neuron[0], 1)))
    dw1 = mat(zeros((num_neuron[1], num_neuron[0])))
    db1 = mat(zeros((num_neuron[1], 1)))

    # training by SGD (back propagation)
    for j in range(epochs):
        for k in range(0, num_train, mini_batch_size):
            mini_batches_img = train_images[k: k + mini_batch_size]
            mini_batches_label = train_labels[k: k + mini_batch_size]
            for i in range(mini_batch_size):
                img = mini_batches_img[i].reshape(row * col, 1) * 1.0 / 255
                label = int(mini_batches_label[i])
                [dw0, db0, dw1, db1] = back_propogation(w0, w1, img, b0, b1, label)
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

            # start = time.clock()
            accuracy = mnist_test(verified_images, verified_labels, w0, w1, b0, b1)
            # end = time.clock()
            # print('the trest time is %f' % (end - start))
            print('the accuracy of %dth iteration in %dth epochs is: %f' % (k/mini_batch_size+1, j, accuracy))

        if (j + 1) % 10 == 0:
            learn_rate = learn_rate * 0.1

        if (j + 1) % 15 == 0:
            learn_rate = learn_rate * 0.1




    return w0, w1, b0, b1



if __name__ == '__main__':

    # the parameters of training
    epochs = 20
    mini_batch_size = 10
    learn_rate = 0.01

    # training mnist
    [w0, w1, b0, b1] = mnist_train(epochs, mini_batch_size, learn_rate)

    # test mnist
    test_images = load_images(test_images_idx3_ubyte_file)
    test_labels = load_labels(test_labels_idx1_ubyte_file)
    accuracy = mnist_test(test_images, test_labels, w0, w1, b0, b1)
    print('the test accuracy is %f' % accuracy)





