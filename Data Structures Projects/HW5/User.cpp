#include "User.h"
#include "StringNode.h"
#include <iostream>
#include <vector>
#include "Node.h"
#include <cmath>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;


//getting the user object pointer by phone number
User* findUser(Node* allUsers, const string& phone)
{
  //temp is the first phone 
     Node* temp = allUsers;  // use the parameter name
    while (temp != nullptr)
    {
        if (temp->data->getPhone() == phone)
            return temp->data;

        temp = temp->next;
    }
    return nullptr;
}


// calculate the distance between two coordinates using Haversine formula
//from readme
double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    const double radiusOfEarth = 6371.0; // Earth's radius in kilometers

    // convert latitude and longitude from degrees to radians
    lat1 *= M_PI / 180.0;
    lon1 *= M_PI / 180.0;
    lat2 *= M_PI / 180.0;
    lon2 *= M_PI / 180.0;

    // Haversine formula
    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;
    double a = sin(dLat / 2.0) * sin(dLat / 2.0) + cos(lat1) * cos(lat2) * sin(dLon / 2.0) * sin(dLon / 2.0);
    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
    // distance in kilometers
    double distanceKM = radiusOfEarth * c;
    // convert it to distance in miles
    double distanceMiles = distanceKM * 0.621371;

    return distanceMiles;
}


// constructor user
User::User(string n,int a, string g,string p, string occ, string edu, double la,double lo,bool premium, int minA, int maxA, double maxD, string gPref  )

{
    //initializing the vars
    name = n;
    age = a;
    gender = g;
    phone = p;
    occupation = occ;
    education = edu;

    //locations
    lat = la;
    lon = lo;

    
    isPremium = premium;

    //preferences
    minAge = minA;
    maxAge = maxA;
    maxDis = maxD;
    genderPref = gPref;

    // linked lists start as empty
    likes = nullptr;
    likedBy = nullptr;
    matches = nullptr;
    blocked = nullptr;
}

// destructor 
User::~User()
    {
            

        // delete all linked list

        //delete nodes and no memory leaks

        StringNode* temp;
        while (likes) 
        { 
            temp = likes; 
            likes = likes->next; 
            //traversing through moving the likes and deleting values
            delete temp; 
        }

        while (matches) 
        { 

            temp = matches;
            matches = matches->next;
            delete temp; 


            }
        while (likedBy)
        {

            temp = likedBy; 
            likedBy = likedBy->next; 
            delete temp; 

            }
        while (blocked) 
        { 
            
            temp = blocked; 
            blocked = blocked->next;

            delete temp; 
        }
}
    

    //getters and setters 
    //get user information 
    string User::getPhone()
    {
        return phone;
    }

    string User::getName()
    {
        return name;
    }
    int User::getAge()
    {
        return age;
    }

    bool User::getPremium()
    {
        return isPremium;

    }


    //set user information 

    void User::setPhone(string newPhone)
    {
        phone = newPhone;
    }
    
    void User::setName(string newName)
    {
        name = newName;
    }

    void User::setAge(int newAge)
    {
        age = newAge;
    }
    void User::setPremium(bool newStatus)
    {
        isPremium = newStatus;
    }


    //linked list getters and setters for likes, matches, liked by and blocked 

    void User::addLikedBy(User& otherUser)
    {
        //add liked by phone number 

        //adding new node to head 

        StringNode* theNode = new StringNode(otherUser.getPhone());
        theNode->next = likedBy;
        likedBy = theNode;

    }

    //adding match to the matches
    void User::addMatch(User& otherUser)
    {
    // Check if this user is already matched with otherUser
    StringNode* temp = matches;
    while (temp != nullptr)
    {
        if (temp->phone == otherUser.getPhone())
        {
            // Already matched, do nothing
            return;
        }
        temp = temp->next;
    }

    // add new match at the head of the matches list
    StringNode* newNode = new StringNode(otherUser.getPhone());
    newNode->next = matches;
    matches = newNode;
        
    }


    void User::addLiked(User& otherUser)
    {
        //add like by phone number 

        //adding new node to head 
        
        StringNode* theNode = new StringNode(otherUser.getPhone());
        theNode->next = likes;
        likes = theNode;

    }
    void User::addBlocked(User& otherUser)
    {
        //add block by phone number 

        //adding new node to head 
        
        StringNode* theNode = new StringNode(otherUser.getPhone());
        theNode->next = blocked;
        blocked = theNode;

    }

    StringNode* User::getLikes()
    {
        return likes;
    }

    StringNode* User::getMatches()
    {
        return  matches;
    }

    StringNode* User::getlikedBy()
    {
        return likedBy;
    }

    StringNode* User::getBlocked()
    {
        return blocked;
    }


    bool User::isBlocked(User* otherUser) 
    {

    // check if otherUser is in this->blocked list
    StringNode* temp = blocked;

    //until reached the end of linked list
    while(temp != nullptr) 
    {
        if(temp->phone == otherUser->getPhone()) 
        {
            return true;
        }

        temp = temp->next;
    }
    return false;
}
    
