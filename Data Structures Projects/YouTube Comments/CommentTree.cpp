#include "CommentTree.h"

//no argument constructor each of them just initialize themselves as default values 
//map and vector are just empty
CommentTree::CommentTree()
{
}


//destructor for memory clearance 

CommentTree::~CommentTree()
{
    //loop through the roots and delete the subtrees
    for (size_t i = 0; i < roots.size(); i++)
    {

        //deleting the tree 
        deleteSubtree(roots[i]);

    }


    //clearing the vector and map 
    roots.clear();

    lookup.clear();
}


//add root to the tree and add it to map for searching 
void CommentTree::addRoot(Comment* c)
{
    //push back and then ge thte id of the comment and add it to map 
    roots.push_back(c);

    //lookup map fast search 
    lookup[c->getID()] = c;
}





//add a reply to the tree by getting id of parent and then adding the comment c to it as a child
void CommentTree::addReply(string parent_id, Comment* c)
{

    //find the comment with parent id
    Comment* parent = find(parent_id);

    //if parent is found then update the map and add the child to the parent 
    if (parent != nullptr)
    {

        //add child to the parnet id adn then add the map for new reply
        parent->addChild(c);

        lookup[c->getID()] = c;


    }

}
void CommentTree::addNewReply(string parent_id, Comment* c)
{

    //find the comment with parent id
    Comment* parent = find(parent_id);

    //if parent is found then update the map and add the child to the parent 
    if (parent != nullptr)
    {

        //add child to the parnet id adn then add the map for new reply
        parent->addChild(c);
        parent->addReplyCount();

        lookup[c->getID()] = c;


    }

}

//like comment action using id of the comment getting increased like
void CommentTree::likeComment(string id)
{

    //find the comment 
    Comment* c = find(id);


    //if found the commend using find id of the map then call add like comment function 
    //increaase like count
    if (c != nullptr)
    {

        //increase like count 
        c->addLike();

    }
}


//delete comment action
//id is of comment getting deleted as arg
void CommentTree::deleteComment(string id)
{

    //find comment using id and map 
    Comment* comment = find(id);

    //return nothing if not found
    if (comment == nullptr)
    {
        return;
    }

    //if there is no parent it is the root and can have children 

    if (comment->getParent() == nullptr)
    {

        //get rid of the children then delete the root
        for (int i = 0; i < roots.size(); i++)
        {

            //if the root is the node to delete then erase it then break out 
            if (roots[i] == comment)
            {
                roots.erase(roots.begin() + i);
                break;

            }

        }


    }


    //if it is a reply comment
    else
    {


       
        vector<Comment*>& children = comment->getParent()->getChildren();
        comment->getParent()->deleteReplyCount();
        for (int i = 0; i < children.size(); i++)
        {
            if (children[i] == comment)
            {
                children.erase(children.begin() + i);
                break;
            }
        }
    }

//then delete the subtree to delete all of the children and the comment itself
    deleteSubtree(comment);
}



//display comment and all of children if there are any 
//write it to outfile 

//outfile and id are args
void CommentTree::displayComment(string id, ofstream& out)
{

    //find the comment using id 
    Comment* thisComment = find(id);

    //if it exists then display it with the indent of 0 since its the parent/first 
    if (thisComment != nullptr)
    {
        thisComment->display(0, out);
    }
}



//find the id of a comment using the map 
//map holds all of the ids and the comment objects
Comment* CommentTree::find(string id)
{

    //find the id in the map then return the value which is the object
    unordered_map<string, Comment*>::iterator it = lookup.find(id);

    if (it != lookup.end())
    {
        return it->second;
    }

    //else return null
    return nullptr;
}



//delete the subtrees

void CommentTree::deleteSubtree(Comment* node)
{

    //base case if there is nothing then return nothing 

    if (node == nullptr)
    {
        return;

    }


    //get vector of the children of the node
    //use get children func
    vector<Comment*>& kids = node->getChildren();



    //loop through it and delete that child and all of its children by recursively calling delete 
    for (int i = 0; i < kids.size(); i++)
    {
        deleteSubtree(kids[i]);
    }


    //then erase it from the map and delete THIS node 

    lookup.erase(node->getID());
    delete node;
}


