# %%
import matplotlib.pyplot as plt
import pandas as pd

# %%
def draw_result(file_name, y_lim, y_lim2):
    result = pd.read_csv(file_name)
    avg = result.loc[result["Run"] == "avg"].drop(["Run"], axis=1)
    plt.figure(figsize=(8, 6))
    plt.title(file_name[: file_name.index(".")])
    plt.xlim(0, 1000)
    plt.ylim(y_lim - 1, y_lim2 + 1)
    plt.plot(range(1001), avg.values.reshape(1001), lw=2)
    plt.savefig(f"./result/{file_name[: file_name.index('.')]}.jpg", dpi=300)
    plt.show()


# %%
draw_result("onemax-B2D-result.csv", 0, 100)
draw_result("onemax-bit-flip-nb-result.csv", 0, 100)
draw_result("deception-B2D-nb-4n-result.csv", 0, 11)
draw_result("deception-B2D-nb-10n-result.csv", 0, 767)
draw_result("deception-bit-flip-4n-result.csv", 0, 11)
draw_result("deception-bit-flip-10n-result.csv", 0, 767)
