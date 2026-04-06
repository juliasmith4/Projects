
#include "Business.h"

#include <fstream>
#include <cmath>
#include <sstream>
#include <iomanip>

using namespace std;
#include <string>
#include <iostream>
#include <list>

//safely return a number to not throw a stoi error
int safe_stoi(const std::string& s, int defaultValue = 0)
 {
    std::string digits;
    //loop through the string 
    for (char c : s) 
    {
        //check if it is a digit 
        if (std::isdigit(c))
        {
            //if it is then add it 
            digits += c;
        }
    }


    //return default
    if (digits.empty()) 
    {
        return defaultValue;
    }

    // convert digits string to integer manually

    int result = 0;

    for (char c : digits)
    {
        result = result * 10 + (c - '0'); 
    }
    return result;
}

Business::Business(const std::string& line)
{
    // assign values to member variables
    name = firstGetName(const_cast<std::string&>(line));
    categories = firstGetCategories(const_cast<std::string&>(line));
    rating = firstGetRating(const_cast<std::string&>(line));
    numReviews = firstGetNumReviews(const_cast<std::string&>(line));
    price = firstGetPrice(const_cast<std::string&>(line));
    zipcode = firstGetZip(const_cast<std::string&>(line));
    town = firstGetTown(const_cast<std::string&>(line));
}


//Get Business Name:
string Business::firstGetName(std::string& line) const
{
        int start = 0;
        // starting from the position start, and search the string variable line,
        // to find the first name string.
        int key_start = line.find("name", start);
        int value_start = key_start + 7;
        // remember to use escape.
        int value_end = line.find("\"", value_start);
        int len = value_end - value_start;
        // go from start to end, but exclude the character at end.
        // when we use the substr(start, length) function on a std::string,
        // the substring includes the character at the start position,
        // and the length of the substring is length.
        // It does not include the character at the position start + length.
        std::string name = line.substr(value_start, len);
        return name;
}

string Business::getName() const
{
    return name;
}

//Get Categories:
list<string> Business::firstGetCategories(std::string& line) const
{
    list<string> result;
    int key_start = line.find("categories");
    if (key_start == string::npos) 
    {
        return result;
    }
    
    int value_start = key_start + 13;

    int value_end = line.find("\"", value_start);

    if (value_end == string::npos) 
    {
        return result;
    }
    //string of the categories
    string catString = line.substr(value_start, value_end - value_start);
    string temp;

    //loop through the categories and trim the extra spaces 
    for (char   c : catString) 
    {
        if (c == ',') 
        {
            // Trim spaces
            while (!temp.empty() && temp.front() == ' ') 
            {
                temp.erase(0,1);
            }
            while (!temp.empty() && temp.back() == ' ') 
            {
                temp.pop_back();
            }

            if (!temp.empty()) 
            {
                result.push_back(temp);
            }
            temp.clear();
        } 
        else 
        {
            temp += c;
        }
    }

    // last cat
    while (!temp.empty() && temp.front() == ' ') 
    {
        temp.erase(0,1);
    }
    while (!temp.empty() && temp.back() == ' ') 
    {
        temp.pop_back();
    }
    //safely push back
    if (!temp.empty()) 
    {
        result.push_back(temp);
    }

    return result;
}

int Business::firstGetNumReviews(string& line) const
{
    int key_start = line.find("review_count");

    //if doesntexist 
    
    if (key_start == string::npos)
    {
        return 0;
    }
    //extracting 
    int value_start = line.find(":", key_start) + 1;
    int value_end = line.find(",", value_start);


    string number = line.substr(value_start, value_end - value_start);

    //no number return 0  no stoi error
    if (number.empty()) 
    {
        return 0;
    }

    //no stoi error
    if (number.empty()) 
    {
        return 0;
    }
    //returning safely so there is no stoi error 
    return safe_stoi(number, 0);;
}


list<string> Business::getCategories() const
{
    return categories;
}



