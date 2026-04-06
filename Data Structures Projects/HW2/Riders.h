#ifndef RIDERS_H
#define RIDERS_H
 #include <sstream>
#include <cmath>
#include <iostream> 
#include <fstream>
#include <vector>
#include <string>
//for std::cout
using namespace std;
class Riders
{
    private:
        string first ; 
        string last ; 
        string gender ; 
        int age ; 
        string phone; 
        double rating ; 
        string pickup ; 
        double pickLat; 
        double pickLong; 
        string drop ; 
        double dropLat ; 
        double dropLong; 
        string vehicle ; 
        string state ; 
        string driverFirst ;
        string driverLast;
        string driverPhone;
    
    public: 
        Riders(string firstName, string lastName, string theGender,
        int theAge, string thePhone, double theRating, string thePickup, double thePickLat, double thePickLong, 
        string theDrop, double theDropLat, double theDropLong, string theVehicle, string theState, 
        string theDriverFirst = "", string theDriverLast ="", string theDriverPhone = "" )
    {   
        //^^ if no paremeters for drivers it is ""

        //riders vars
         first = firstName; 
         last = lastName; 
         gender = theGender; 
         age = theAge; 
         phone = thePhone; 
         rating = theRating; 
         pickup = thePickup; 
         pickLat = thePickLat; 
         pickLong = thePickLong; 
         drop = theDrop; 
         dropLat = theDropLat; 
         dropLong = theDropLong; 
         vehicle = theVehicle; 
         state = theState; 

        //drivers for riders, can be null
         driverFirst = theDriverFirst; 
         driverLast = theDriverLast;
         driverPhone = theDriverPhone;
    }

    //functions to set and access, setters and getters
    string getFirst();
    void setFirst(string newFirst);
    string getLast();
    void setLast (string newLast);
    string getGender();
    void setGender(string newGen);
    int getAge();
    void setAge(int newAge);
    string getPhone();
    void setPhone(string newPhone);
    double getRating();
    void setRating(double newRating);
    string getPickup();
    void setPickup(string newPickup);
    double getPickLat();
    void setPickLong(double newPickLong);
    double getPickLong();
    void setPickLat(double newPickLat);
    string getDrop();
    void setDrop(string newDrop);
    double getDropLat();
    void setDropLat(double newLat);
    double getDropLong();
    void setDropLong(double newDrop);
    string getVehicle();
    void setVehicle(string newVehicle);
    string getState();
    void setState(string newState);
    string getDriverFirst();
    void setDriverFirst(string newFirst);
       string getDriverLast();
    void setDriverLast(string newLast);
    void setDriverPhone(string newPhone);
    string getDriverPhone();
};
#endif