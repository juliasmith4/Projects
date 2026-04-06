#include <fstream>
#include <sstream>
#include <algorithm>
#include "Search.h"
#include <sstream>

// parse and read the files functions

// read the entire file and return it as a string

string readFile(const string& inputFile)
{
    ifstream file(inputFile);

    if (!file.is_open()) return ""; 
    // return empty string if cant open

    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    return content;
}

// check if the match is a full word by looking at boundaries
bool isWordBoundary(const string& text, int pos, int len)
{
    bool left = (pos == 0 || !isalnum(text[pos - 1]));

    bool right = (pos + len >= text.size() || !isalnum(text[pos + len]));

    return left && right;
}

// count how many times a word appears in normalized content
int countWordOccurrences(const string& content, const string& word)
{
    // split entire content into normalized words
    vector<string> allWords = splitWords(content);

    int count = 0;

    // count occurrences of exactly matching normalized word
    for (size_t i = 0; i < allWords.size(); i++)
    {
        if (allWords[i] == word)
        {
            count++;
        }
    }

    return count;
}
// count the words in a file and return as a map
map<string, int> countWords(const string& content)
{
    map<string, int> wordCount;
    vector<string> words = splitWords(content); 
    // get vector of words

    for (size_t i = 0; i < words.size(); i++)
    {
        string w = words[i];
        wordCount[w]++;
    }

    return wordCount;
}

// split a string into words based on space and remove punctuation

//previously caused error because it would split words together and ruin the page scoring and word count
vector<string> splitWords(const string& text)
{
    vector<string> words;
    string current;


    //loop through the text
    for (size_t i = 0; i < text.size(); i++)
    {
        char c = text[i];

        //check this specific character
        if (isalnum((c)))
        {
            //if it is alnum then add it to the current word
            current += c;
        }
        else
        {
            //if current current isnt empty then push back the word and clear it 
            if (!current.empty())
            {
                words.push_back(current);

                current.clear();
            }
        }
    }


    if (!current.empty())
    {
        words.push_back(current);
    }

    return words;
}

// remove any non-alphanumeric characters from a word
string normalizeWord(const string& word)
{
    string result; 
    for (size_t i = 0; i < word.size(); i++)
    {
        char c = word[i];
        if (isalnum(c))
        {
            result +=(c);
        }
    }
    return result;
}



// query functions

// check if query is a phrase ""

bool isPhraseQuery(const string& query)
{
    return (query.size() >= 2 && query.front() == '"' && query.back() == '"');
}



// remove quotes from a phrase query
string stripQuotes(const string& query)
{
    if (isPhraseQuery(query))
    {
        return query.substr(1, query.size()-2);
    }
    return query;
}

// extract words from query and normalize them
vector<string> extractQueryWords(const string& query)
{
    // remove punctuation, convert to lowercase, split by space
    vector<string> words; 
    stringstream ss(query);
    string temp; 

    while (ss >> temp)
    {
        // splits by white space 
        string clean = normalizeWord(temp);

        if (!clean.empty())
        {
            words.push_back(clean);
        }
    }

    // returns vector of clean words
    return words;
}

// regular search no ""

// search documents for all words 
set<string> regularSearch(const vector<string>& words)
{
    set<string> result;

    if (words.empty()) return result;

    // check first word if it doesnt exist then return the empty 
    if (invertedIndex.find(words[0]) == invertedIndex.end())            
    {
        return result;
    }


    //else initialize the result with the first word
    result = invertedIndex[words[0]];



    for (size_t i = 1; i < words.size(); i++)
    {
        if (invertedIndex.find(words[i]) == invertedIndex.end())
        {
            result.clear(); 
            // if any word missing no match
            return result;
        }

        set<string> temp;
        set<string> currentDocs = invertedIndex[words[i]];

        // keep only docs that contain all words
        for (size_t j = 0; j < result.size(); j++)
        {
            string doc = *next(result.begin(), j);
            if (currentDocs.count(doc))
            {
                temp.insert(doc);
            }
        }

        result = temp;

        if (result.empty()) return result;
    }

    return result;
}

// phrase "" search

// search documents for exact phrase
set<string> phraseSearch(const string& query)
{
    set<string> result;

    // remove quotes from phrase
    string phrase = stripQuotes(query);

    // loop through all pages
    for (map<string, PageInfo>::iterator it = pages.begin(); it != pages.end(); it++)
    {
        const string& content = it->second.content;

        size_t pos = 0;

        // search for phrase in content
        while ((pos = content.find(phrase, pos)) != string::npos)
        {
            // check word boundaries
            if (isWordBoundary(content, pos, phrase.size()))
            {
                result.insert(it->first);
                break; 
                // stop after first match
            }

            pos++;
        }
    }

    return result;
}






// scoring functions


