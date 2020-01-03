#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// constructor defined outside the class definition in the header file
Process::Process(int pid, std::string cmdl, std::string vmsize, std::string user, long int uptime, float load):
pid_(pid), cmd_line_(cmdl), vmsize_(vmsize), user_(user), uptime_(uptime), cpu_load_(load){};

// Return this process's ID
int Process::Pid() { return pid_; }

// Return the command that generated this process
string Process::Command() { return cmd_line_; }

// Return this process's memory utilization
string Process::Ram() { return vmsize_; }

// Return the user that generated this process
string Process::User() { return user_; }

// Return the age of this process (in seconds)
long int Process::UpTime() { return uptime_; }

// Return this process's CPU utilization
float Process::CpuUtilization() { return cpu_load_; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }