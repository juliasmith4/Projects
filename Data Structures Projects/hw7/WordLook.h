#ifndef WORDLOOK_H
#define WORDLOOK_H

#include "Document.h"
#include <string>
#include <map>
#include <set>
#include <vector>

using namespace std;

class WordLook {
private:
    map<string, set<string>> lookup; // word -> set of doc URLs
public:
    void addWord(const string& word, const string& url) {
        lookup[word].insert(url);
    }

    set<string> getDocs(const string& word) const {
        auto it = lookup.find(word);
        if (it != lookup.end()) return it->second;
        return {};
    }

    bool contains(const string& word) const {
        return lookup.find(word) != lookup.end();
    }

    const map<string, set<string>>& getMap() const {
        return lookup;
    }
};
#endif