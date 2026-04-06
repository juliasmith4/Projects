#ifndef SEARCH_H
#define SEARCH_H
using namespace std;
#include <string>
#include <vector>
#include <map>
#include "PageInfo.h"




#include "Search.h"


extern map<string, PageInfo> pages;
extern set<string> visited;
extern map<string, set<string>> invertedIndex;


struct SearchResult
{
    string path;
    double score;
};



//file and parsing 
string readFile(const string& inputFile);

map<string, int> countWords(const string& content);

vector<string> splitWords(const string& text);

string normalizeWord(const string& word);
//searching

bool isPhraseQuery(const string& query);

string stripQuotes(const string& query);

vector<string> extractQueryWords(const string& query);

set<string> regularSearch(const vector<string>& words);
set<string> phraseSearch(const string& phrase);


//ranking

double computeKeywordDensityScore(const string& doc, const vector<string>& words);

double computeBacklinkScore(const string& doc);
double computePageScore(const string& doc, const vector<string>& words);
//output 

void writeResults(const string& outFile, const vector<SearchResult>& results, const string& query) ;
void processQueries(const string& inputFile) ;
string extractBody(const string& content); 


void buildIncomingLinks() ;
void crawl(const string& filePath);
string extractDescription(const string& content);
string extractTitle(const string& content) ;
string constructSnippet(const string& content, const string& query);
string getDirectory(const string& path);
string normalizePath(const string& baseDir, const string& link);
size_t findWithBoundary(const string& text, const string& target);





#endif