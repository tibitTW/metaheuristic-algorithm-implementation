# ACO, Ant Colony Optimization

## Process

- [x] turn dataset to city distance relation matrix (*passed)
    - [x] read location to `cityLocatoin[][]`
    - [x] turn `cityLocation[][]` to **relation matrix**
- [x] ants (initialize tables)
    - [x] `AntsCurrentCity[]`
    - [x] `AntsPathLengthAccumulation[]`
    - [x] `AntsVisitedCity[POP_SIZE][CITY_DIM]`
- [x] create pheromone relation matrix (*failed :<)
- [ ] in iteration:
    - [x] solution construction (*most complex part)
    - [ ] update pheromone
    - [ ] local search (optional)

# 原理

