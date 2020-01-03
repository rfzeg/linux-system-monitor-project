#include "ncurses_display.h"
#include "system.h"
#include "linux_parser.h"

int main() {
  System system(LinuxParser::CpuUtilization(), LinuxParser::Pids());
  NCursesDisplay::Display(system);
}