#ifndef DRIVERS_H
#define DRIVERS_H 
 
 #include <sstream>
#include <cmath>
#include <iostream> 
#include <fstream>
#include <vector>
#include <string>
//for std::cout
using namespace std;

class Drivers 
{
    private: 
            string first;
            string last; 
            int age; 
            string phone ; 
            double rating ; 
            double theLat ; 
            double theLong ; 
            string vehicle ; 
            string state ; 
            string riderFirst;
            string riderLast ; 
            string riderPhone; 
            string gender;

 public:
        Drivers(string firstName, string lastName, string theGender, int theAge, string thePhone, 
        double theRating, double newLat, double newLong, string vehicleType, string theState, string riderFirstName = "",
        string riderLastName = "", string riderPhoneNum = "")
            {
                first = firstName;
                last = lastName; 
                age = theAge; 
                phone = thePhone; 
                rating = theRating; 
                theLat = newLat; 
                theLong = newLong; 
                vehicle = vehicleType; 
                state = theState; 
                riderFirst= riderFirstName;
                riderLast = riderLastName; 
                riderPhone = riderPhoneNum; 
                gender = theGender;
            }

            bool available();
            string getGender();
            void setGender(string newGen);
            string getFirstName();
            void setFirst(string newFirst);
            string getLastName();
            void setLast(string newLast);
            int getAge();
            void setAge(int newAge);
            string getPhone();
            void setPhone(string newPhone);
            double getRating();
            void setRating(double newRating);
            double getLat();
            void setLat(double newLat);
            double getLong();
            void setLong(double newLong);
            string getVehicle();
            void setVehicle(string newVehicle);
            string getState();
            void setState(string newState);
            string getRiderFirst();
            void setRiderFirst(string newFirst);
            string getRiderLast();
            void setRiderLast(string newLast);
            string getRiderPhone();
            void setRiderPhone(string newPhone);
};
#endif