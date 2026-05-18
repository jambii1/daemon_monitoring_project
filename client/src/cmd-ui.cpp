#include "cmd-ui.hpp"
#include <iostream>

CmdUI::CmdUI(std::unique_ptr< Client > client):
  client_(std::move(client))
{
  registerCommands();
}

void CmdUI::run()
{
  std::cout << "> ";
  std::string command;
  while (std::cin >> command)
  {
    try
    {
      auto it = commands_.find(command);
      if (it != commands_.end())
      {
        it->second();
      }
      else
      {
        std::cout << "Error: invalid command\n";
      }
    }
    catch (const std::exception & e)
    {
      std::cout << "Error: " << e.what() << '\n';
    }

    if (std::cin.fail())
    {
      std::cin.clear();
    }
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');

    std::cout << "> ";
  }
}

void CmdUI::registerCommands()
{
  commands_["help"] = std::bind(printHelp, this);
  commands_["load-config"] = std::bind(loadClientConfig, this);

  commands_["ping"] = std::bind(ping, this);
  commands_["print-time"] = std::bind(printTimeMetric, this);
  commands_["print-interval"] = std::bind(printIntervalMetrics, this);
}

void CmdUI::printHelp()
{
  std::cout << "== commands ==\n";
  for (auto item : commands_)
  {
    std::cout << item.first << '\n';
  }
}

void CmdUI::loadClientConfig()
{
  std::string config_path;
  std::cin >> config_path;

  client_->updateConfig(config_path);

  std::cout << "new path: " << client_->getConfig().getClientConfigFilePath() << '\n';
}

void CmdUI::ping()
{
  client_->ping();
}

void CmdUI::printTimeMetric()
{
  std::string server_name, timestamp;
  std::cin >> server_name >> timestamp;

  std::string res;
  try
  {
    res = client_->getTimeMetric(server_name, timestamp);
  }
  catch (const std::runtime_error & e)
  {
    std::cerr << "Error: " << e.what() << '\n';
    return;
  }

  std::cout << res << '\n';
}

void CmdUI::printIntervalMetrics()
{
  std::string server_name, begin_timestamp, end_timestamp;
  std::cin >> server_name >> begin_timestamp >> end_timestamp;

  std::string res;
  try
  {
    res = client_->getIntervalMetrics(server_name, begin_timestamp, end_timestamp);
  }
  catch (const std::runtime_error & e)
  {
    std::cerr << "Error: " << e.what() << '\n';
    return;
  }

  std::cout << res << '\n';
}
