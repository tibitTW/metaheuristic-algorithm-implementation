# %%
import matplotlib.pyplot as plt
import pandas as pd

# %%
def draw_result(file_name, y_lim, y_lim2):
    with open(file_name, "r") as f:
        res = f.read().strip().split()

    plt.plot(list(map(float, res)))
    plt.savefig("result.jpg", dpi=600)


# %%
draw_result("result.txt", 0, 100)
