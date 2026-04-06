/*
Get familiar with a commonly used data structure - linked lists.
Practice using std::list.
Practice using iterators.

*/
#include <cmath>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <string>
#include <fstream>
//include Business class
#include "Business.h"
#include <algorithm> 
// for transform ^^


// to lowercase a string
//need to make a function to not throw stoi error 

string toLower(const string& s) 
{
    string result = s;
    transform(      result.begin(), result.end(), result.begin(),
     [](unsigned char c) { return tolower(c); }

);
    return result;
}

list<Business> filterBusiness(list<Business>& businesses, const string& zipcode, const list<string>& categories)
{
    list<Business> final;

    for (const Business& b : businesses)
    {
        if (b.getZipcode() != zipcode)
        {
            continue;
        }

        list<string> businessCats = b.getCategories();
        //flag 
        bool matchFound = false;

        for (string businessCat : businessCats)
        {
            for (string cat : categories)
            {
                // lowercase conversion for no case sensitivity 
                //if category is found in the categories, incorporates the categories such as ___ & ___ 
                if (toLower(businessCat).find(toLower(cat)) != string::npos)                
                {
                    //add the business
                    final.push_back(b);  
                //update flag          
                    matchFound = true;
                    break;  
                    // break inner loop
                }
            }
            if (matchFound) break; 
             // break outer loop
        }
    }

    return final;
}




//main
int main(int argc, char* argv[])
{

    //use business class and make a list of business objects 
    list<Business> businesses; 

    //parsing through json file, making business objects and adding them to the list



  //variables based off of the user inputs 
    string input = string(argv[1]);
    ifstream this_json(input);
    string output = std::string(argv[2]);
    string zipcode = string(argv[3]);
    string categoryInput = string(argv[4]);
    string line; 


   //going through the initial file
   while(getline(this_json, line))
	  {
      businesses.push_back(Business(line));
    }
    this_json.close();


// collect categories from argv4 and on
list<string> categories;
for (int i = 4; i < argc; i++)
{
    categories.push_back(string(argv[i]));
}

    //after parsing make a new list for only the filtered businesses using the filterBusiness 
    //iterate through businesses and get b.firstGetCategories and make a list 


    list<Business> filteredBusiness = filterBusiness(businesses, zipcode, categories);

//need to to sort the business objects in a list based on the rating 

// sort the filtered businesses by rating descending 

filteredBusiness.sort
(
    [](const Business& a, const Business& b)
 {
    return a.getRating() > b.getRating(); 
    // higher rating first
}

);



//print them
    ofstream outFile(output);
    if (!outFile.is_open())
        {
            return 1;
        }

    //checks if there were no matches
    if (filteredBusiness.empty())     
    {
        //none found message
        outFile << "Sorry, we couldn't find any results\n";
    } 
    else
     {
        //int index for count for printing 
        int index = 1;

        outFile << "=====================\n";

        for (const Business& b : filteredBusiness)
        {
            outFile << index << ". " << b << endl;
            outFile << "=====================\n";
            index++;
        }
    }

        outFile.close();
        return 0;

    }