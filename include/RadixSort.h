#ifndef RADIXSORT_H
#define RADIXSORT_H

#include <iostream>
#include <algorithm>

void count_sort(std::vector<int>& labels_sorted, 
                std::vector<int>& labels, 
                int& max_element, 
                int& unit_place);

void radix_sort(std::vector<int>& labels, 
                std::vector<int>& labels_sorted);

#endif // RADIXSORT_H