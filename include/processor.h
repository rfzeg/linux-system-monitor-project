#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <vector>

class Processor {
 public:
  // returns the aggregate CPU utilization
  float Utilization();
  // constructor declaration
  Processor(std::vector<std::string>);

 private:
    std::vector<std::string> values_;
};

#endif