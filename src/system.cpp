#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// constructor declared outside the class
System::System(std::vector<std::string> cpu_values): cpu_(cpu_values){};
// Return an 'Processor' object containing the system's CPU utilization
Processor& System::Cpu() {
  // Get 'Processor' object
  return cpu_;
  }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { return processes_; }

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() {
  return string(LinuxParser::Kernel());
}

// Return the system's memory utilization
float System::MemoryUtilization() {
  return LinuxParser::MemoryUtilization(); }

// Return the operating system name
std::string System::OperatingSystem() { 
    return string(LinuxParser::OperatingSystem());
}

// Return the number of processes actively running on the system
int System::RunningProcesses() {
  return LinuxParser::RunningProcesses();
}

// Return the total number of processes on the system
int System::TotalProcesses() {
  return LinuxParser::TotalProcesses();
}

// Return the number of seconds since the system started running
long int System::UpTime() {
  return LinuxParser::UpTime();
}