//include output files as parameter to print

// /Show Profiles
void User::showProfiles(Node* allUsers, ofstream& outFile)
{
    

    Node* current = allUsers;
    bool foundAny = false; 
    // flag for match profile
     bool firstProfile = true;  
     // flag for first profile
    while (current != nullptr)
    {
        User* other = current->data;

        // skip current user
        if (other->getPhone() == this->getPhone())
        {
            current = current->next;
            continue;
        }

        // skip blocked users
        if (other->isBlocked(this) || this->isBlocked(other))
        {
            current = current->next;
            continue;
        }

        // age preference check
        if (other->getAge() < this->minAge || other->getAge() > this->maxAge)
        {
            current = current->next;
            continue;
        }

        // gender preference check

        //only matters if the other suits you NOT if you suit each other
        bool genderMatch = (this->genderPref == "Both" || other->gender == this->genderPref);
        if (!genderMatch)
        {
            current = current->next;
            continue;
        }

        // distance match
        double distance = calculateDistance(this->lat, this->lon, other->lat, other->lon);
        if (distance > this->maxDis )
        {
            current = current->next;
            continue;
        }

        //  this user matches preferences flag = true
        foundAny = true;

        //  \n only before profiles after  first
        if (!firstProfile)
        {
            // one blank line between profiles
            outFile << "\n"; 
        }
             
        else
        {
            firstProfile = false;
        }
            
        outFile << other->name << " " << other->age;

        if (!other->occupation.empty())
        {
            outFile << "\n" << other->occupation;
        }

        if (!other->education.empty())
        {
            outFile << "\n" << other->education;
        }

        outFile << "\n"; // end of this profile
        current = current->next;
    }
        

    //flag
    if (!foundAny)
    {
        outFile << "There are no users matching with your preference at this moment.\n";
    }
}

// Block someone by phone number
void User::block(string thePhone, Node* allUsers)
{
    // other user in the list
    User* other = findUser(allUsers, thePhone);
    if (other != nullptr)
    {
        // add to linked list
        addBlocked(*other);

        
 // only unmatch if they are actually matched
        StringNode* temp = matches;
        //flag
        bool isMatched = false;

        //traversing through until end 

        while (temp != nullptr)
        {
            if (temp->phone == thePhone)
            {
                isMatched = true;
                break;
            }
            temp = temp->next;
        }

        if (isMatched)
        {
            unmatch(thePhone, allUsers);
        }

        // remove from likes if liked

        StringNode* prev = nullptr;
        StringNode* current = likes;

        while (current != nullptr)
        {
            if (current->phone == thePhone)
            {
                if (prev == nullptr)
                {
                    // node is head of list
                    likes = current->next;
                }
                else
                {
                    prev->next = current->next;
                }
                delete current;
                break;  
            }
            prev = current;
            current = current->next;
        }

    
         prev = nullptr;
        current = likes;

        while (current != nullptr)
        {
            if (current->phone == thePhone)
            {
                if (prev == nullptr)
                {
                    // node is head of list
                    likes = current->next;
                }
                else
                {
                    prev->next = current->next;
                }
                delete current;
                break;  
            }
            prev = current;
            current = current->next;
        }


    }
}
//Show Matches (both swiped right liked by)

