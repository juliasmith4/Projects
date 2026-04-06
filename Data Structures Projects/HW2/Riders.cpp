 #include "Riders.h"
 #include <sstream>
#include <cmath>
#include <iostream> 
#include <fstream>
#include <vector>
#include <string>
//for std::cout
using namespace std;


    //functions to set and access, setters and getters
    string Riders::getFirst()
    {
        return first;
    }
    void Riders::setFirst(string newFirst)
    {
        first = newFirst;
    }


    string Riders::getLast()
    {
        return last;
    }
    void Riders::setLast (string newLast)
    {
        last = newLast;
    }

    string Riders::getGender()
    {
        return gender;
    }
    void Riders::setGender(string newGen)
    {
        gender = newGen; 
    }

    int Riders::getAge()
    {
        return age;

    }

    void Riders::setAge(int newAge)
    {
        age = newAge; 
    }


    string Riders::getPhone()
    {
        return phone;
    }


    void Riders::setPhone(string newPhone)
    {
        phone = newPhone; 
    }

    double Riders::getRating()
    {
        return rating; 
    }
    void Riders::setRating(double newRating)
    {
        rating = newRating; 
    }
    string Riders::getPickup()
    {
        return pickup;
    }
    void Riders::setPickup(string newPickup)
    {
        pickup = newPickup;
    }

    double Riders::getPickLat()
    {
        return pickLat;
    }
    void Riders::setPickLong(double newPickLong)
    {
        pickLong = newPickLong; 
    }
    double Riders::getPickLong()
    {
        return pickLong;
    }
    void Riders::setPickLat(double newPickLat)
    {
        pickLat = newPickLat; 
    }
        

    string Riders::getDrop()
    {
        return drop;
    }

    void Riders::setDrop(string newDrop)
    {
        drop = newDrop; 
    }

    double Riders::getDropLat()
    {
        return dropLat;
    }
    void Riders::setDropLat(double newLat)
    {
        dropLat = newLat; 
    }


    double Riders::getDropLong()
    {
        return dropLong;
    }
    void Riders::setDropLong(double newDrop)
    {
        dropLong = newDrop; 
    }


    string Riders::getVehicle()
    {
        return vehicle; 
    }
    void Riders::setVehicle(string newVehicle)
    {
        vehicle = newVehicle; 
    }

    string Riders::getState()
    {
        return state;
    }
    void Riders::setState(string newState)
    {
        state = newState;
    }
    
    string Riders::getDriverFirst()
    {
        return driverFirst;
    }
    void Riders::setDriverFirst(string newFirst)
    {
        driverFirst = newFirst;
    }
       string Riders::getDriverLast()
    {
        return driverLast;
    }
    void Riders::setDriverLast(string newLast)
    {
        driverLast = newLast;
    }
    void Riders::setDriverPhone(string newPhone)
    {
        driverPhone = newPhone;
    }
    string Riders::getDriverPhone()
    {
        return driverPhone;
    }

