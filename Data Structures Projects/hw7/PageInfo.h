#ifndef PAGEINFO_H
#define PAGEINFO_H
#include <regex>
#include <vector>

#include <string>
#include <list>
#include <set>
#include <map>
using namespace std;

list<string> extractLinksFromHTML(const string& fileContent);


//data to hold the info of each page/html file
struct PageInfo 
{
    string path;

    string fullContent;   
    // store entire HTML content
    string content;       
    // body only for snippets

    size_t length = 0;    
    // full content length

    set<string> outgoing;
    set<string> incoming;

    map<string, int> wordCount; 
    // word count for full content

    string title;
    string description;
};
#endif