 
  #include "Comment.h"


       //constructor no arguments 
       Comment::Comment()
       {

            //no arg constructor that is just default vals 
              comment_id = "";
              author = "";
              content = "";

              like_count = 0;

              edited = false;

              //no parent 
              parent = nullptr;
            is_video_owner = false;
            published_date = "0 seconds ago";

              //no children yet


       }

       //constructor with arguments

       //craft comment with the vals from the json
      //user name id content like count date 

        Comment::Comment(string id, string user, string text, int likes, string date, int replies)
        {


            //set all of the vals to the args
              comment_id = id;
              author = user;
              content = text;
              like_count = likes;
              edited = false;
              published_date = date;
             is_video_owner = false;
            reply_count  = replies;
              parent = nullptr;


        }

        // getters returning variable vals

        string Comment::getID() const
        {

              return comment_id;
        }

        
        string Comment::getAuthor() const
        {
              return author;

        }


        string Comment::getContent() const
        {

              return content;

        }


        int Comment::getLikes() const
        {

              return like_count;

        }


        //for parent and children getters
        Comment* Comment::getParent() const
        {

              return parent;
        }

        vector<Comment*>& Comment::getChildren()
        {
              return children;

        }



        // setters / actions
        void Comment::addChild(Comment* child)
        {

             

            children.push_back(child);
            child->parent = this;


            //update this child comments parent to be the comment
        }


        void Comment::addLike()
        {
              like_count++;
        }

 void Comment::addReplyCount()
        {
              reply_count++;
        }

 void Comment::deleteReplyCount()
        {
              reply_count--;
        }


        //set the comment content as the comment, edited is true because it was previously made and the date is now updated with the edited stat
        void Comment:: setComment(string comment)
        {
             
                 content = comment;
                 edited = true;
                 published_date = "0 seconds ago (edited)";

              
        }

        //getter for stat and others
              bool Comment::isEdited() const
              {
                     return edited;

              }


        string Comment::getPublishedDate() const
        {
              return published_date;

        }


        bool Comment::isVideoOwner() const
        {
              return is_video_owner;

        }

        //printing 

        /*
        @camyllalopes7173 7 months ago (edited)
Que sensação de paz ouvir essa música. Cada toque da melodia faz me sentir mais leve ❤ fiquei feliz em saber que era o Elton John que cantava ❤
👍 82
6 replies
        */


        void Comment::display(int indent, ofstream& out)
        {

            //indent is times the number of spaces for the indent 
            //to correctly do tree and child 

            //tree root
            //         child

            string spaces = string(indent * 4, ' ');


            //write to outfile this comment with its stats
            out << spaces << author << " " << published_date << endl;
            out << spaces << content << endl;
            out << spaces << "\U0001F44D " << like_count << endl;




          

            //child calls in case it is a parent comment
            if(reply_count >1)
            //if there are mult children 
            {
                              out << spaces << reply_count << " replies" << endl;

            }

            else if (reply_count ==1)
            {
                  //only one child then it is reply not replies
                  out << spaces << reply_count << " reply" << endl;

            }

            //go through each of the children and display its content using the display func
            //increase indent since its a child in the func call

            for (size_t i = 0; i < children.size(); i++)
            {

                  children[i]->display(indent + 1, out);
            }

        }
    