#include "data_manager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

string getTimestamp() {
    time_t now = time(0);
    struct tm tid;
    localtime_s(&tid, &now);

    std::stringstream ss;
    ss << std::put_time(&tid, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

void DataManager::inputMeasurements() {
    float input;
    cout << "Mata in mätvärden (avsluta med 'f'):\n";
    while (data.size() < MAX) {
        cout << "Mätvärde " << (data.size() + 1) << ": ";
        cin >> input;
        if (cin.fail()) {
            cin.clear();
            char c;
            cin >> c;
            if (c == 'f' || c == 'F') break;
            cout << "Felaktig inmatning, försök igen.\n";
            continue;
        }
        data.push_back({ input, getTimestamp() });
    }
}

void DataManager::simulateSensor() {
    if (isFull()) {
        cout << "Max antal mätvärden har redan nåtts.\n";
        return;
    }

    int antalSimuleringar;
    cout << "Hur många mätvärden vill du simulera?\n";
    cin >> antalSimuleringar;

    if (antalSimuleringar <= 0 || antalSimuleringar > (MAX - data.size())) {
        cout << "Ogiltigt antal. Max tillgängliga platser: " << (MAX - data.size()) << "\n";
        return;
    }

    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < antalSimuleringar; i++) {
        float slumpvärde = 20.0 + static_cast<float>(rand()) / RAND_MAX * 10.0;
        data.push_back({ slumpvärde, getTimestamp() });
        cout << "Simulerat värde " << (data.size()) << ": " << slumpvärde << " °C\n";
    }

    cout << "Sensorvärden har genererats och lagrats.\n";
}

void DataManager::sortMeasurements() {
    if (data.empty()) {
        cout << "Ingen data att sortera.\n";
        return;
    }

    sort(data.begin(), data.end(), [](const Measurement& a, const Measurement& b) {
        return a.value < b.value;
        });

    cout << "Mätvärden sorterade:\n";
    printMeasurements();
}

void DataManager::searchValue() {
    if (data.empty()) {
        cout << "Listan är tom.\n";
        return;
    }

    float sökt;
    cout << "Ange värde att söka efter: ";
    cin >> sökt;
    bool hittad = false;

    for (size_t i = 0; i < data.size(); i++) {
        if (data[i].value == sökt) {
            cout << "Värdet " << sökt << " hittades på position " << (i + 1) << ".\n";
            hittad = true;
        }
    }

    if (!hittad) {
        cout << "Värdet hittades inte.\n";
    }
}

void DataManager::showStatistics() {
    if (data.empty()) {
        cout << "Inga mätvärden att analysera.\n";
        return;
    }

    float sum = 0.0, min = data[0].value, max = data[0].value;
    for (const auto& m : data) {
        sum += m.value;
        if (m.value < min) min = m.value;
        if (m.value > max) max = m.value;
    }

    float medel = sum / data.size();
    float varians = 0.0;
    for (const auto& m : data) {
        varians += pow(m.value - medel, 2);
    }
    varians /= data.size();
    float stddev = sqrt(varians);

    cout << "\n--- Statistik ---\n";
    cout << "Antal värden: " << data.size() << "\n";
    cout << "Summa: " << sum << "\n";
    cout << "Medelvärde: " << medel << "\n";
    cout << "Min-värde: " << min << "\n";
    cout << "Max-värde: " << max << "\n";
    cout << "Standardavvikelse: " << stddev << "\n";
}

void DataManager::loadFromFile(const string& filename) {
    ifstream fil(filename);
    string line;
    while (getline(fil, line)) {
        stringstream ss(line);
        string timestamp, valueStr;
        if (getline(ss, timestamp, ',') && getline(ss, valueStr)) {
            float value = stof(valueStr);
            data.push_back({ value, timestamp });
        }
    }
    fil.close();
}

void DataManager::saveToFile(const string& filename) const {
    ofstream fil(filename);
    for (const auto& m : data) {
        fil << m.timestamp << "," << m.value << endl;
    }
    fil.close();
}

void DataManager::printMeasurements() const {
    for (const auto& m : data) {
        cout << m.timestamp << " → " << m.value << " °C\n";
    }
}

bool DataManager::isFull() const {
    return data.size() >= MAX;
}
