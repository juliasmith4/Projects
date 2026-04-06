 
  #include "Drivers.h"

 #include <sstream>
#include <cmath>
#include <iostream> 
#include <fstream>
#include <vector>
#include <string>
//for std::cout
using namespace std;


            bool Drivers::available()
            {
                if (getRiderFirst() == "")
                {
                    return true;
                }
                return false;
            }
            string Drivers::getGender()
            {
            return gender;
            }

            void Drivers::setGender(string newGen)
            {
                gender = newGen; 
            }

            string Drivers::getFirstName()
            {
                return first;
            }

            void Drivers::setFirst(string newFirst)
            {
                first = newFirst; 
            }
            string Drivers::getLastName()
            {
                return last; 
            }
            void Drivers::setLast(string newLast)
            {
                last = newLast; 
            }

            int Drivers::getAge()
            {
                return age;
            }
            void Drivers::setAge(int newAge)
            {
                age = newAge; 
            }

            string Drivers::getPhone()
            {
                return phone; 

            }
            void Drivers::setPhone(string newPhone)
            {
                phone = newPhone; 
            }

            double Drivers::getRating()
            {
                return rating; 
            }
            void Drivers::setRating(double newRating)
            {
                rating = newRating; 
            }

            double Drivers::getLat()
            {
                return theLat;
            }
            void Drivers::setLat(double newLat)
            {
                theLat = newLat; 
            }
            double Drivers::getLong()
            {
                return theLong; 
            }
            void Drivers::setLong(double newLong)
            {
                theLong = newLong; 
            }

            string Drivers::getVehicle()
            {
                return vehicle; 
            
            }
            void Drivers::setVehicle(string newVehicle)
            {
                vehicle = newVehicle; 
            }
            string Drivers::getState()
            {
                return state;

            }
            void Drivers::setState(string newState)
            {
                state = newState; 
            }
            string Drivers::getRiderFirst()
            {
                return riderFirst;
            }
            void Drivers::setRiderFirst(string newFirst)
            {
                riderFirst = newFirst; 
            }
            string Drivers::getRiderLast()
            {
                return riderLast;
            }
            void Drivers::setRiderLast(string newLast)
            {
                riderLast = newLast; 
            }
            string Drivers::getRiderPhone()
            {
                return riderPhone;
            }
            void Drivers::setRiderPhone(string newPhone)
            {
                riderPhone = newPhone; 
            }

