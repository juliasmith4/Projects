#ifndef NODE_H
#define NODE_H
class User;
#include <string>

using namespace std;


struct Node
{
    User* data;  
     // pointer to User object
    Node* next;

    Node(User* theUser)
    {
        data = theUser;
        next = nullptr;
    }
};

#endif