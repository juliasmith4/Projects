#include <sstream>
#include <cmath>
#include <iostream> 
#include <fstream>
#include <vector>
#include <string>
//for std::cout
using namespace std;

//include classes
#include "Drivers.h"
#include "Riders.h"



//function from hw file discord
double calculateDistance(double lat1, double lon1, double lat2, double lon2) 
{
    const double radiusOfEarth = 6371.0; // Earth's radius in kilometers

    // convert latitude and longitude from degrees to radians
    lat1 *= M_PI / 180.0;
    lon1 *= M_PI / 180.0;
    lat2 *= M_PI / 180.0;
    lon2 *= M_PI / 180.0;

    // Haversine formula
    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;
    double a = sin(dLat / 2.0) * sin(dLat / 2.0) + cos(lat1) * cos(lat2) * sin(dLon / 2.0) * sin(dLon / 2.0);
    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
    // distance in kilometers
    double distanceKM = radiusOfEarth * c;
    // convert it to distance in miles
    double distanceMiles = distanceKM * 0.621371;

    return distanceMiles;
}

//void function for when the rider requests, takes phone to find the rider themselves and the files to output, along with the vectors
void request(string phoneNum, vector<Drivers>& drivers, vector<Riders>& riders, string messageFileName, string driverFileName, string riderFileName )
{
    ofstream out(messageFileName);
    bool hasDash = false;
    for (int i = 0; i < phoneNum.length(); i++) 
    {
        if (phoneNum[i] == '-') 
        {
            hasDash = true;
            break; 
            //if found dash
        }
    }
    //prints invalid 
    if (!hasDash) {
        out << "Phone number is invalid.\n";
        return; 
    }

    int riderPos = -1;
    for (int i = 0; i < riders.size(); i++)
    {
        if (riders[i].getPhone() == phoneNum) 
        {
            riderPos = i;
        }
    }

    //if rider is not found in the phones, NA
    if (riderPos == -1) 
    { 
        out << "Account does not exist."; 
        return; 
    }

    //if theyre already getting a ride they cant request
    if (riders[riderPos].getState() == "Driver_on_the_way") 
    {
        out << "You have already requested a ride and your driver is on the way to the pickup location.\n";
        return;
    }

    //if theyre on the drive they cant request  ^^ all of these are written to the  file 
    if (riders[riderPos].getState() == "During_the_trip") 
    {
        out << "You can not request a ride at this moment as you are already on a trip.\n";
        return;
    }

    //get the type of vehicle they want 
    string vehicleType = riders[riderPos].getVehicle();
    //big number to start as the min 
    double minDistance = 10000000000;
    //-1 if none is found so it starts with -1
    int driverPos = -1;
    //loop through the drivers vector and find the driver with the same vehicle type and the minimum distance 
    for (int i = 0; i < drivers.size(); i++) 
    {   
        //find the distance 
        double totalDistance = calculateDistance(drivers[i].getLat(), drivers[i].getLong(), riders[riderPos].getPickLat(), riders[riderPos].getPickLong());
        //if it is the same vehicle type, available, and less distancethan previous driver then it is reset to this driver
        if (drivers[i].getState() == "Available" && drivers[i].getVehicle() == vehicleType && totalDistance < minDistance)
        {
            minDistance = totalDistance;
            driverPos = i;
        }
    }
    
    //if there is no driver that can take the request it returns this, -1 means didnt find 
    if (driverPos == -1) 
    { 
        out << "Ride requested for rider " << riders[riderPos].getFirst() << ", looking for";
    if (vehicleType== "Luxury" || vehicleType == "Standard" ||  vehicleType == "Premium")
    {
        out <<  " a " << vehicleType << " vehicle.\n";
    }
    else{
        out <<  " an " << vehicleType << " vehicle.\n";
    }
        out << "Pick Up Location: " << riders[riderPos].getPickup()
            << ", Drop Off Location: " << riders[riderPos].getDrop() << ".\n";
        
         out << "Sorry we can not find a driver for you at this moment.\n"; 
        return; 
    }

    //else it is found and update all of the informations
    out << "Ride requested for rider " << riders[riderPos].getFirst() << ", looking for";
    if (vehicleType== "Luxury" || vehicleType == "Standard" ||  vehicleType == "Premium")
    {
        out <<  " a " << vehicleType << " vehicle.\n";
    }
    else{
        out <<  " an " << vehicleType << " vehicle.\n";
    }

    //updating driver
    drivers[driverPos].setState("On_the_way_to_pickup");
    drivers[driverPos].setRiderFirst(riders[riderPos].getFirst());
    drivers[driverPos].setRiderLast(riders[riderPos].getLast());
    drivers[driverPos].setRiderPhone(riders[riderPos].getPhone());

    //updating rider
    riders[riderPos].setState("Driver_on_the_way");
    riders[riderPos].setDriverFirst(drivers[driverPos].getFirstName());
    riders[riderPos].setDriverLast(drivers[driverPos].getLastName());
    riders[riderPos].setDriverPhone(drivers[driverPos].getPhone());
    out << "Pick Up Location: " << riders[riderPos].getPickup()
    << ", Drop Off Location: " << riders[riderPos].getDrop() << ".\n";

    out << "We have found the closest driver " << drivers[driverPos].getFirstName()
    << "(" << drivers[driverPos].getRating() << ") for you.\n";

    double distance = calculateDistance(drivers[driverPos].getLat(), drivers[driverPos].getLong(),riders[riderPos].getPickLat(),
       riders[riderPos].getPickLong());
    distance = static_cast<int>(distance * 10) / 10.0;
        out << drivers[driverPos].getFirstName() << " is now " << distance << " miles away from you.\n";

}

