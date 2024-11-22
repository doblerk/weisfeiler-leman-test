#ifndef WEISFEILERLEMAN_H
#define WEISFEILERLEMAN_H

#include <set>
#include <iostream>
#include <unordered_map>
#include <boost/graph/adjacency_list.hpp>

struct VertexProperties {
    int label;
};

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexProperties> Graph;

class WeisfeilerLeman {

    public:

        WeisfeilerLeman();
        void set_curr_graph_labels(Graph& g1, Graph& g2, std::vector<int>& curr_g1_labels, std::vector<int>& curr_g2_labels);
        void set_curr_multimap_labels(Graph& g, std::multimap<int, int>& multimap_labels);
        bool calc_step0(Graph &g1, Graph &g2);
        std::multimap<int, int> calc_step1(Graph& g1, Graph& g2);
        std::multimap<int, int> calc_step2(std::multimap<int, int>& multimap_labels);
        std::map<int, int> calc_step3(std::multimap<int, int>& multi_map_labels_sorted);
        void calc_step4(Graph& g1, Graph& g2, std::vector<int>& curr_g1_labels, std::vector<int>& curr_g2_labels, std::map<int, int> map_labels_updated);
        bool check_termination(Graph& g1, Graph& g2);

};


#endif // WEISFEILERLEMAN_H