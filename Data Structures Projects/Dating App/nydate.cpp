#include <iostream>
#include <fstream>
#include "User.h"
#include "Node.h"
#include "StringNode.h"
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

Node* readUsersFromFile(const string& filename) 
{
    ifstream inFile(filename);
    if (!inFile) 
    {
        
        return nullptr;
    }

    //setting first and end in the linked list
    Node* head = nullptr;
    Node* tail = nullptr;

    //declaring vars
    string name, gender, phone, occupation, education, genderPref, likesStr;
    int age, minAge, maxAge;
    double lat, lon, maxDis;
    bool isPremium;


    //parsing through the file 

    //bool alpha read t f as bools
    while (inFile >> name >> age >> gender >> phone >> occupation >> education>> lat >> lon >> boolalpha >> isPremium >> minAge >> maxAge >> maxDis >> genderPref >> likesStr) 
    {
        if (occupation == "Undisclosed") 
        {
          occupation = "";
        }
        else
        {
          string result = occupation;
          for (int i = 0; i < result.length(); i++)
            {
              if (result[i] == '_')
              {
                  result[i] = ' ';
              }
            }
            occupation = result;
        }




        //making ed and occ blank if undisclosed
        if (education == "Undisclosed") 
        {
          education = "";
          
        }
        else
        {
          string result = education;
          for (int i = 0; i < result.length(); i++)
            {
              if (result[i] == '_')
              {
                  result[i] = ' ';
              }
            }
            education = result;
        }
        // creating newUser var
        User* newUser = new User(name, age, gender, phone,occupation, education, lat, lon,isPremium, minAge, maxAge, maxDis, genderPref);


        //parse like string using the code from readme
        if (likesStr != "null") 
        {
            std::istringstream iss(likesStr);
            std::string phoneNumber;

            while (std::getline(iss, phoneNumber, '_')) 
            {
                
                StringNode* node = new StringNode(phoneNumber);
                node->next = newUser->likes;
                newUser->likes = node;            
              }
        }

        // add new user to the linked list
        Node* newNode = new Node(newUser);
        if (!head) 
        {

          //first node in list if head is null
          head = tail = newNode;

        }
        else 
        { 
          //if head
          tail->next = newNode; tail = newNode; 
        }
    }

    return head;
}


// makign mataches for the user calling it

//linked list filling in
void makeMatches(Node* allUsers)
{
    Node* temp = allUsers;

    while (temp != nullptr)
    {
      User* user = temp->data;
      StringNode* likeNode = user->getLikes();

      while (likeNode != nullptr)
      {
        User* likedUser = findUser(allUsers, likeNode->phone);
        if (likedUser)
        {
          // Check if likedUser also liked this user
          StringNode* theirLikes = likedUser->getLikes();
          while (theirLikes != nullptr)
          {
            if (theirLikes->phone == user->getPhone())
              {
                //both likedby then it adds match


                 // checking for duplicate
                 StringNode* existing = user->getMatches();

                 //flag
                 bool alreadyMatched = false;
                  while (existing != nullptr)
                 {
                            if (existing->phone == likedUser->getPhone())
                            {
                              //update flag and break
                                alreadyMatched = true;
                                break;
                            }
                            //iterating to next
                            existing = existing->next;
                        }

                        if (!alreadyMatched)
                        {
                          //if not there then add
                            user->addMatch(*likedUser);
                            likedUser->addMatch(*user);
                        }
                    }
                    //next
                    theirLikes = theirLikes->next;
                }
            }
            //next
            likeNode = likeNode->next;
        }
        //next
        temp = temp->next;
    }
}
void addUser(Node*& head, User* newUser)
{
  //newNode is the new user node 
    Node* newNode = new Node(newUser);

  //if there is no user existing previously then this is the new head 

    if(head == nullptr)
    {
        head = newNode;
        return;
    }

    Node* temp = head;
    //loop through until the end, then add the user if it is the end 
    while(temp->next != nullptr)
    {
        temp = temp->next;
    }

    temp->next = newNode;
}

int main(int argc, char* argv[])
{

  
  //variables based off of the user inputs 
    if (argc < 5)
     {
    return 1;
    }

string users = argv[1];
string output = argv[2];
string phone = argv[3];
string action = argv[4];
string theOtherPhone = "";
if (argc>=6)
{
  theOtherPhone = argv[5];
}

// Read users into linked list
    Node* allUsers = readUsersFromFile(users);
    if (!allUsers) 
    {
      return 1;
    }
   
ofstream outFile(output);

//  mutual matches linked list creation
makeMatches(allUsers);

if (!outFile)
{
    
    return 1;
}


User* thisUser = findUser(allUsers, phone);
if (thisUser == nullptr)
{
   
    return 1;
}

// /Show Profiles

if (action == "profile")
{
    thisUser->showProfiles(allUsers,outFile);

}

//Show Matches

if (action == "match")
{
thisUser->showMatches(allUsers, outFile);

}

//Show All Users Who Swiped Right on This User
if (action == "like")
{
    thisUser->showRight(allUsers, outFile);

}

//Unmatch Someone
if (action == "unmatch")
{
  
  // remove each other from matches
   
    thisUser->unmatch(theOtherPhone, allUsers);

    // this user's matches
        outFile <<  thisUser-> getName() << "'s match list:\n\n";
    thisUser->showMatches(allUsers, outFile);

    outFile << "\n======\n\n";

    // other user's matches
    User* otherUser = findUser(allUsers, theOtherPhone);
    if (otherUser != nullptr)
    {
      outFile <<  otherUser->name << "'s match list:\n\n";
      otherUser->showMatches(allUsers, outFile);
    }
        

}
//Block Someone
if (action == "block")
{ 
  User* other = findUser(allUsers, theOtherPhone);
    if (other != nullptr)
    {
        // unmatch
        thisUser->unmatch(theOtherPhone, allUsers);

        //  block
        thisUser->block(theOtherPhone, allUsers);

        // show profiles
        outFile << "profiles shown to " << thisUser->name << ":\n\n";
        thisUser->showProfiles(allUsers, outFile);
        

        outFile << "\n======\n\n";
outFile << "profiles shown to " << other->name << ":\n\n";
        other->showProfiles(allUsers, outFile);
    }
}

//no leaked memory 
//traversing through the linked list and deleting 
 while (allUsers != nullptr)
    {
        Node* temp = allUsers;
        allUsers = allUsers->next;

        // delete user object
        delete temp->data;

        //delete node
        delete temp;
    }
}