void User::showMatches(Node* allUsers, ofstream& outFile)
{StringNode* temp = matches;

    if (!temp)
    {
        outFile << "You do not have any matches at this moment.\n";
        return;
    }

vector<User*> matchedUsers;

    while (temp != nullptr)
    {
        User* matchedUser = findUser(allUsers, temp->phone);
        if (matchedUser != nullptr)
        {
            matchedUsers.push_back(matchedUser);
        }
        temp = temp->next;
    }

    // increasing phone number 
    sort(matchedUsers.begin(), matchedUsers.end(),[](User* a, User* b)
        {
            return a->getPhone() < b->getPhone();
        });

    // printing this traversing through 
     for (size_t i = 0; i < matchedUsers.size(); i++)
    {
        User* u = matchedUsers[i];
        outFile << u->getName() << " " << u->getAge();

        if (!u->occupation.empty())
        {
            outFile << "\n" << u->occupation;
        }
            

        if (!u->education.empty())
        {
            outFile << "\n" << u->education;
        }
            

        if (i != matchedUsers.size() - 1)
        {
            outFile << "\n\n";  
            // blank line between users
        }
            
        else
        {
            outFile << "\n";    
            // no extra blank line after last user
            }
    }
}


//Show All Users Who Swiped Right on This User
void User::showRight(Node* allUsers, ofstream& outFile)
{
    //go through all users and their likes and if THIS user phone number in it then add it to a vector to then print 
    if (isPremium== false)
    {
        outFile<< "Only premium users can view who liked you.";
        return;
    }
    Node* temp = allUsers;
    


     // gonna find only the matches using phone number

     //temp vector holding user pointers to print 
    vector<User*> theLiked;
    while (temp != nullptr)
    {
        StringNode* intemp = temp->data->likes;
        while (intemp != nullptr)
        {
            if (intemp->phone == this->phone)
            {
                User* likedUser = findUser(allUsers, temp->data->getPhone());
                if (likedUser)
                {
                    theLiked.push_back(likedUser);
                }
                    
            }
            intemp = intemp->next;
        }
        temp = temp->next;
    }

    if (theLiked.empty())
    {
        outFile<< "You have not received any likes so far.\n";
    }


 // print users who swiped right with extra info
    for (size_t i = 0; i < theLiked.size(); i++)
    {
        User* u = theLiked[i];
        string extra;
        if (!u->occupation.empty())
        {
            extra += "\n" + u->occupation;
        }

        if (!u->education.empty())
        {
            extra += "\n" + u->education;
        }

        outFile << u->name << " " << u->age << extra;

        if (i != theLiked.size() - 1)
        {
           outFile << "\n\n";  
            // blank line between users 
        }
            
        else
        {
             outFile << "\n";    
            // no extra blank line after last user
        }
           
    }



return;
}


//Unmatch Someone

void User::unmatch(string thePhone,Node* allUsers)
{
    
    // find otherUser
    User* other = findUser(allUsers, thePhone);
    if (other == nullptr) 
    {
        return;
    }

    // remove from thisUser matches
    StringNode* prev = nullptr;
    StringNode* curr = matches;
    while (curr != nullptr)
    {
        if (curr->phone == thePhone)
        {
            if (prev == nullptr)
            {
                matches = curr->next; 
                // head node
            }
                
            else
            {
                prev->next = curr->next;
            }
                
            delete curr;
            break; 
            // remove only first 
        }
        prev = curr;
        curr = curr->next;
    }

    // removing from otherUser
    prev = nullptr;
    curr = other->matches;
    while (curr != nullptr)
    {
        if (curr->phone == this->phone)
        {
            if (prev == nullptr)
                other->matches = curr->next;
            else
            {
                prev->next = curr->next;
            }
                
            delete curr;
            break;
        }
        prev = curr;
        curr = curr->next;
    }
}



