#!/usr/bin/python

import pandas as pd
import matplotlib.pyplot as plt
import math
import random

def data_from_function(f, inputs):
    raw = {
        'x': inputs,
        'y': [],
    }
    for x in inputs:
        raw['y'] += [f(x)]

    raw['y'] = sorted(raw['y'])
    return raw

def grange(n, gran):
    out = []
    for i in range(n):
        out += [i*gran]
    return out

def average(array):
    cum = 0
    for x in array:
        cum += x
    return cum/len(array)

def median(array):
    if len(array) % 2 == 0:
        lefty = len(array)//2
        righty = lefty+1
        return average([ array[lefty], array[righty] ])
    else:
        return array[len(array)/2]

def data_from_const(const, input):
    out = {
        'x': input,
        'y': [],
    }
    for i in input:
        out['y'] += [const]
    return out

def rand(x):
    return random.randint(0, math.floor(x))

datapoints = 720
inputs = grange(datapoints, math.pi/360)
raw_data1 = data_from_function(rand, inputs)
raw_data2 = data_from_const(average(raw_data1['y']), inputs)
raw_data3 = data_from_const(median(raw_data1['y']), inputs)

data1 = pd.DataFrame(raw_data1)
data2 = pd.DataFrame(raw_data2)
data3 = pd.DataFrame(raw_data3)
# Plot the data
plt.plot(data1['x'], data1['y'])
plt.plot(data2['x'], data2['y'])
plt.plot(data3['x'], data3['y'])
plt.title('Simple Plot')
plt.xlabel('X-axis Label')
plt.ylabel('Y-axis Label')
plt.show()
