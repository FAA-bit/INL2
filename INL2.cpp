// INL2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "data_manager.h"
#include <iostream>
#include <windows.h>
#include <locale>

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "SV_se");

    DataManager manager;
    manager.loadFromFile("temperatures.csv");

    cout << "Hej! Välkommen till mitt inlämningsuppgift.\n";
    manager.inputMeasurements();

    int val;
    do {
        cout << "\n--- MENY ---\n";
        cout << "1. Lägg till nya mätvärden\n";
        cout << "2. Visa statistiken\n";
        cout << "3. Sortera mätvärden\n";
        cout << "4. Sök efter ett visst värde\n";
        cout << "5. Simulera sensorvärden\n";
        cout << "6. Avsluta\n";
        cout << "Ditt val: ";
        cin >> val;

        switch (val) {
        case 1: manager.inputMeasurements(); break;
        case 2: manager.showStatistics(); break;
        case 3: manager.sortMeasurements(); break;
        case 4: manager.searchValue(); break;
        case 5: manager.simulateSensor(); break;
        case 6: cout << "Avslutar programmet.\n"; break;
        }
    } while (val != 6 && !manager.isFull());

    manager.saveToFile("temperatures.csv");

    if (manager.isFull()) {
        cout << "Max antal mätvärden nått, avslutar programmet.\n";
    }

    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
