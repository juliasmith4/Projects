#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cctype>
#include <algorithm>
#include <regex>
#include "PageInfo.h"
#include "Search.h"

using namespace std;

// global vars

// set holding the files already visited
set<string> visited;


// map from file path to page info
map<string, PageInfo> pages;

// inverted index 
// word -->  set of file paths containing it
map<string, set<string>> invertedIndex;


// start main function
int main(int argc, char* argv[]) 
{
    // check for seed file and query file
    if (argc < 3) return 1;

    string seedFile = argv[1];
    string inputFile = argv[2];


    // crawl starting from seed file
    crawl(seedFile);

    // build incoming links for each page
    buildIncomingLinks();


    // process search queries from input file
    processQueries(inputFile);

    return 0;
}