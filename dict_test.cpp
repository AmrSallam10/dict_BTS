#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include "dict.h"
using namespace std;

int main()
{
    dict<string> dictionary;
    vector<vector<string>> suggestions;
    dictionary.generate_dict("text_files/wordlist.txt");
    suggestions = dictionary.spell_check("text_files/file_to_check.txt");

    for (int i = 0; i < suggestions.size(); i++){
        cout << "Word: " << suggestions[i][0] << endl;
        cout << "Suggestions: ";
        for (int j = 1; j < suggestions[i].size(); j++)
            cout << suggestions[i][j] << " ";
        cout << endl << endl;
    }

    // dictionary.graph_dict();

    return 0;
}