//cancel function for action
void cancel(string phoneNum, vector<Drivers>& drivers, vector<Riders>& riders, string messageFileName, string driverFileName, string riderFileName )
{

    ofstream out(messageFileName);
    bool hasDash = false;
    for (int i = 0; i < phoneNum.length(); i++) 
    {
        if (phoneNum[i] == '-') 
        {
            hasDash = true;
            break; 
            //if found dash
        }
    }
    //prints invalid 
    if (!hasDash) {
        out << "Phone number is invalid.\n";
        return; 
    }
    int riderPos = -1;
    int driverPos = -1;

    // Find rider by phone
    for (int i = 0; i < riders.size(); i++) 
        {
            if (riders[i].getPhone() == phoneNum)
            {
                riderPos = i;
                break;
            }
        }
        // Find driver by phone
        for (int i = 0; i < drivers.size(); i++) 
        {
            if (drivers[i].getPhone() == phoneNum) 
            {
                driverPos = i;
                break;
            }
        }
        // Account not found
        if (riderPos == -1 && driverPos == -1) 
        {
            out << "Account does not exist.\n";
            return;
        }
        // Rider cancelling
        if (riderPos != -1) 
        {
            if (riders[riderPos].getState() != "Driver_on_the_way") 
            {
                out << "You can only cancel a ride request if your driver is currently on the way to the pickup location.\n";
                return;
            }
            int assignedDriver = -1;
            for (int i = 0; i < drivers.size(); i++) 
            {
                if (drivers[i].getRiderPhone() == riders[riderPos].getPhone())
                {
                    assignedDriver = i;
                    break;
                }
            }

            if (assignedDriver != -1) 
            {   
                out << "Ride request for rider " << riders[riderPos].getFirst() << " is now canceled by the rider.\n";
                drivers[assignedDriver].setState("Available");
                drivers[assignedDriver].setRiderFirst("");
                drivers[assignedDriver].setRiderLast("");
                drivers[assignedDriver].setRiderPhone("");
            }
            riders[riderPos].setState("Ready_to_request");
            riders[riderPos].setDriverFirst("");
            riders[riderPos].setDriverLast("");
            riders[riderPos].setDriverPhone("");

        }

        // Driver cancelling
        if (driverPos != -1) 
        {           
            //only allow cancellation if driver has a rider assigned
            if (drivers[driverPos].getState() != "On_the_way_to_pickup") 
            {
                out << "You can only cancel a ride request if you are currently on the way to the pickup location.\n";
                return;
            }

            int assignedRider = -1;
            for (int i = 0; i < riders.size(); i++) 
            {
                if (riders[i].getDriverPhone() == drivers[driverPos].getPhone())   
                {
                    assignedRider = i;
                    break;
                }
            }
            if (assignedRider != -1)
            {            
                out << "Your driver " << riders[assignedRider].getDriverFirst()<<" has canceled the ride request. We will now find a new driver for you.\n";
            }
            
            //reset drivers stats
            drivers[driverPos].setState("Available");
            drivers[driverPos].setRiderFirst("");
            drivers[driverPos].setRiderLast("");
            drivers[driverPos].setRiderPhone("");

            if (assignedRider != -1)
            {
                //reset the rider's stats
                riders[assignedRider].setState("Ready_to_request");
                riders[assignedRider].setDriverFirst("");
                riders[assignedRider].setDriverLast("");
                riders[assignedRider].setDriverPhone("");

            //if it was the driver who cancelled then request is called so that the rider gets their ride back
                
            //get the type of vehicle they want 

            string vehicleType = riders[assignedRider].getVehicle();


            //big number to start as the min 
            double minDistance = 10000000000;

    //loop through the drivers vector and find the driver with the same vehicle type and the minimum distance 
    for (int i = 0; i < drivers.size(); i++) 
    {   
        //find the distance 
        double totalDistance = calculateDistance(drivers[i].getLat(), drivers[i].getLong(), riders[assignedRider].getPickLat(), riders[assignedRider].getPickLong());
       
        //if it is the same vehicle type, available, and less distancethan previous driver then it is reset to this driver
        if (drivers[i].getState() == "Available" && drivers[i].getVehicle() == vehicleType && totalDistance < minDistance)
        {
            minDistance = totalDistance;
            driverPos = i;
        }
    }

    //if there is no driver that can take the request it returns this, -1 means didnt find 
    if (driverPos == -1) 
    { 
       out << "Ride requested for rider " << riders[assignedRider].getFirst() << ", looking for";
    if (vehicleType== "Luxury" || vehicleType == "Standard" ||  vehicleType == "Premium")
    {
        out <<  " a " << vehicleType << " vehicle.\n";
    }
    else{
        out <<  " an " << vehicleType << " vehicle.\n";
    }
        out << "Pick Up Location: " << riders[assignedRider].getPickup()
            << ", Drop Off Location: " << riders[assignedRider].getDrop() << ".\n";
        out << "Sorry we can not find a driver for you at this moment.\n"; 
        return; 
    }

    //else it is found and update all of the informations
    out << "Ride requested for rider " << riders[assignedRider].getFirst() << ", looking for";
    if (vehicleType== "Luxury" || vehicleType == "Standard" ||  vehicleType == "Premium")
    {
        out <<  " a " << vehicleType << " vehicle.\n";
    }
    else{
        out <<  " an " << vehicleType << " vehicle.\n";
    }
    

    //updating driver
    drivers[driverPos].setState("On_the_way_to_pickup");

    drivers[driverPos].setRiderFirst(riders[assignedRider ].getFirst());

    drivers[driverPos].setRiderLast(riders[assignedRider ].getLast());

    drivers[driverPos].setRiderPhone(riders[assignedRider ].getPhone());

    //updating rider
    riders[assignedRider ].setState("Driver_on_the_way");

    riders[assignedRider ].setDriverFirst(drivers[driverPos].getFirstName());

    riders[assignedRider ].setDriverLast(drivers[driverPos].getLastName());

    riders[assignedRider ].setDriverPhone(drivers[driverPos].getPhone());
    double distance = calculateDistance(drivers[driverPos].getLat(), drivers[driverPos].getLong(),riders[assignedRider].getPickLat(),
         riders[assignedRider].getPickLong());
    distance = static_cast<int>(distance * 10) / 10.0;
    out << "Pick Up Location: " << riders[assignedRider].getPickup()
        << ", Drop Off Location: " << riders[assignedRider].getDrop() << ".\n";

    out << "We have found the closest driver " << drivers[driverPos].getFirstName()
        << "(" << drivers[driverPos].getRating() << ") for you.\n";

    out << drivers[driverPos].getFirstName() << " is now " << distance << " miles away from you.\n";

    }
    }
    }


