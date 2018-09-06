# simple plotter

import matplotlib
import matplotlib.pyplot as plt
import numpy as np

data = np.genfromtxt('data.dat', unpack=True)

cmap = matplotlib.cm.get_cmap('viridis')
normalize = matplotlib.colors.Normalize(vmin=min(data[2]), vmax=max(data[2]))
colors = [cmap(normalize(value)) for value in data[2]]

plt.scatter(data[0], data[1], color=colors)
plt.show()