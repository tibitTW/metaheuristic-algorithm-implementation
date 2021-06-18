# %%
import matplotlib
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

# %%
def ack_function_2d(x1: float, x2: float):
    a = 20
    b = 0.2
    c = np.pi * 2
    d = 2

    sum1 = x1 ** 2 + x2 ** 2
    sum2 = np.cos(c * x1) + np.cos(c * x2)

    term1 = -a * np.exp(-b * ((1 / d) * sum1 ** (0.5)))
    term2 = -np.exp((1 / d) * sum2)

    return term1 + term2 + a + np.exp(1)


# %%
plotN = 100
x1 = np.linspace(-20, 20, plotN)
x2 = np.linspace(-20, 20, plotN)
x1, x2 = np.meshgrid(x1, x2)

z = ack_function_2d(x1, x2)

# %%
fig = plt.figure()
ax = Axes3D(fig)
ax.plot_wireframe(x1, x2, z)
plt.show()

# %%
