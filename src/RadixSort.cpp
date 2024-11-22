#include <iostream>
#include <algorithm>
#include "RadixSort.h"

void count_sort(std::vector<int>& labels_sorted, std::vector<int>& labels, int& max_element, int& unit_place) {

  // init a vector of length max + 1
  std::vector<int> count_array(max_element + 1, 0);

  // store the count of each unique element based on the unit place
  for (int i = 0; i < labels.size(); i++) {
    count_array[(labels[i] / unit_place) % 10]++;
  }

  // store the cumulative sum of the elements
  for (int i = 1; i < count_array.size(); i++) {
    count_array[i] += count_array[i-1];
  }
  
  // iterate from the end of the input vector
  for (int i = labels.size() - 1; i >= 0; i--) {
    // update
    labels_sorted[count_array[(labels[i] / unit_place) % 10] - 1] = labels[i];
    // update
    count_array[(labels[i] / unit_place) % 10]--;
  }
  
  for (int i = 0; i < labels.size(); i++) {
    labels[i] = labels_sorted[i];
  }

}

void radix_sort(std::vector<int>& labels, std::vector<int>& labels_sorted) {
  // step 1: find largest element
  int max_element = *std::max_element(labels.begin(), labels.end());
  
  // step 2: sort based on unit place
  for (int unit_place = 1; max_element / unit_place > 0; unit_place *= 10) {
    count_sort(labels_sorted, labels, max_element, unit_place);
  }

}