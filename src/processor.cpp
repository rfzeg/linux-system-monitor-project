#include "processor.h"

// returns the aggregate CPU utilization
// CPU percentage = (total - real_idle)/total
// total = real_idle + nonidle
// real_idle = idle_ + iowait
// nonidle = user + nice + system + irq + softirq + steal
float Processor::Utilization() {
    int user_ = std::stoi(values_[1]);
    int nice_ = std::stoi(values_[2]);
    int sys_ = std::stoi(values_[3]);
    int idle_ = std::stoi(values_[4]);
    int iowait_ = std::stoi(values_[5]);
    int irq_ = std::stoi(values_[6]);
    int softirq_ = std::stoi(values_[7]);
    int steal_ = std::stoi(values_[8]);
    
    int nonidle = user_ + nice_ + sys_ + irq_ + softirq_ + steal_;
    int real_idle = idle_ + iowait_;

    return ((float)nonidle/(real_idle + nonidle));
}

// constructor defined outside the class definition in the header file
Processor::Processor(std::vector<std::string> cpu_values): values_(cpu_values){};