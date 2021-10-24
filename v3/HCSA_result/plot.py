# %%
import numpy as np
import matplotlib.pyplot as plt

# %%
with open("../OMP - HC/out.txt") as f:
    hc_out = np.array(f.read().strip().split(), dtype="float64")
with open("../OMP - SA/out.txt") as f:
    sa_out = np.array(f.read().strip().split(), dtype="float64")

# %%
plt.plot(hc_out)
plt.plot(sa_out)
plt.savefig("result.jpg", dpi=300)
plt.show()

# %%
