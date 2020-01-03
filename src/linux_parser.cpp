#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"
#include <unistd.h> // to convert from "clock ticks" to seconds
#include <iomanip>  // std::setprecision

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// Read and return the system memory utilization
// Mem. total: MemTotal
// Mem. used:	MemTotal - MemFree - Buffers - Cached - Slab
float LinuxParser::MemoryUtilization() {
  string line;
  string key;
  string value;
  int memtotal, memfree, buffers, cached, slab;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal:") { memtotal = std::stoi(value); }
        else if (key == "MemFree:") { memfree = std::stoi(value); }
        else if (key == "Buffers:") { buffers = std::stoi(value); }
        else if (key == "Cached:") { cached = std::stoi(value); }
        else if (key == "Slab:") { slab = std::stoi(value); }
      }
    }
    return (memtotal - memfree - buffers - cached - slab)/float(memtotal);
  }
  return -1.0;
}

// Read and return the system uptime (values in seconds)
long LinuxParser::UpTime() {
  string total, idle;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> total >> idle;
  }
  return std::stol(total, nullptr, 10); }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// Read and return CPU utilization (aggregated)
vector<string> LinuxParser::CpuUtilization() {
  string line;
  std::vector<std::string> values;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    string val;
    // Push back the elements on the string separately into a vector
    while (linestream >> val) values.push_back(val);
  }
  return {values};
}

// Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          int int_value;
          try
            {
            int_value = std::stoi(value);
            }
            catch (std::invalid_argument const &e)
            {
              throw std::invalid_argument( "std::stoi received invalid argument \n");
            }
            catch (std::out_of_range const &e)
            {
              throw std::invalid_argument( "Integer overflow: std::out_of_range thrown by std::stoi \n");
            }
          return int_value;
        }
      }
    }
  }
  return -1;
}

// Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          int int_value;
          try
            {
            int_value = std::stoi(value);
            }
            catch (std::invalid_argument const &e)
            {
              throw std::invalid_argument( "std::stoi received invalid argument \n");
            }
            catch (std::out_of_range const &e)
            {
              throw std::invalid_argument( "Integer overflow: std::out_of_range thrown by std::stoi \n");
            }
          return int_value;
        }
      }
    }
  }
  return -1;
}

// Read and return the command associated with a process
// Linux stores the command used to launch the function in the /proc/[pid]/cmdline file
string LinuxParser::Command(int pid) {
  string line;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    // Take a stream object from which to extract a line.
    // 'line' is a std::string to which to extract the line into
    std::getline(stream, line);
    return line;
  }
  return string();
}

// Read and return the memory used by a process
// Linux stores memory utilization for the process in /proc/[pid]/status.
string LinuxParser::Ram(int pid) {
  string line, key, value;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "VmSize:") {
          std::stringstream mem_string;
          float mem_float = std::stof(value)/1000;
          mem_string << std::setfill(' ') << std::setw(6) << std::fixed << std::setprecision(1) << mem_float;
          return mem_string.str();
          }
      }
    }
  }
  return string();
}

// Read and return the user associated with a process
// The UID for a process is stored in /proc/[PID]/status
// To-Do: match the UID to a username
string LinuxParser::User(int pid) {
  string line, key, value;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "Uid:") { return value; }
      }
    }
  }
  return string();
}

// Read and return the uptime of a process
// Linux stores the process up time in /proc/[pid]/stat
long LinuxParser::UpTime(int pid) {
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
  string line, value;
  if (filestream.is_open()) {
    int counter = 0;
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      // read tokens one by one
      while (linestream >> value) {
        counter++;
        if (counter == 22) {
          // convert from "clock ticks" to seconds
          return std::stol(value)/sysconf(_SC_CLK_TCK);
        }
      }
    }
  }
  return 0;
}

// Read and return CPU utilization (per pid) in percentage
float LinuxParser::CpuUtilization(int pid) {
  string line, value;
  long int total_time, seconds, utime, stime, cutime, cstime, starttime;
  float cpu_usage;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    int counter = 0;
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      // read tokens one by one
      while (linestream >> value) {
        ++counter;
        switch(counter) {
          // Amount of time scheduled in user mode (in clock ticks)
          case 14: utime = std::stol(value); break;
          // Amount of time scheduled in kernel mode (in clock ticks)
          case 15: stime = std::stol(value); break;
          // Amount of time waiting-for children in user mode (in clock ticks)
          case 16: cutime = std::stol(value); break;
          // Amount of time waiting-for children in kernel mode (in clock ticks)
          case 17: cstime = std::stol(value); break;
          // The time the process started after system boot (in clock ticks)
          case 22: starttime = std::stol(value); break;
        }
      }
    }
    total_time = utime + stime + cutime + cstime;
    // Total elapsed time in seconds since the process started
    seconds = LinuxParser::UpTime() - (starttime / sysconf(_SC_CLK_TCK));
    cpu_usage = ((total_time / sysconf(_SC_CLK_TCK)) / (float)seconds);
    return cpu_usage;
  }
  return 0.0;
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }
