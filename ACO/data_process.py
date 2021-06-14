#%%
import numpy as np
import matplotlib.pyplot as plt

#%%
with open("out.txt") as f:
    data = f.readlines()
for d in data:
    table = d[:-1].strip().split(",")[:-1]
    table = np.array(list(map(float, table))).reshape((5, 5))
    plt.imshow(table, cmap="gray")
    plt.show()

#%%

# map
map = [[37, 52], [49, 49], [52, 64], [20, 26], [40, 30]]

plt.figure(figsize=(10, 10))
for l in map:
    plt.plot(l[0], l[1], "r.")

plt.show()
