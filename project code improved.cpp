#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

// ---------------------- Function Prototypes ----------------------
float getInput(string label);
float calculateProductivity(float useful, float total);
void findMaxMin(float arr[], string names[], float &maxVal, string &maxName,
                float &minVal, string &minName);
void giveSuggestions(float study, float mobile, float sleep, float freeTime);
void saveToFile(float study, float mobile, float sleep, float classes,
                float freeTime, float productivity, string status,
                string maxName, string minName);

// ---------------------- MAIN FUNCTION ----------------------------
int main() {

    cout << "\n     DAILY ROUTINE PRODUCTIVITY ANALYZER\n";
    

    float study = getInput("Study");
    float mobile = getInput("Mobile / Social Media");
    float sleep = getInput("Sleep");
    float classes = getInput("Classes");
    float freeTime = getInput("Free / Wasted Time");

                // Validate total hours
    float totalHours = study + mobile + sleep + classes + freeTime;

    if (totalHours > 24) {
        cout << "\nError: Total hours cannot exceed 24.\n";
        cout << "Please re-run the program with valid inputs.\n";
        return 0;
    }

                // Useful hours
    float sleepScore;
    if (sleep >= 7 && sleep <= 8) sleepScore = 1.0;
    else if (sleep < 6) sleepScore = 0.5;
    else sleepScore = 0.7;

    float usefulHours = study + classes + (sleep * sleepScore);
    float wastedHours = mobile + freeTime;
    float productivity = calculateProductivity(usefulHours, totalHours);

                // Find max/min activity
    float activities[5] = {study, mobile, sleep, classes, freeTime};
    string names[5] = {"Study", "Mobile", "Sleep", "Classes", "Free Time"};

    float maxValue, minValue;
    string maxName, minName;

    findMaxMin(activities, names, maxValue, maxName, minValue, minName);

                // Productivity Status
    string status;
    if (productivity >= 75) status = "Highly Productive";
    else if (productivity >= 50) status = "Moderately Productive";
    else status = "Low Productivity";

               //OUTPUT 
    cout << "\n\n          DAILY SUMMARY        \n";
    cout << fixed << setprecision(2);
    cout << "Total Hours Counted: " << totalHours << " hrs\n";
    cout << "Productivity Score : " << productivity << "%\n";
    cout << "Most Time Spent On : " << maxName << " (" << maxValue << " hrs)\n";
    cout << "Least Time Spent On: " << minName << " (" << minValue << " hrs)\n";
    cout << "Status             : " << status << endl;

    cout << "\n        SUGGESTIONS        \n";
    giveSuggestions(study, mobile, sleep, freeTime);

    // Save to File
    saveToFile(study, mobile, sleep, classes, freeTime, productivity,
               status, maxName, minName);

    cout << "\nRecord saved to 'daily_routine.txt'\n";

    return 0;
}

           //FUNCTION DEFINITIONS 

float getInput(string label) {
    float hours;
    while (true) {
        cout << "Enter hours spent on " << label << ": ";
        cin >> hours;

        if (cin.fail() || hours < 0 || hours > 24) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Enter a number between 0 and 24.\n";
        } 
        else break;
    }
    return hours;
}

float calculateProductivity(float useful, float total) {
    return (useful / total) * 100;
}

void findMaxMin(float arr[], string names[], float &maxVal, string &maxName,
                float &minVal, string &minName) {

    maxVal = arr[0];
    minVal = arr[0];
    maxName = names[0];
    minName = names[0];

    for (int i = 1; i < 5; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
            maxName = names[i];
        }
        if (arr[i] < minVal) {
            minVal = arr[i];
            minName = names[i];
        }
    }
}

void giveSuggestions(float study, float mobile, float sleep, float freeTime) {
    if (mobile > 3)
        cout << "- Reduce mobile usage to stay focused.\n";

    if (study < 2)
        cout << "- Increase study time to improve learning.\n";

    if (sleep < 6)
        cout << "- Increase sleep for better productivity and health.\n";

    if (freeTime > 3)
        cout << "- Reduce wasted time and set stronger daily goals.\n";

    cout << "- Maintain a balanced routine.\n";
}

void saveToFile(float study, float mobile, float sleep, float classes,
                float freeTime, float productivity, string status,
                string maxName, string minName) {

    ofstream file("daily_routine.txt", ios::app);

    file << "----- New Entry -----\n";
    file << "Study: " << study << " hrs\n";
    file << "Mobile: " << mobile << " hrs\n";
    file << "Sleep: " << sleep << " hrs\n";
    file << "Classes: " << classes << " hrs\n";
    file << "Free Time: " << freeTime << " hrs\n";
    file << "Productivity: " << productivity << "%\n";
    file << "Status: " << status << "\n";
    file << "Most Time: " << maxName << "\n";
    file << "Least Time: " << minName << "\n\n";

    file.close();
}

