#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "measurement.h"
#include <vector>
#include <string>

class DataManager {
private:
    std::vector<Measurement> data;
    const int MAX = 25;

public:
    void inputMeasurements();
    void simulateSensor();
    void sortMeasurements();
    void searchValue();
    void showStatistics();
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;
    void printMeasurements() const;
    bool isFull() const;
};

#endif

