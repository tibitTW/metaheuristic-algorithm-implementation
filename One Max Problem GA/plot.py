# %%
import matplotlib.pyplot as plt
import pandas as pd

# %%
def draw_result(file_name, y_lim, y_lim2):
    result = pd.read_csv(file_name)
    avg = result.loc[result["Run"] == "avg"].drop(["Run"], axis=1)
    plt.figure(figsize=(8, 6))
    plt.title(file_name[: file_name.index(".")] + " of 51 run avg")
    plt.xlabel("Iteration")
    plt.ylabel("fitness")
    plt.xlim(0, 1000)
    plt.ylim(y_lim - 1, y_lim2 + 1)
    plt.plot(range(1001), avg.values.reshape(1001), lw=2)
    plt.savefig(f"{file_name[: file_name.index('.')]}.jpg", dpi=300)
    plt.show()


# %%
draw_result("result.csv", 0, 100)
