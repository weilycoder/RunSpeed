import numpy as np

from matplotlib import pyplot as plt

plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False

def read_data(fn: str):
    with open(fn) as f:
        d = f.read()
        t = list(zip(*map(lambda s: tuple(map(float, s.split())), d.strip().split('\n'))))
        return np.array(t[0]), np.array(t[1])

def show(title, *files):
    plt.title(title)
    plt.xlabel('N')
    plt.ylabel('t/us')
    print(sum(map(read_data, files), ()))
    plt.plot(*sum(map(read_data, files), ()))
    plt.show()
