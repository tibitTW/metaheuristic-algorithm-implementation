# %%
import matplotlib.pyplot as plt
import pandas as pd

CITY_DIM = 51


def load_city_path(file_path) -> list:
    with open(file_path) as f:
        path = f.read()

    path = list(map(int, path.strip().split("\n")))

    return path


def display_city_location():
    for loc in locations:
        x, y = loc
        plt.scatter(x, y, marker="x", c="k")


def display_path_graph(path):
    if max(path) == CITY_DIM:
        path = [pi - 1 for pi in path]

    for i in range(CITY_DIM):
        c1 = locations[path[i]]
        if i == CITY_DIM - 1:
            c2 = locations[path[0]]
        else:
            c2 = locations[path[i + 1]]

        xarr, yarr = zip(*(c1, c2))
        plt.plot(xarr, yarr, c="b")


# load locations
with open("eil51.txt") as f:
    locations = f.read()

locations = tuple(
    tuple(map(int, loc.split(" ")[1:])) for loc in locations.strip().split("\n")
)


# %%
path_opt = load_city_path("./path/path_opt.txt")

plt.figure(figsize=(10, 10))
plt.xlim(0, 70)
plt.ylim(0, 70)

display_path_graph(path_opt)
display_city_location()

plt.show()

# %%
