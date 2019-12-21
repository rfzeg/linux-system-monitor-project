#include <string>

#include "format.h"

const int secs_in_day = 86400;
const int secs_in_hour = 3600;
const int secs_in_minute = 60;

// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
std::string Format::ElapsedTime(long input_seconds) {
    long hours = (input_seconds % secs_in_day) / secs_in_hour;
    long minutes = ((input_seconds % secs_in_day) % secs_in_hour) / secs_in_minute;
    long seconds = (((input_seconds % secs_in_day) % secs_in_hour) % secs_in_minute);
    // pad numbers with leading zeros
    std::string hrs = std::to_string(hours);
    hrs = std::string(2 - hrs.length(), '0') + hrs;
    std::string min = std::to_string(minutes);
    min = std::string(2 - min.length(), '0') + min;
    std::string sec = std::to_string(seconds);
    sec = std::string(2 - sec.length(), '0') + sec;

    return std::to_string(hours)+":"+min+":"+sec;
}