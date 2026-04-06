#ifndef BUSINESS_H
#define BUSINESS_H

#include <list>

#include <string>
using namespace std;


class Business
{

private:

    //variables for business object 

    string name; 
    list<string> categories;
    double rating; 
    int price;
    string zipcode;
    string town;
    int numReviews;


public:


//constructor using the line from the json file 

Business(const string& line);

//no argument constructor that sets to null just in case 

Business()
{
    name = "";
    categories = list<string>();
 //have to convert this string to a list (done)
    rating = 0.0;
    price = 0;
    zipcode = "";
    town = "";
    numReviews = 0;


}


//getters 
int firstGetNumReviews(string& line) const;

string firstGetName(std::string& line) const;

string getName() const;

list<string> firstGetCategories(std::string& line) const;

list<string> getCategories() const;

double firstGetRating(std::string& line) const;

double getRating() const;

int firstGetPrice(std::string& line) const;

int getPrice() const;

string firstGetZip(string& line) const;

string getZipcode() const;

int getNumReviews() const;

/*

how it is supposed to print

=====================
4. Dustie Wagens
★★★★★ 5 (8 reviews)
Santa Barbara 
Tours, Hotels & Travel, Wine Tours, Campgrounds, Car Rental, Active Life, Wedding Planning, Surfing, Event Planning & Services
=====================

*/

//printing override 

friend ostream& operator<<(ostream& os, const Business& business);

string firstGetTown(string& line) const;
string getTown() const;


};
#endif