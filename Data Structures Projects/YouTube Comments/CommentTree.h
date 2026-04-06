#ifndef COMMENTTREE_H
#define COMMENTTREE_H

#include "Comment.h"
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>

using namespace std;

class CommentTree
{
    private:

        vector<Comment*> roots;
        // comments to video in vector
        //multiple children can happen


        unordered_map<string, Comment*> lookup; 
        // fast ID search of all of the comment ids in tree

    public:
        CommentTree();

        //destructor for memory
        ~CommentTree();
        // building tree
        
        //add root and add children to tree 
        void addRoot(Comment* c);

        void addReply(string parent_id, Comment* c);

        // actions/operations
        void likeComment(string id);
        void deleteComment(string id);
        
        void displayComment(string id, ofstream& out);
        void addNewReply(string parent_id, Comment* c);


        // find the comment using id for the map lookup
        Comment* find(string id);

        // delete the tree using recursive function
        //goes through each of the tree sub
        void deleteSubtree(Comment* node);

    };

#endif