//  score from keyword density
//using formula from submitty 
double computeKeywordDensityScore(const string& doc, const vector<string>& words)
{
    double totalScore = 0.0;

    double totalLengthAllDocs = 0.0;

    // total length from all docs 

    //chars 

    for (map<string, PageInfo>::iterator it = pages.begin(); it != pages.end(); it++)
    {
        totalLengthAllDocs += it->second.content.size();
    }

    //if it is 0 return 0
    if (totalLengthAllDocs == 0) return 0.0;

    //docLength is the size of hte doc in the page map
    double docLength = pages[doc].content.size();


    if (docLength == 0) return 0.0;

    //loop through words
    for (size_t i = 0; i < words.size(); i++)
    {
        string word = words[i];


        //track occurances
        double totalOccurrences = 0.0;

        // count occurrences across all documents using wordCount map
        for (map<string, PageInfo>::iterator it = pages.begin(); it != pages.end(); it++)
        {
            map<string, int>::iterator found = it->second.wordCount.find(word);

            if (found != it->second.wordCount.end())
            {
                totalOccurrences += found->second;
            }
        }

        if (totalOccurrences == 0.0) continue;

        double docCount = 0.0;

        // count occurrences in this document using wordCount
        map<string, int>::iterator itDoc = pages[doc].wordCount.find(word);
        if (itDoc != pages[doc].wordCount.end())
        {
            docCount = itDoc->second;
        }


        //scoring formulas 
        double globalDensity = totalOccurrences / totalLengthAllDocs;

        double keywordScore = docCount / (docLength * globalDensity);

        totalScore += keywordScore;
    }

    return totalScore;
}


// compute score based on backlinks
double computeBacklinkScore(const string& doc)
{
    double score = 0.0;

    // go through all incoming links

    for (set<string>::iterator it = pages[doc].incoming.begin(); it != pages[doc].incoming.end(); it++)
    {

        //incoming doc iterator
        string incomingDoc = *it;

        //getting the size of the outCount from the map 
        int outCount = pages[incomingDoc].outgoing.size();

        score += 1.0 / (1 + outCount);
    }

    return score;
}





// compute final page score


double computePageScore(const string& doc, const vector<string>& words)
{

    //formulas from the submitty

    //used for output printing


    double densityScore = computeKeywordDensityScore(doc, words);

    double backLinkScore = computeBacklinkScore(doc);
    
    double pageScore = 0.5 * densityScore + 0.5 * backLinkScore;
    return pageScore;

}


// wwriting to the output file
void writeResults(const string& outFile, const vector<SearchResult>& results, const string& query) 

{
   
    ofstream fout(outFile);
    if (results.empty()) 
    
    {
        fout << "Your search - " << query << " - did not match any documents.\n";
        return;
    }



    vector<SearchResult>::const_iterator rit;
    fout<< "Matching documents: \n";
    for (rit = results.begin(); rit != results.end(); ++rit) 
    
    {
        PageInfo page = pages[rit->path];


        fout << "\nTitle: " << page.title << "\n";
        fout << "URL: " << rit->path << "\n";
        fout << "Description: " << page.description << "\n";


        fout << "Snippet: " << constructSnippet(page.content, query) << "\n";
    }
}


// forward declarations
void writeResults(const string& outFile, const vector<SearchResult>& results, const string& query);
string constructSnippet(const string& content, const string& query);



//path funcs

// function for  ./ and ../
string normalizePath(const string& baseDir, const string& link)
{
    string path;

    
    if (link.find("html_files") == 0) 
    
    {
        // link is already absolute
        path = link;
    } 
    
    else 
    {
        // add base directory
        path = baseDir + link;
    }


    // remove . and / from the path 
    size_t pos;
    while ((pos = path.find("/./")) != string::npos)
    {
        path.erase(pos, 2);
    }

    while ((pos = path.find("/../")) != string::npos)
    {
        if (pos == 0) break; 
        // cannot go above root

        size_t beforeSlash = path.rfind('/', pos - 1);

        //if not exist then break
        if (beforeSlash == string::npos) break;

        path.erase(beforeSlash, pos - beforeSlash + 3);
    }


    // remove trailing slash if its there
    if (!path.empty() && path.back() == '/')   path.pop_back();

    return path;

}



// function to get directory from a file path
string getDirectory(const string& path)

{
    size_t lastSlash = path.find_last_of('/');

    if (lastSlash == string::npos) return "";


    return path.substr(0, lastSlash + 1); 
    // include trailing slash
}



// snippet


// function to create a snippet of text around the query

// get snippet of  exact query word

// helper function to find a target word or phrase with word boundaries
size_t findWithBoundary(const string& text, const string& target)
{
    size_t p = 0;
    while ((p = text.find(target, p)) != string::npos)
    {
        if (isWordBoundary(text, p, target.size()))
        {
            return p; 
            // found a full word match
        }


        p++;
    }

    return string::npos; 
    // not found
}

