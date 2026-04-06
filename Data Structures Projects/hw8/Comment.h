#ifndef COMMENT_H
#define COMMENT_H
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Comment
{
    private:
        string comment_id;
        string author;
        string content;
        int like_count;
        int reply_count;

        /*
        "published_date": "7 hours ago (edited)"
        keep track of edited status 

        */
        string published_date;
        bool is_video_owner;
        bool edited;

        //pointer to parent comment for reply comments 
        Comment* parent;

        //vector of children since it can have multiple children 
        vector<Comment*> children;

    public:
        // constructors
        Comment();
        Comment(string id, string user, string text, int likes, string date, int replies);
        
        // getters
        string getID() const;

        string getAuthor() const;

        string getContent() const;

        int getLikes() const;
        bool isEdited() const;

        string getPublishedDate() const;

        bool isVideoOwner() const;
        void deleteReplyCount();

        //for parent and children getters
        Comment* getParent() const;
        vector<Comment*>& getChildren();

        // setters / actions
        void addChild(Comment* child);

        void addLike();
        void setComment(string comment);
        void addReplyCount();

        // recursive functions
        void display(int indent, ofstream& out);


    };

#endif



