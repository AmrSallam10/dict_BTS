#include <iostream>
#include <iomanip>
#include "dict.h"
using namespace std;

template <class dataType>
dict<dataType>::dict()
{ size = 0; }

template <class dataType>
void dict<dataType>::generate_dict(const string& filename)
{
    ifstream infile;
    infile.open(filename.c_str());
    if (infile.fail())
    {
        cout << "Error: File not found" << endl;
        return;
    }
    dataType word;
    while (infile >> word){
        to_lower_case(word);
        add_word(word);
    }

    infile.close();
}

template <class dataType>
void dict<dataType>::add_word(const dataType& word)
{
    dataType tmp = word;
    to_lower_case(tmp);
    int index = get_index(tmp);
    if (index == -1)
        return;
    if (!dict_tree[index].search(tmp))
    {
        dict_tree[index].insert(tmp, true);
        size++;
    }
}

template <class dataType>
void dict<dataType>::remove_word(const dataType& word)
{
    dataType tmp = word;
    to_lower_case(tmp);
    int index = get_index(tmp);
    if (index == -1){
        cout << "Invalid word" << endl;
        return;
    }
    if (dict_tree[index].search(tmp))
    {
        dict_tree[index].remove(tmp);
        size--;
    } else
        cout << "Word not found" << endl;

}

// TODO: Implement the save_dict function
template <class dataType>
void dict<dataType>::save_dict(const string& filename)
{
    ofstream outfile;
    outfile.open(filename.c_str());
    if (outfile.fail())
    {
        cout << "Error: File not found" << endl;
        return;
    }
    for (int i = 0; i < 36; i++)
        if (!dict_tree[i].empty())
            dict_tree[i].preorder(outfile);
    outfile.close();
}

template <class dataType>
void dict<dataType>::read_dict(const string& filename)
{
    ifstream infile;
    infile.open(filename.c_str());
    if (infile.fail())
    {
        cout << "Error: File not found" << endl;
        return;
    }
    dataType word;
    while (infile >> word){
        to_lower_case(word);
        add_word(word);
    }
    infile.close();
}

template <class dataType>
int dict<dataType>::dict_size() const
{ return size; }

// TODO: Implement the suggestion part
template <class dataType>
vector<vector<dataType>> dict<dataType>::spell_check(const string& filename)
{
    ifstream infile;
    infile.open(filename.c_str());
    if (infile.fail())
    {
        cout << "Error: File not found" << endl;
        return vector<vector<dataType>>();
    }
    vector<vector<dataType>> misspelled;
    dataType word;
    while (infile >> word)
    {
        to_lower_case(word);
        int index = get_index(word);
        if (!dict_tree[index].search(word))
        {
            vector<dataType> suggestions;
            suggestions.push_back(word);
            if (!dict_tree[index].empty())
            {
                vector<dataType> words = dict_tree[i].inorder();
                for (int j = 0; j < words.size(); j++)
                {
                    if (hammer_distance(word, words[j]) == 1)
                        suggestions.push_back(words[j]);
                }
            }
            misspelled.push_back(suggestions);
        }
    }
    infile.close();
    return misspelled;
}

template <class dataType>
void dict<dataType>::graph_dict() const
{
    for (int i = 0; i < 36; i++)
        if (!dict_tree[i].empty()){
            dict_tree[i].graph();
            cout << "-----------------------------------" << endl;
        }
}

template <class dataType>
int dict<dataType>::get_index(const dataType& word)
{
    dataType temp = word;
    for (int i = 0; i < temp.length(); i++)
        if (isalpha(temp[i]))
            temp[i] = tolower(temp[i]);
    char c = temp[0];
    if (isdigit(c))
        return c - '0' + 26;
    else if (isalpha(c))
        return c - 'a';
    else
        return -1;
}

template <class dataType>
void dict<dataType>::to_lower_case(dataType& word)
{
    for (int i = 0; i < word.length(); i++)
        if (isalpha(word[i]))
            word[i] = tolower(word[i]);
}

template <class dataType>
int dict<dataType>::hammer_distance(const dataType& word1, const dataType& word2)
{
    int m = std::min(word1.size(), word2.size());
    int M = std::max(word1.size(), word2.size());
    int mismatches = 0;
    for (int i = 0; i < m; i++) {
        if (word1[i] != word2[i]) {
            mismatches++;
        }
    }
    return mismatches + (M - m);
}