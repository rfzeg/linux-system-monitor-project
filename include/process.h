#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();
  std::string User();
  std::string Command();
  float CpuUtilization();
  std::string Ram();
  long int UpTime();
  bool operator<(Process const& a) const;  //
  // constructor declaration
  Process(int, std::string, std::string, std::string, long int, float);

 // Necessary private members
 private:
  int pid_;
  std::string cmd_line_;
  std::string vmsize_;
  std::string user_;
  long int uptime_;
  float cpu_load_;
};

#endif