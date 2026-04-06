#include <iostream> 
#include <fstream>
#include <vector>
#include <string>
//for std::cout
using namespace std;

//functions for the actions 
void add(const string& line, vector<string>& songs)
{
    //this_song is everything after the "add "
    string this_song = line.substr(4); 
    //appends to the end of this_song vector
    songs.push_back(this_song);
}

void remove (const string& line, vector<string>& songs)
{
  //finding this song after "remove "
  string this_song = line.substr(7);

  //going through the songs vector and once finding the song, erase it 
  for (unsigned int i = 0; i < songs.size(); i++)
  {
    if (songs[i] == this_song)           
    {
      //ending the loop after this in case there are duplicates, so only the first one is removed 
      songs.erase(songs.begin() + i);
      break;
    }
  }
}

void previous (const string& line, vector<string>& songs)
{
 string this_song = "";
        unsigned int pos = 0;
        //finding what song has "current" in order to get the position
        for (int i = 0; i < songs.size(); i++)
        {
          if (songs[i].find(" current") != -1)
          {
            this_song = songs[i];
            pos = i;
          }
        }
        //if it exists and isnt at the beginning , then we remove current from the current, adn then add it to the previous standing 
        if (pos != 0 && pos != -1)
        {
          songs[pos] = songs[pos].substr(0, songs[pos].length() - 8);
          songs[pos - 1] = songs[pos - 1] + " current";
        }

        else
        {
          //if the current song is at the beginning, the previous song will be the one at the end of the playlist
          int last_pos = songs.size() - 1;
          songs[0] = songs[0].substr(0, songs[0].length() - 8);
          songs[last_pos] = songs[last_pos] + " current";
        }
      }
        
void move (const string& line, vector<string>& songs)
{
  // finding when the song name ends and the space right before the position 
  int last_space = line.rfind(' ');

  //only the song, not artist
  string song_name = line.substr(5, last_space -5);

  //string to int
  int new_pos = stoi(line.substr(last_space + 1)) -1;
  int old_pos = -1;

  //finding the old position of the song
  for (unsigned int i = 0; i < songs.size(); i++) 
    {
      //still moving even if it is the current song, checking for both 
      if (songs[i] == song_name || songs[i] == song_name + " current")
      {
        old_pos = i;
        break;
      }
    } 

  //song not found , then the function continues
  if (old_pos == -1) 
  {
    return;
  }

  //checking the bounds if the position is longer than the playlist, if so making it the last index instead
  if (new_pos >= songs.size())
  {
    new_pos = songs.size() - 1;
  }

  //moving the position of the song now
  //holding the og song, then erasing it
  string temp = songs[old_pos];
  songs.erase(songs.begin() + old_pos);

  //0 indexing 
  if (new_pos > old_pos) 
  {
    new_pos = new_pos - 1;
  }
  songs.insert(songs.begin() + new_pos, temp);
}


void next (const string& line, vector<string>& songs)
{
 string this_song = "";
  int pos = 0;
  //going through the songs to find what the current song is and where it is 
  for (unsigned int i = 0; i < songs.size(); i++)
  {
    //if current exists in the file, we update pos and this_song
    if (songs[i].find(" current") != -1)
    {
      this_song = songs[i];
      pos = i;
    }
  }

  //if pos is within the bounds of the playlist (and not at the end), we make the next song the current song and take current away from this_song
  if (pos < songs.size() - 1)
  {
    songs[pos] = songs[pos].substr(0, songs[pos].length() - 8);
    songs[pos + 1] = songs[pos + 1] + " current";
  }

  //if the song is at the end of the playlist, we make the current song the first song in the playlist
  else
  {
    songs[pos] = songs[pos].substr(0, songs[pos].length() - 8);
    songs[0] = songs[0] + " current";
  }
}


int main(int argc, char* argv[])
{
  //variables based off of the user inputs 
  std::string playlist = std::string(argv[1]);
  std::ifstream this_playlist(playlist);
  std::string actions = std::string(argv[2]);
  std::string output = std::string(argv[3]);

  std::vector<string> songs;
  string line; 


   //going through the initial playlist
   while(getline(this_playlist, line))
	  {
      songs.push_back(line)  ;
    }
    this_playlist.close();

    //going through the actions file 
    std::ifstream this_actions(actions);
    while(getline(this_actions, line))
	{
      //add, which adds a song to the end of the playlist.
      if (line.find("add ") != string::npos)
      {
        add(line, songs);
      } 

      //move, which moves a song to a new position - the new position is always included at the end of the line. 
      else if (line.find("move ") == 0)
      {
        move(line, songs);
      }

      //remove, which removes a song from the playlist.
     else if (line.find("remove") != string::npos)
      {
        remove(line, songs);
      } 


    //next, which skips the currently playing song and starts playing the song that is listed directly after it.
      else if (line.find("next") != string::npos)
      {
        next(line,songs);
      }


   // previous 
    else if (line.find("previous") != string::npos)
    {
      previous(line, songs);
    }
  }

  //writing to the output file the final playlist 
  ofstream out(output);
  for (unsigned int i = 0; i < songs.size(); i++) 
  {
    out << songs[i] << "\n"; 
  }

  // close the file
  out.close(); 

  //end 
  return 0; 
}
