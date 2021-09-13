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
- [x] in iteration:
    - [x] solution construction (*most complex part)
    - [x] update pheromone
    - [ ] local search (optional)

# Todo List

- [ ] 檢查邏輯錯誤
- [ ] 增加 log





