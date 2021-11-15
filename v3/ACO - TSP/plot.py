# %%
import matplotlib.pyplot as plt

# %%
with open("result_avg.txt") as f:
    res = f.read()

res = list(map(float, res.strip().split("\n")))
# %%
plt.figure(figsize=(12, 8))
plt.plot(res)
plt.title("51run convergence")
plt.savefig("con.jpg", dpi=300)
plt.show()
