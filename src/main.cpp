#include <set>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include "RadixSort.h"
#include "WeisfeilerLeman.h"




int main() {
    // Define the graph type with vertex properties
    

    // Create a graph object with 5 vertices
    Graph g1(6), g2(6); 

    // Set the label of each vertex
    g1[0].label = 1;
    g1[1].label = 1;
    g1[2].label = 4;
    g1[3].label = 5;
    g1[4].label = 2;
    g1[5].label = 3;

    g2[0].label = 2;
    g2[1].label = 1;
    g2[2].label = 4;
    g2[3].label = 2;
    g2[4].label = 5;
    g2[5].label = 3;

    // Add edges between the vertices
    boost::add_edge(0, 2, g1); 
    boost::add_edge(1, 2, g1); 
    boost::add_edge(2, 3, g1); 
    boost::add_edge(2, 5, g1);
    boost::add_edge(3, 4, g1); 
    boost::add_edge(3, 5, g1);
    boost::add_edge(4, 5, g1);

    boost::add_edge(0, 5, g2); 
    boost::add_edge(1, 2, g2); 
    boost::add_edge(2, 3, g2); 
    boost::add_edge(2, 4, g2);
    boost::add_edge(2, 5, g2); 
    boost::add_edge(3, 4, g2);
    boost::add_edge(4, 5, g2);

    WeisfeilerLeman isomorphic_test;

    bool maybe_isomorphic = isomorphic_test.calc_step0(g1, g2);
    if (!maybe_isomorphic) {
        std::cout<<"The two graphs are not isomorphic"<<std::endl;
        return 0;
    }

    while (maybe_isomorphic) {

    }

    std::vector<int> curr_g1_labels(6), curr_g2_labels(6);
    std::multimap<int, int> multimap_labels, multimap_labels_sorted;
    std::map<int, int> map_labels_updated;

    isomorphic_test.set_curr_graph_labels(g1, g2, curr_g1_labels, curr_g2_labels);

    multimap_labels = isomorphic_test.calc_step1(g1, g2);

    multimap_labels_sorted = isomorphic_test.calc_step2(multimap_labels);

    map_labels_updated = isomorphic_test.calc_step3(multimap_labels_sorted);

    isomorphic_test.calc_step4(g1, g2, curr_g1_labels, curr_g2_labels, map_labels_updated);

    return 0;
}
