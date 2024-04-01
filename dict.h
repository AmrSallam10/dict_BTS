#ifndef DICT_H
#define DICT_H

// Specification of the class
#include <string>
#include <vector>
#include "binaryTree.h"
using namespace std;
template <class dataType>
class dict
{   
    public:

        dict();

        void generate_dict(const string& filename);

        void add_word(const dataType& word);

        void remove_word(const dataType& word);

        void save_dict(const string& filename);

        void read_dict(const string& filename);

        int dict_size() const;

        void graph_dict() const;

        vector<vector<dataType>> spell_check(const string& filename);

    private:
        binaryTree<dataType, bool> dict_tree[36];
        int size;

        int get_index(const dataType& word);

        void to_lower_case(dataType& word);

        void get_similar_words(const dataType& word, vector<std::pair<dataType, int>>& similar_words);
}; 
#include "dict.cpp"
#endif // DICT_H