#include <iostream>
#include <fstream>
#include <sstream>
#include "CommentTree.h"
#include "Comment.h"

using namespace std;

int main(int argc, char* argv[])
{
    //error checking for correct # of arg
    if (argc != 4)
    {
        return 1;
    }

    string jsonFileName = argv[1];
    string opsFileName = argv[2];
    string outputFileName = argv[3];

    ifstream json(jsonFileName);   
    // JSON input
    ifstream in(opsFileName);      
    // operations/actions file
    ofstream out(outputFileName); 
     //  write to output file


    CommentTree tree;

    string line;


    // read JSON
    while (getline(json, line))
    {

        //find the json vals and skip the id based on the length of each of the vals
        //"author: == 11"

        //get each of the vals for the variables this way in the json

        //loop through using get line



   



        //adding reply count
          //find the pos of the val 
        size_t pos_author = line.find("\"author\": \"");
        pos_author += 11;

        //find the end 
        size_t end_author = line.find("\"", pos_author);

        string author = line.substr(pos_author, end_author - pos_author);







        //do the same for the rest
        size_t pos_id = line.find("\"comment_id\": \"");
        pos_id += 15;
        size_t end_id = line.find("\"", pos_id);
        string comment_id = line.substr(pos_id, end_id - pos_id);


        size_t pos_parent = line.find("\"parent_comment_id\": \"");
        pos_parent += 22;

        size_t end_parent = line.find("\"", pos_parent);

        string parent_id = line.substr(pos_parent, end_parent - pos_parent);

        size_t pos_comment = line.find("\"comment\": \"");
        pos_comment += 12;

        size_t end_comment = line.rfind("\"");

        string content = line.substr(pos_comment, end_comment - pos_comment);

        size_t pos_reply = line.find("\"is_reply\": ");

        pos_reply += 12;

        bool is_reply = (line.substr(pos_reply, 4) == "true");
            
        size_t pos_like = line.find("\"like_count\": ");
        pos_like += 14;

        size_t end_like = line.find(",", pos_like);

        string like_string = line.substr(pos_like, end_like - pos_like);
        int like_count = stoi(like_string);



        /*
 size_t pos_like = line.find("\"like_count\": ");
        pos_like += 14;

        size_t end_like = line.find(",", pos_like);

        string like_string = line.substr(pos_like, end_like - pos_like);
        int like_count = stoi(like_string);

*/

     //find the pos of the val
     //treat it like like count 
        size_t pos_replyC = line.find("\"reply_count\": ");
        pos_replyC += 15;

        //find the end 
        size_t end_replyC = line.find(",", pos_replyC);

        string reply_count = line.substr(pos_replyC, end_replyC - pos_replyC);
        int replies = stoi(reply_count);

        size_t pos_date = line.find("\"published_date\": \"");
        pos_date += 19;

        size_t end_date = line.find("\"", pos_date);

        string published_date = line.substr(pos_date, end_date - pos_date);


        Comment* newComment = new Comment(comment_id, author, content, like_count, published_date, replies);

        //if it is not a reply it is its own root
        //else it is a reply then add it as child to parent
        //
                if (!is_reply)
                {
                    tree.addRoot(newComment);
                }
                else
                {
                    tree.addReply(parent_id, newComment);
                }
    }


    // operations
    string command;

    //while there is commands
    while (in >> command)
    {

        //if it is a reply 
        if (command == "reply_to_video")
        {
            //get the vals of the variables, create a comment, then add it as a root because its a normal reply to a video 
            string id, user, text;

            in >> id >> user;
            in >> ws;

            getline(in, text, '"');
            getline(in, text, '"');

            Comment* c = new Comment(id, user, text,0, "0 seconds ago", 0);
            tree.addRoot(c);


        }


        //reply to comment then it will be added as a child to a parent comm
        else if (command == "reply_to_comment")
        {

            //get vars for the comment, create the comment, then add it as a reply to another parent comment after finding it with the 
            //parent id

            string parent_id, id, user, text;

            in >> parent_id >> id >> user;
            in >> ws;

            getline(in, text, '"');
            getline(in, text, '"');


            //all actions are 0 seconds ago and not edited when created

            Comment* c = new Comment(id, user, text, 0,"0 seconds ago",0);
            tree.addNewReply(parent_id, c);



        }


        //liking comment find the other commend using id, then like the comment by increasing like count 
        else if (command == "like_comment")
        {
            //get the id
            string id;
            in >> id;

            tree.likeComment(id);
        }

        //delete the comment action

        //delete the comment and all of its children if it is parent comment 
        else if (command == "delete_comment")
        {

            //get the id of the comment to delete then delete it 
            //call delete func
            string id;
            in >> id;

            tree.deleteComment(id);


        }

        //display comment and all of children if it is parent 
        else if (command == "display_comment")
        {

            //get id and call display comment using out file and the id of comment
            string id;
            in >> id;

            tree.displayComment(id, out);
        }
    }

    return 0;
}