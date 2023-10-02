#include "solution.hpp"

static int getSumOfDigits(int n) {
  int sum = 0;
  while (n != 0) {
    sum = sum + n % 10;
    n = n / 10;
  }
  return sum;
}


#ifndef SOLUTION
#  define SOLUTION 1
#endif

#if SOLUTION == 0
// Baseline.

int solution(const hash_map_t *hash_map, const std::vector<int> &lookups) {
  int result = 0;

  for (int val : lookups) {
    if (hash_map->find(val))
      result += getSumOfDigits(val);
  }

  return result;
}


#elif SOLUTION == 1
// My solution.


int solution(const hash_map_t *hash_map, const std::vector<int> &lookups)
{
  int result = 0;

  if (lookups.size() == 0)
  {
    return result;
  }

  constexpr std::size_t block_size {16};

  std::size_t i {0};
  for (; i < lookups.size() - block_size; i += 16)
  {
    // Prefetch a bunch of values.
    for (int j = 0; j < block_size; ++j)
    {
      hash_map->prefetch(lookups[i + j]);
    }

    // Compute on the prefetched data.
    for (int j = 0; j < block_size; ++j)
    {
      int val = lookups[i+j];
      if (hash_map->find(val))
      {
        result += getSumOfDigits(val);
      }
    }
  }

  // Serial loop for the last <16 elements.
  for (; i < lookups.size(); i++)
  {
    int val = lookups[i];
    if (hash_map->find(val))
    {
      result += getSumOfDigits(val);
    }
  }

  return result;
}


#elif SOLUTION == 2
// Facit.

// TODO Still the baseline implementation.

int solution(const hash_map_t *hash_map, const std::vector<int> &lookups) {
  int result = 0;

  for (int val : lookups) {
    if (hash_map->find(val))
      result += getSumOfDigits(val);
  }

  return result;
}

#else
#  pragma error("Unknown solution. Valid values are 0 through 2.")
#endif