void write( vector<Drivers>& drivers, vector<Riders>& riders,  string& riderFileName, string& driverFileName)
 {
    // Write updated drivers file
    ofstream driverOut(driverFileName);

    //looping through drivers and printing vars
    for (Drivers& d : drivers) 
    {
            driverOut << d.getFirstName() << " " << d.getLastName() << " " << d.getGender() << " "
            << d.getAge() << " " << d.getPhone() << " " << d.getRating() << " " << d.getLat() << " "
            << d.getLong() << " " << d.getVehicle() << " " << d.getState() << " ";

            // Check each rider field in case theyre null 
            if (d.getRiderFirst().empty())
            {

            driverOut << "null ";
            }
            else 
            {
                driverOut << d.getRiderFirst() << " ";
            }

            if (d.getRiderLast().empty()) 
            {
                driverOut << "null ";
            }
            else 
            {
                driverOut << d.getRiderLast() << " ";
            }

            if (d.getRiderPhone().empty()) 
            {
                driverOut << "null";
            }
            else
            {
                driverOut << d.getRiderPhone();

            } 

            driverOut << "\n";  
    }

    // write riders file
    ofstream riderOut(riderFileName);
    //looping through riders vector 
    for (Riders& r : riders) 
        {
            riderOut << r.getFirst() << " " << r.getLast() << " "<< r.getGender() << " " << r.getAge() << " " << r.getPhone() << " "
            << r.getRating() << " " << r.getPickup() << " " << r.getPickLat() << " " << r.getPickLong() << " " << r.getDrop() << " "  << r.getDropLat() << " "
             << r.getDropLong() << " "  << r.getVehicle() << " " << r.getState() << " ";

            // check for null drivers
            if (r.getDriverFirst().empty()) 
            {
                riderOut << "null ";
            }

            else
                {
                riderOut << r.getDriverFirst() << " ";
                } 


            if (r.getDriverLast().empty())
            {
                riderOut << "null ";
            } 
            else 
            {
                riderOut << r.getDriverLast() << " ";
            }

            if (r.getDriverPhone().empty()) 
            {
                riderOut << "null";
            }
            else 
            {
                riderOut << r.getDriverPhone();
            }

            riderOut << "\n";  
            // new line

}

}





