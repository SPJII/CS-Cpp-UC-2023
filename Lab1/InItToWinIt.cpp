/*
This program was made by: Steven Paul Jones II

The program is designed to help you enter the In It To Win It competition.

The first line of output should contain (only) the type of competition that you are entering. 
Your choices are limited to Air Guitar, Air Drum, Karaoke. 
You must choose from one of these three competitions and you must capitalize and spell your choice exactly as it is shown.

The second line of output should contain (only) the name of the song that you are going to perform.

The third line of output should contain the name of the song's (real) performer, prefixed with the string As performed by:.
The fourth line of output should contain the number's run time, prefixed with the string Time:.

Example output:
Karaoke
Brian Wilson
As performed by: Barenaked Ladies
Time: 4:48
*/ 
#include <iostream>
#include <string>
using namespace std;
int main() {
   string competitionType;
   string songName;
   string songPerformer;
   string songTime;
//Your Choices goes here
   competitionType = "Karaoke";
//This is the song was written and sung by the soudcloud user Saint Mercator
   songName = "Da Biggest Bird";
   songPerformer = "Saint Mercator";
   songTime = "2:26";
// This prints out the results
   cout << competitionType << endl;
   cout << songName << endl;
   cout << "As performed by: " << songPerformer<< "\n";
   cout << "Time: " << songTime << "\n";
   return 0;
}