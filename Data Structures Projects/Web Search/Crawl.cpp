
using namespace std;
#include <map>
#include <set>
#include "Crawl.h"
#include "Document.h"
#include "WordLook.h"
#include <cctype> 


void goCrawl(const string& url,
             map<string, Document>& docs,
             set<string>& visited,
             WordLook& wordLook)
{
    // ✅ Avoid infinite loop
    if (visited.count(url)) return;
    visited.insert(url);

    ifstream file(url);
    if (!file.is_open()) return;

    string content((istreambuf_iterator<char>(file)),
                    istreambuf_iterator<char>());

    Document doc;
    doc.url = url;
    doc.content = content;
    doc.length = content.length();

    // 🔷 TITLE
    size_t tStart = content.find("<title>");
    size_t tEnd   = content.find("</title>");
    if (tStart != string::npos && tEnd != string::npos)
        doc.title = content.substr(tStart + 7, tEnd - (tStart + 7));

    // 🔷 DESCRIPTION
    size_t dStart = content.find("name=\"description\"");
    if (dStart != string::npos) {
        size_t cStart = content.find("content=\"", dStart);
        size_t cEnd   = content.find("\"", cStart + 9);

        if (cStart != string::npos && cEnd != string::npos)
            doc.description = content.substr(cStart + 9, cEnd - (cStart + 9));
    }

    // 🔷 BODY
    size_t bStart = content.find("<body>");
    size_t bEnd   = content.find("</body>");
    if (bStart != string::npos && bEnd != string::npos)
        doc.body = content.substr(bStart + 6, bEnd - (bStart + 6));

    // 🔷 LINKS
    list<string> links = extractLinksFromHTML(content);

    size_t lastSlash = url.find_last_of('/');
    string dir = (lastSlash != string::npos) ? url.substr(0, lastSlash + 1) : "";

    for (const string& link : links) {

        string fullPath = dir + link;

        doc.outgoingLinks.insert(fullPath);

        // ✅ DO NOT create doc prematurely
        // Instead, record after crawl
    }

    // 🔷 WORD COUNT
    string word;

    for (char c : content) {
        if (isalnum(c)) {
            word += c;
        } else {
            if (!word.empty()) {
                doc.wordFreq[word]++;
                wordLook.addWord(word, url);
                word.clear();
            }
        }
    }

    if (!word.empty()) {
        doc.wordFreq[word]++;
        wordLook.addWord(word, url);
    }

    // ✅ Save doc AFTER processing
    docs[url] = doc;

    // 🔷 RECURSIVE CRAWL
    for (const string& link : doc.outgoingLinks) {
        goCrawl(link, docs, visited, wordLook);

        // ✅ NOW safely update incoming links
        if (docs.find(link) != docs.end()) {
            docs[link].incomingLinks.insert(url);
        }
    }
}