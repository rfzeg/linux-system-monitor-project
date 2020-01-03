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

// constructor defined outside the class definition in the header file
System::System(std::vector<std::string> cpu_values, std::vector<int> pids): cpu_(cpu_values){
  for (int elem : pids) {
    std::string cmdline = LinuxParser::Command(elem);
    std::string vmsize = LinuxParser::Ram(elem);
    std::string user = LinuxParser::User(elem);
    long int uptime = LinuxParser::UpTime(elem);
    float cpu_load = LinuxParser::CpuUtilization(elem);
    Process process_(elem, cmdline, vmsize, user, uptime, cpu_load);
    // Push back 'Process' objects separately into a vector
    processes_.push_back(process_);
  }
};

// Return an 'Processor' object containing the system's CPU utilization
Processor& System::Cpu() {
  // Get 'Processor' object
  return cpu_;
  }

// Return a container composed of the system's processes
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