//Get Rating:
double Business::firstGetRating(string& line) const
{
    int key_start = line.find("stars");
    if (key_start == string::npos)
    {
        return 0.0;
    }

    //correctly extract it from the json
    //no spaces
    int value_start = line.find(":", key_start) + 1;
    int value_end = line.find(",", value_start);

    string number = line.substr(value_start, value_end - value_start);
    //return first rating 
    return stod(number);
}


double Business::getRating() const
{
    return rating;
}


//get price from json
int Business::firstGetPrice(std::string& line) const{
        int start = 0;
        // starting from the position start, and search the string variable line,
        // to find the first RestaurantsPriceRange2 string.

        int key_start = line.find("RestaurantsPriceRange2", start);

        // if not found, return now
        if(key_start == std::string::npos){
                return -1;
        }
        int value_start = key_start + 25;
        // remember to use escape.
        int value_end = line.find("\"", value_start);
        // -1 here because this is not a string.
        int len = value_end - value_start;
        // go from start to end, but exclude the character at end.
        // when we use the substr(start, length) function on a std::string,
        // the substring includes the character at the start position,
        // and the length of the substring is length.
        // It does not include the character at the position start + length.
        // convert this string to an integer
        int price = safe_stoi(line.substr(value_start, len));
        return price;
}

int Business::getPrice() const
{
    return price;
}

string Business::firstGetZip(string& line) const
{

    //postal code holds zip from input 

    int key_start = line.find("postal_code");


    //if not exis return empty 
    if (key_start == string::npos)
        {
            return "";
        }

    int value_start = line.find("\"", key_start + 12) + 1;
    int value_end = line.find("\"", value_start);

    return line.substr(value_start, value_end - value_start);
}



string Business::getZipcode() const
{
return zipcode;
}


 ostream& operator<<(ostream& os, const Business& business)
{   
    //theReturn is the final print 
    string theReturn; 
    theReturn += business.getName() + '\n';
    double rating = business.getRating();


    int fullStars = (int)rating;          
    // full stars

    bool halfStar = (rating - fullStars) >= 0.5;  
    // check if there is a half star

    for (int i = 0; i < fullStars; i++)
    {
        theReturn += "\u2605";
    }

    if (halfStar)
    {
        theReturn += "\u00BD";  
        // half star symbol
    }
       

    //  only one decimal if fraction

    std::ostringstream ratingStream;

    if (std::floor(rating) == rating) 
    {
        ratingStream << (int)rating; 
        // whole number
    } 

    else 
    {
        ratingStream << std::fixed << std::setprecision(1) << rating; 
        // 1 decimal if not whole
    }

    theReturn += " " + ratingStream.str();

    //num of reviews 
    theReturn += " (" + to_string(business.getNumReviews()) + " reviews)\n";

    //printing town 
    theReturn += business.getTown() + " ";
    
    if (business.getPrice() > 0)
        {
            
            for (int i = 0; i < business.getPrice(); i++)
            {
                theReturn += "$";
            }
        }


    theReturn += "\n";

    list<string> cats = business.getCategories();

    //iterating through categories and printing them 
    int count = 0;
    for (string c : cats)
        {
            //formating for no , at end or before beginning
            if (count == 0)
            {
                theReturn += c ;
            }
          
            else
            {
                theReturn += ", " + c;
            }
            count++;
        }
    

    //printing done 

    os << theReturn;
    return os;

}

//towns
string Business:: firstGetTown(string& line) const
{
    int key_start = line.find("\"city\"");

    if (key_start == string::npos)
    {
        return "";
    }
        
    // find the colon after "city"
    int colon_pos = line.find(":", key_start);


    if (colon_pos == string::npos)
    {
        return "";

    }
        
    // find the starting quote of the value
    
    int value_start = line.find("\"", colon_pos) + 1;
    int value_end = line.find("\"", value_start);

    return line.substr(value_start, value_end - value_start);
}


int Business::getNumReviews() const
{
    return numReviews;
}


string Business::getTown() const
{
    return town;
}



