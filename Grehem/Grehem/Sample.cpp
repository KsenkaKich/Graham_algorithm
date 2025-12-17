#include <iostream>
#include <vector>
#include <random>
#include "Experiment.h"

using namespace std;

int main() {
    int choice;

    cout << "1. Experiment 3.1" << endl;
    cout << "q = 10^6, w = 10^6" << endl;
    cout << "n = 1 to 10^6+1 (step 10^4)" << endl;
    cout << endl;
    cout << "2. Experiment 3.2" << endl;
    cout << "n = 10^6" << endl;
    cout << "q = w = 0 to 10^6 (step 10^4)" << endl;
    cout << endl;
    cout << "3. Run Interactive mode" << endl;
    cout << endl;
    cout << "4. Run mode with points" << endl;
    cout << endl;
    cout << "0. Exit" << endl;
    cout << endl;
    cout << "Select 0-4: ";
    cin >> choice;
    cout << endl;

    switch (choice) {
    case 1:
        experiment3_1();
        break;

    case 2:
        experiment3_2();
        break;

    case 3:
        interactiveMode();
        break;

    case 4:
        manualConvexHull();
        break;

    case 0:
        cout << "Exiting program." << endl;
        break;

    default:
        cout << "Invalid choice! Please select 0-4." << endl;
        break;
    }
    return 0;
}