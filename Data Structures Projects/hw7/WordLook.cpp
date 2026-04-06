
#include "Document.h"
#include <string>
#include <map>
#include <set>
#include <vector>
using namespace std;

class WordLook 

{
private:

    map<string, set<string>> lookup; 
    // word -> set of doc URLs


public:

    //adding the word to the map and its url
    void addWord(const string& word, const string& url) 
    {
        lookup[word].insert(url);
    }

    //return the document set
    set<string> getDocs(const string& word) const {
        auto it = lookup.find(word);

        if (it != lookup.end()) return it->second;

        return {};
    }

    //see if the word exists in the map
    bool contains(const string& word) const
     {
        return lookup.find(word) != lookup.end();
    }


    //return the map itself
    const map<string, set<string>>& getMap() const 
    {
        return lookup;
    }
    
};