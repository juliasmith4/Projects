#ifndef CRAWL_H
#define CRAWL_H
using namespace std;
#include <map>
#include <set>
#include "Document.h"
#include "WordLook.h"
#include <cctype> 

void goCrawl(const string& url, map<string, Document>& docs, set<string>& visited, WordLook& wordLook);

#endif