int main(int argc, char* argv[])
{
    //variables based off of the user inputs 
    

    //safe guard for too many arguments 
    if (argc < 8) 
    { 
        return 1; 
    }

    string driversFileName = argv[1];

    string ridersFileName = argv[2];

    string out0 = argv[3];
    string out1 = argv[4];
    string out2 = argv[5];

    //phone number for the actions in order to find who

    string thePhone = argv[6];
    string action = argv[7];


    //vectors to store objects 

    vector<Drivers> drivers;
    vector<Riders> riders;

    // Read drivers file

    ifstream driversFile(driversFileName);

    string line;
    while (getline(driversFile, line)) 
    {
        // trim trailing spaces

        line.erase(line.find_last_not_of(" \t\r\n") + 1); 

        string first;
        string last;
        string gender;
        string phone;
        string vehicle;
        string state;
        string riderFirst;
        string riderLast; 
        string riderPhone;
        int age; 
        double rating;
        double lat;
        double lon;

        stringstream ss(line);

        ss >> first >> last >> gender >> age >> phone >> rating >> lat >> lon >> vehicle >> state
           >> riderFirst >> riderLast >> riderPhone;


           //safeguard for null arguments 

        if (riderFirst == "null") 
        {
            riderFirst = "";
        }
        if (riderLast == "null") 
        {
            riderLast = "";
        }
        if (riderPhone == "null") 
        {
            riderPhone = "";
        }
        //if string stream didnt work it is a safeguard 
        if (ss.fail()) 
        {  
            continue; 
        }
        //since no nulls add it to the vector of drivers objects
        drivers.push_back(Drivers(first,last,gender,age,phone,rating,lat,lon,vehicle,state,riderFirst,riderLast,riderPhone));
    }
    //close file
    driversFile.close();
    // read riders file
    ifstream ridersFile(ridersFileName);
    //parsing riders file 
    while (getline(ridersFile, line)) {
        // trim trailing spaces
        line.erase(line.find_last_not_of(" \t\r\n") + 1); 
        //vars for string stream for riders
        string first;
        string last;
        string gender;
        string phone;
        string pickup;
        string drop;
        string vehicle;
        string state;
        string driverFirst;
        string driverLast; 
        string driverPhone;
        int age; 
        double rating;
        double pickLat;
        double pickLong;
        double dropLat;
        double dropLong;
        stringstream ss(line);

        //string stream
        ss >> first >> last >> gender >> age >> phone >> rating >> pickup >> pickLat >> pickLong >> drop >> dropLat >> dropLong
           >> vehicle >> state >> driverFirst >> driverLast >> driverPhone;

        //avoiding null arguments 
        if (driverFirst == "null") 
        {
            driverFirst = "";
        }
        if (driverLast == "null")
        {
            driverLast = "";
        } 
        if (driverPhone == "null")
        {
            driverPhone = "";
        }

        //when fails it ends 
        if (ss.fail()) 
        { 
            continue;
        }
        //else it adds rider to vector 
        riders.push_back(Riders(first,last, gender, age,phone,rating, pickup, pickLat,pickLong, drop,dropLat, dropLong, vehicle, state, driverFirst, driverLast, driverPhone));
    }
    //ends ^^

    //close file 
    ridersFile.close();
    if (action == "request") 
    {
        //if action is request then it calls this function
        request(thePhone,drivers,riders,out0,out1,out2);
    }
    else 
    {
        //if it is not request then it must be cancel since there is 2 actions
        cancel(thePhone,drivers,riders,out0,out1,out2); 
    }
    write(drivers, riders,out2, out1);
    //return 0 for success
    return 0;
}
//end main
