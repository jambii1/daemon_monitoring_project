#include <cstring>
#include <iostream>
#include "client.hpp"
#include "cmd-ui.hpp"

int main(int argc, char ** argv)
{
  if (argc < 2)
  {
    std::cerr << "Error: incorrect args count, need config path\n";
    return 1;
  }

  ClientConfig config;
  try
  {
    config.load(argv[1]);
  }
  catch (const std::exception & e)
  {
    std::cerr << "Failed to load config file: " << e.what() << '\n';
    return 2;
  }

  try
  {
    if (argc == 3 && std::strcmp(argv[2], "--cmd") == 0 || argc == 2)
    {
      CmdUI cmdui(std::make_unique< Client >(config));
      cmdui.run();
    }
  }
  catch (const std::exception & e)
  {
    std::cerr << "Error: " << e.what() << '\n';
    return 2;
  }
}