string constructSnippet(const string& content, const string& query) 
{
    // extract body
    size_t bodyStart = content.find("<body>");
    size_t bodyEnd = content.find("</body>");

    string body;

    if (bodyStart != string::npos && bodyEnd != string::npos)
    {
        body = content.substr(bodyStart + 6, bodyEnd - (bodyStart + 6));
    }

    else
    {
        body = content;

    }
        

    string phrase = stripQuotes(query);
    vector<string> words = extractQueryWords(query);

    size_t pos = string::npos;

    // phrase search 
  
    pos = findWithBoundary(body, phrase);

    // fallback for regular search
    if (pos == string::npos && !isPhraseQuery(query) && !words.empty())
    {
        pos = findWithBoundary(body, words[0]);
    }

    if (pos == string::npos) return "";

    // find sentence start

    size_t sentenceStart = body.rfind('.', pos);


    if (sentenceStart == string::npos)
    {
        sentenceStart = 0;
    }
        
    else
    {
        sentenceStart++;
    }
        

    // skip blank spaces
    while (sentenceStart < body.size() && isspace(body[sentenceStart]))
    {
        sentenceStart++;
    }

    //  120 chars limit
    size_t snippetLength = 120;
    if (sentenceStart + snippetLength > body.size())
    {
                snippetLength = body.size() - sentenceStart;

    }

    return body.substr(sentenceStart, snippetLength);
}
// parse the html

// extract title from html content
string extractTitle(const string& content) 
{
    size_t start = content.find("<title>");

    size_t end = content.find("</title>");

    if (start == string::npos || end == string::npos) return "";

    start += 7; 
    // skip <title>

    return content.substr(start, end - start);
}


//  description from html content
string extractDescription(const string& content)
{

    size_t start = content.find("<meta name=\"description\" content=\"");

    if (start == string::npos) return "";


    start += 34; 
    // skip meta tag

    size_t end = content.find("\">", start);

    if (end == string::npos) return "";

    return content.substr(start, end - start);
}

// recursive function to crawl pages and build index
void crawl(const string& filePath)
{
    // skip if already visited
    if (visited.count(filePath)) return;

    //else insert it 
    visited.insert(filePath);


    // read file content
    ifstream fin(filePath);

    //file open error 
    if (!fin.is_open()) return;


    string content((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
    // create page info
    PageInfo page;
    page.path = filePath;
    page.content = content;

    page.length = content.size();

    page.wordCount = countWords(content);
    page.title = extractTitle(content);
    page.description = extractDescription(content);

    // extract links from html
   list<string> links = extractLinksFromHTML(content);
set<string> outgoingLinks;

string baseDir = getDirectory(filePath);

for (list<string>::iterator it = links.begin(); it != links.end(); ++it)
{
    string fullPath = normalizePath(baseDir, *it);
    outgoingLinks.insert(fullPath);
}

page.outgoing = outgoingLinks;



    // update inverted index
    map<string,int>::iterator it;
    for (it = page.wordCount.begin(); it != page.wordCount.end(); ++it) 
    {
        invertedIndex[it->first].insert(filePath);
    }


    // save page

    pages[filePath] = page;


    // recurse through outgoing links

     baseDir = getDirectory(filePath);

    set<string>::iterator sit;


    for (sit = outgoingLinks.begin(); sit != outgoingLinks.end(); ++sit)
     {
        string fullPath = normalizePath(baseDir, *sit);
        crawl(fullPath);
    }
}

// create incoming link path
//from outgoing links of each page
void buildIncomingLinks() 
{
    map<string, PageInfo>::iterator pit;

    for (pit = pages.begin(); pit != pages.end(); ++pit) 
    {
        string from = pit->first;

        set<string>::iterator sit;

        for (sit = pit->second.outgoing.begin(); sit != pit->second.outgoing.end(); ++sit) 
        {

            string to = *sit;


            if (pages.count(to)) 
            {
                pages[to].incoming.insert(from);
            }


        }
    }
}

// process the querey
void processQueries(const string& inputFile) 

{
    ifstream fin(inputFile);

    //error opening file 
    if (!fin.is_open()) return;

    string query;
    int fileIndex = 1;

    while (getline(fin, query))
    {
        set<string> matchedDocs;

        if (isPhraseQuery(query)) 
        {
            matchedDocs = phraseSearch(query);
        }
    
        else 
        {
            vector<string> words = extractQueryWords(query);
            matchedDocs = regularSearch(words);
        }


        vector<SearchResult> results;

        set<string>::iterator sit;

        for (sit = matchedDocs.begin(); sit != matchedDocs.end(); ++sit) 
        {
            SearchResult r;
            r.path = *sit;
            vector<string> words = extractQueryWords(query);
            r.score = computePageScore(*sit, words);
            results.push_back(r);


        }


        // sort by score descending


    sort(results.begin(), results.end(), [](const SearchResult& a, const SearchResult& b)
    {
       
            return a.score > b.score; 
            // higher score first
    

    });

        // write output file
        string outFile = "out" + to_string(fileIndex) + ".txt";
        fileIndex++;
        writeResults(outFile, results, query);
    }
}


