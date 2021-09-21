# %%
import matplotlib.pyplot as plt
import numpy as np


def draw(file_name):
    with open(file_name + ".txt") as f:
        data = f.read().strip().split("\n")[4:]

    for i, n in enumerate(data):
        data[i] = float(n.split("\t")[-1])

    plt.plot(data)
    plt.savefig(f"{file_name}.jpg", dpi=300)
    plt.show()


# %%
draw("51_run_avg_CX_2")
draw("51_run_avg_PMX_3")
