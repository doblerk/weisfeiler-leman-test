#include <set>
#include <iostream>
#include <unordered_map>
#include <boost/graph/adjacency_list.hpp>
#include "RadixSort.h"
#include "WeisfeilerLeman.h"


WeisfeilerLeman::WeisfeilerLeman() {}

void WeisfeilerLeman::set_curr_graph_labels(Graph& g1, Graph& g2, std::vector<int>& curr_g1_labels, std::vector<int>& curr_g2_labels) {
    for (int i = 0; i < curr_g1_labels.size(); i++) {curr_g1_labels[i] = g1[i].label;}
    for (int i = 0; i < curr_g2_labels.size(); i++) {curr_g2_labels[i] = g2[i].label;}
}

void WeisfeilerLeman::set_curr_multimap_labels(Graph& g, std::multimap<int, int>& multimap_labels) {
    auto [v_begin, v_end] = boost::vertices(g);
    for (auto v = v_begin; v != v_end; ++v) {
        // iterate through adjacent vertices
        std::string str = "";
        auto [ai, ai_end] = boost::adjacent_vertices(*v, g);
        for (; ai != ai_end; ++ai) {
            str += std::to_string(g[*ai].label);
        }
        // sort the string
        std::sort(str.begin(), str.end());
        // convert it back to int
        int sorted_int = std::stoi(str);

        multimap_labels.insert(std::pair<int, int>(g[*v].label, sorted_int));
    }
}

bool WeisfeilerLeman::calc_step0(Graph& g1, Graph& g2) {
    int num_vertices_g1, num_vertices_g2;
    int num_edges_g1, num_edges_g2;

    num_vertices_g1 = boost::num_vertices(g1);
    num_vertices_g2 = boost::num_vertices(g2);

    num_edges_g1 = boost::num_edges(g1);
    num_edges_g2 = boost::num_edges(g2);

    if (num_vertices_g1 != num_edges_g2 || num_edges_g1 != num_edges_g2) {
        return false;
    }
    return true;
}

std::multimap<int, int> WeisfeilerLeman::calc_step1(Graph& g1, Graph& g2) {
    std::multimap<int, int> multimap_labels;
    set_curr_multimap_labels(g1, multimap_labels);
    set_curr_multimap_labels(g2, multimap_labels);
    return multimap_labels;
}

std::multimap<int, int> WeisfeilerLeman::calc_step2(std::multimap<int, int>& multimap_labels) {
    std::multimap<int, int> multimap_labels_sorted;
    for (const auto& [key, _] : multimap_labels) {
        // Skip already processed keys
        static int last_processed_key = -1;
        if (key == last_processed_key) continue;
        last_processed_key = key;

        // Retrieve all values for the current key
        std::vector<int> tmp_labels;
        auto range = multimap_labels.equal_range(key);
        for (auto it = range.first; it != range.second; ++it) {
            tmp_labels.push_back(it->second);
        }
        
        if (tmp_labels.size() > 1) {
            std::vector<int> labels_sorted(tmp_labels.size());
            radix_sort(tmp_labels, labels_sorted);
            for (int i = 0; i < labels_sorted.size(); i++) {
                multimap_labels_sorted.insert(std::pair<int, int>(key, labels_sorted[i]));
            }
        } else {
            multimap_labels_sorted.insert(std::pair<int, int>(key, tmp_labels[0]));
        }
    }
    return multimap_labels_sorted;
}

std::map<int, int> WeisfeilerLeman::calc_step3(std::multimap<int, int>& multimap_labels_sorted) {
    int next_new_label = (--multimap_labels_sorted.end())->first + 1;
    std::map<int, int> map_labels_updated;
    for (auto& [key, value] : multimap_labels_sorted) {
        map_labels_updated.insert(std::pair<int, int>(value, next_new_label));
        next_new_label++;
    }
    return map_labels_updated;
}

void WeisfeilerLeman::calc_step4(Graph& g1, Graph& g2, std::vector<int>& curr_g1_labels, std::vector<int>& curr_g2_labels, std::map<int, int> map_labels_updated) {
    int tmp_label_g1, tmp_label_g2;
    for (int i = 0; i < boost::num_vertices(g1); i++) {
        tmp_label_g1 = curr_g1_labels[i];
        tmp_label_g2 = curr_g2_labels[i];
        g1[i].label = map_labels_updated[tmp_label_g1];
        g2[i].label = map_labels_updated[tmp_label_g2];
    }
}

bool WeisfeilerLeman::check_termination(Graph& g1, Graph& g2) {
    std::vector<int> g1_relabeled(boost::num_vertices(g1)), g2_relabeled(boost::num_vertices(g1));
    for (int i = 0; i < g1_relabeled.size(); i++) {
        g1_relabeled[i] = g1[i].label;
        g2_relabeled[i] = g2[i].label;
    }

    if (!(std::equal(g1_relabeled.begin(), g1_relabeled.end(), g2_relabeled.begin()))) {
        return false;
    }
    return true;
}