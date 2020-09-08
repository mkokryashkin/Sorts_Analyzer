#include <iostream>
#include <random>
#include <utility>

#include "sorts.h"
#include "stat.h"

void generateArray(Stat<int>* begin, Stat<int>* end, size_t mod = 10) 
{
    assert(begin != nullptr);
    assert(end != nullptr);

    for(Stat<int>* current = begin; current != end; ++current)
    {
        *current = rand() % mod;
    }
}

std::pair<int, int>* benchmarkSort(size_t n_samples, AbstractSort<Stat<int>>&& sort)
{
    auto results = new std::pair<int, int>[n_samples]();

    for(size_t current_size = 1; current_size < n_samples; ++current_size) 
    {
        Stat<int>::n_comparisons = 0;
        Stat<int>::n_assignments = 0;

        Stat<int>* array = new Stat<int>[current_size]();
        generateArray(array, array + current_size);
        sort(array, array + current_size);
        results[current_size] = {Stat<int>::n_comparisons, Stat<int>::n_assignments};

        delete[] array;
    }

    return results;
}

int main(int argc, char** argv)
{
    const size_t N_SAMPLES = 100;
    
    auto results = benchmarkSort(N_SAMPLES, InsertionSort<Stat<int>>());

    printf("|  Array size | Comparisons | Assignments |\n");
    for(size_t i = 0; i < N_SAMPLES; ++i) 
    {
        printf("| %11.1d | %11.1d | %11.1d |\n", i, results[i].first, results[i].second);
    }

    delete[] results;
}
