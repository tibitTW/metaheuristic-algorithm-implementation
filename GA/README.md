# Genetic Algorithm

Genetic Algorithm implemented on C.

## Summary

This program uses Genetic Algorithm to solve One Max problem.

## Structure

### Parameters

* `population size` : how many chromosomes in this population
* `chromosome length` : length of all chromosome
* `iteration count` : how many times does selection, crossover and mutation run
* `crossover rate` : chromosomes crossover rate
* `mutation rate` : chromosomes mutation rate

### Algorithm structure

```pseudocode
initialize population[pop_size], fitness[pop_size]

do iteration_count times:
	calculate fitness[pop_size]
	population <- selection(population)
	population <- crossover(population)
	population <- mutation(population)

output best chromosome
```



