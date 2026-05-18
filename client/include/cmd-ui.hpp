#ifndef CMD_UI_HPP
#define CMD_UI_HPP

#include <string>
#include "client.hpp"

class CmdUI final
{
public:
  explicit CmdUI(std::unique_ptr< Client > client);
  void run();

private:
  std::unordered_map< std::string, std::function< void() > > commands_;
  std::unique_ptr< Client > client_;

  void registerCommands();
  void printHelp();
  void loadClientConfig();
  void ping();
  void printTimeMetric();
  void printIntervalMetrics();
};

#endif
