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
    dictionary.generate_dict("text_files/wordlist.txt");
    misspelled_words = dictionary.spell_check("text_files/file_to_check.txt");
    for (int i = 0; i < misspelled_words.size(); i++)
    {
        cout << "Misspelled word: " << misspelled_words[i][0] << endl;
        cout << "Similar words: ";
        for (int j = 1; j < misspelled_words[i].size(); j++)
            cout << misspelled_words[i][j] << " ";
        cout << endl;
    }

    return 0;
}