#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <string>

struct Measurement {
	float value;  // e.g., temperature in Celsius
	std::string timestamp;  // e.g., "2024-06-01 14:30:00"
};

#endif
