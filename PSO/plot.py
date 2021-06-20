# %%
import matplotlib.pyplot as plt
import numpy as np

# %%
with open("out.txt") as f:
    data = [list(map(float, l.strip().split("\t"))) for l in f.readlines()]

# %%
for line in data:
    plt.figure(figsize=(5, 5))
    plt.xlim(-40, 40)
    plt.ylim(-40, 40)
    for i in range(0, len(line), 2):
        plt.scatter(line[i], line[i + 1], c="k")
    plt.show()
