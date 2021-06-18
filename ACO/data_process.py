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

# %%

city_order_list = [
    1,
    22,
    8,
    26,
    31,
    28,
    3,
    36,
    35,
    20,
    2,
    29,
    21,
    16,
    50,
    34,
    30,
    9,
    49,
    10,
    39,
    33,
    45,
    15,
    44,
    42,
    40,
    19,
    41,
    13,
    25,
    14,
    24,
    43,
    7,
    23,
    48,
    6,
    27,
    51,
    46,
    12,
    47,
    18,
    4,
    17,
    37,
    5,
    38,
    11,
    32,
]
city_order_list
# %%
