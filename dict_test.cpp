#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include "dict.h"
using namespace std;

int main()
{
    dict<string> dictionary;
    vector<vector<string>> misspelled_words;
    dictionary.generate_dict("text_files/simple_wordlist.txt");
    dictionary.add_word("hello");
    dictionary.remove_word("hello");
    dictionary.save_dict("text_files/saved_dict.txt");
    dictionary.read_dict("text_files/saved_dict.txt");
    cout << dictionary.dict_size() << endl;
    misspelled_words = dictionary.spell_check("text_files/file_to_check.txt");
    // for (int i = 0; i < misspelled_words.size(); i++)
    // {
    //     cout << "Misspelled word: " << misspelled_words[i][0] << endl;
    //     cout << "Similar words: ";
    //     for (int j = 1; j < misspelled_words[i].size(); j++)
    //         cout << misspelled_words[i][j] << " ";
    //     cout << endl << endl;
    // }

    return 0;
}