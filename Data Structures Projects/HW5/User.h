#ifndef USER_H
#define USER_H

#include <string>
#include "StringNode.h"
#include "Node.h"  // include Node.h here, AFTER StringNode.h
using namespace std;

class User
{
public:
    // public to access 

    string phone;
    string name;
    int age;
    bool isPremium;
    string gender;

    int minAge;
    int maxAge;
    double maxDis;
    double lat;
    double lon;
    
    string education;
    string occupation;
    string genderPref;
    // linked lists for other user info 

    StringNode* likes;      
    // users this user swiped right on
    StringNode* likedBy;    
    // users who swiped right on this user
    StringNode* matches;    
    //  matches both swiped right 
    StringNode* blocked;    
    // blocked users

    // constructor

    User(string n, int a, string g, string p, string occ, string edu, double la, double lo, bool premium, int minA, int maxA, double maxD, string gPref);

    // destructor 
    ~User();

    //getters and setters 

    //get user information 
    string getPhone();

    string getName();
    int getAge();

    bool getPremium();


    //set user information 

    void setPhone(string newPhone);
    
    void setName(string newName);

    void setAge(int newAge);
    void setPremium(bool newStatus);


    //linked list getters and setters for likes, matches, liked by and blocked 

    void addLikedBy(User& otherUser);
    void addMatch(User& otherUser);


    void addLiked(User& otherUser);


    void addBlocked(User& otherUser);

    StringNode* getLikes();

    StringNode* getMatches();

    StringNode* getlikedBy();

    StringNode* getBlocked();

    bool isBlocked(User* otherUser);
    

void showProfiles(Node* allUsers, ofstream& outFile);

void showMatches(Node* allUsers, ofstream& outFile);

void showRight(Node* allUsers, ofstream& outFile);

void unmatch(string thePhone, Node* allUsers);

void block(string thePhone, Node* allUsers);



};


User* findUser(Node* allUsers,  const string& phone);


#endif