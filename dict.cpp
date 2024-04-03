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
        cout << "Invalid word: " << word << endl;
    else if (!dict_tree[index].search(tmp))
    {
        dict_tree[index].insert(tmp);
        size++; 
    } else
        cout << "Word already exists: " << word << endl;
}

template <class dataType>
void dict<dataType>::remove_word(const dataType& word)
{
    dataType tmp = word;
    to_lower_case(tmp);
    int index = get_index(tmp);
    if (index == -1)
        cout << "Invalid word: " << word << endl;
    else if (dict_tree[index].search(tmp))
    {
        dict_tree[index].remove(tmp);
        size--;
    } else
        cout << "Word not found: " << word << endl;
}

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
            dict_tree[i].preorder_save(outfile);
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
    vector<vector<dataType>> suggestions;
    dataType word;
    while (infile >> word)
    {
        to_lower_case(word);
        int index = get_index(word);
        if (index == -1 || dict_tree[index].empty() || !dict_tree[index].search(word))
        {
            vector<std::pair<dataType, int>> top_words;
            suggestions.push_back(vector<dataType>());
            suggestions.back().push_back(word);
            get_similar_words(word, top_words);
            for (int i = 0; i < top_words.size(); i++)
                suggestions.back().push_back(top_words[i].first);
        }
    }
    infile.close();
    return suggestions;
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
void dict<dataType>::get_similar_words(const dataType& word, vector<std::pair<dataType, int>>& top_words)
{
    int index = get_index(word);
    if (index != -1){
        if (!dict_tree[index].empty())
            dict_tree[index].get_top_similar_words(word, top_words);
    }
}