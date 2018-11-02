#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<cctype>
#include<set>
#include<map>

using namespace std;

int main()
{
    ifstream ifs("words", ios::in);
    string word;
    
    set<string> word_list;
    map<string, set<string> > word_map;
    
    // Read the words
    while (ifs.good())
    {
        getline(ifs, word);
        
        // Read only 4-letter words
        if (word.length() == 4)
        {
            int i = 0;
            int flag = 0;
            
            // Skip words containing numbers and other special characters
            while (word[i])
            {
                if (!isalpha(word[i]))
                {
                    flag = 1;
                }
                i++;
            }
            
            // Store the filtered words into a set
            if (flag == 0)
            {
                transform(word.begin(), word.end(), word.begin(), ::tolower);
                word_list.insert(word);
            }
        }
    }
    
    // Generate sets of similar words into a map
    for (set<string>::iterator it = word_list.begin(); it != word_list.end(); ++it)
    {
        for (set<string>::iterator it2 = word_list.begin(); it2 != word_list.end(); ++it2)
        {
            // Compute the difference between each word
            int diff = 0;
            for (int i = 0; i < 4; i++)
            {
                if ((*it)[i] == (*it2)[i])
                {
                    diff++;
                }
            }
            
            // If the strings differ by one character, add them to the corresponding set
            if (diff == 3)
            {
                word_map[*it].insert(*it2);
            }
        }
    }

    // Read user-input
    cout << "Enter a 4-letter word : ";
    string input;
    
    while (cin >> input)
    {
        // Invalid input
        if (input.length() != 4)
        {
            cout << "Please enter a string of length 4" << endl;
            cout << endl << "Enter a 4-letter word : ";
            continue;
        }
        
        // Find the input word in the map
        map<string, set<string> >::iterator temp_it = word_map.find(input);
        int counter = 0;
        
        if (temp_it != word_map.end())
        {
            set<string> &similar_words = temp_it->second;
            
            // Print out the contents in the local set
            for (set<string>::iterator sw_it = similar_words.begin(); sw_it != similar_words.end(); ++sw_it)
            {
                cout << *sw_it << "\t";
                counter++;
            }
        }
        cout << endl << "Total " << counter << " words" << endl;
        cout << endl << "Enter a 4-letter word : ";
    }

    return 0;
}
