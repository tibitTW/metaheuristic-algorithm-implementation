# %%
import matplotlib.pyplot as plt
import pandas as pd

# %%
flipresult = pd.read_csv("flipbit_result.csv")
mean = pd.DataFrame(flipresult.mean(axis=0)).T
mean["runid"] = "avg"

# combine original data and mean
flipresult_with_avg = flipresult.append(mean)
flipresult_with_avg.to_csv("./flipbit_result_with_avg.csv")

fig, axes = plt.subplots(nrows=2, ncols=1, figsize=(10, 16))
for ax in axes:
    ax.set_xlabel("iteration")
    ax.set_ylabel("fitness")
    ax.set_xlim(0, 200)
    ax.set_ylim(0, 100)
axes[0].set_title("result of each run")
axes[1].set_title("average of each run")

for i in range(51):
    flipresult.iloc[i][1:].plot(ax=axes[0], linewidth=1)

axes[1].plot(list(range(201)), mean.loc[:, "0":].values.reshape(201))
plt.savefig("flipbit.jpg", dpi=300)
# %%
binary_numeric = pd.read_csv("binary_numeric_rseult.csv")
mean = pd.DataFrame(binary_numeric.mean(axis=0)).T
mean["runid"] = "avg"

# combine original data and mean
binary_numeric_with_avg = binary_numeric.append(mean)
binary_numeric_with_avg.to_csv("./binary_numeric_rseult_with_avg.csv")

fig, axes = plt.subplots(nrows=2, ncols=1, figsize=(10, 16))
for ax in axes:
    ax.set_xlabel("iteration")
    ax.set_ylabel("fitness")
    ax.set_xlim(0, 200)
    ax.set_ylim(0, 100)
axes[0].set_title("result of each run")
axes[1].set_title("average of each run")

for i in range(51):
    binary_numeric.iloc[i][1:].plot(ax=axes[0], linewidth=1)

axes[1].plot(list(range(201)), mean.loc[:, "0":].values.reshape(201))
plt.savefig("binary_numeric.jpg", dpi=300)
