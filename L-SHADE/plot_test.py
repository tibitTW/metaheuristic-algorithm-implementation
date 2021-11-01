# %%
import numpy as np
import matplotlib.pyplot as plt

# %%
with open("out.txt") as f:
    res = list(map(float, f.read().strip().split()))

# %%
plt.hist(res)
