#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<sstream>
#include<map>

using namespace std;

int main(int argc, char *argv[])
{
    // Argument check
    if (argc != 2)
    {
        cout << "Invalid/Missing inputs" << endl;
        cout << "Usage: ./<executable> <file>" << endl;
        exit(EXIT_FAILURE);
    }
    
    // Open data file
    ifstream ifs(argv[1], ios::in);
    string line;
    
    // Declaring the map variables
    map<string, string> year_map;
    map<string, map<string, string> > word_map;
    
    // Read every line from the CSV file, and store them in the appropriate containers
    while (ifs.good())
    {
        getline(ifs, line);
        istringstream iss(line);
        string word, year, count;
        
        getline(iss, word, '\t');
        getline(iss, year, '\t');
        getline(iss, count, '\t');

        word_map.insert(make_pair(word, year_map));
        word_map[word].insert(make_pair(year, count));
    }
    
    ifs.close();
    
    // Read input from user
    string inputs;
    cout << "Enter the word and year: " << endl;
    
    // Read user inputs
    while (cin >> inputs)
    {
        string input_word = inputs;
        cin >> inputs;
        string input_year = inputs;
    
        // Search through contents of word map using iterator
        map<string, map<string, string> >::iterator it = word_map.find(input_word);
        
        // If word found
        if (it != word_map.end())
        {            
            // Search through contents of year map
            map<string, string> &internal_map = it->second;
            map<string, string>::iterator it2 = internal_map.find(input_year);
            
            // If input year found
            if (it2 != internal_map.end())
            {
                // Iterate and print through the end
                for (; it2 != internal_map.end(); ++it2)
                {
                    cout << it2->first << "\t" << it2->second << endl;
                }
            }
            
            // Input year not found
            else
            {
                cout << "Year not found." << endl;
            }
        }

        // Input word not found
        else
        {
            cout << "Word not found." << endl;
        }
        
        cout << "Enter the word and year: " << endl;
    }
    
    return 0;
}
