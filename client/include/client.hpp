#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <httplib.h>
#include <memory>
#include "client-config.hpp"

class Client
{
public:
  explicit Client(const ClientConfig & config);

  Client(const Client &) = delete;
  Client(Client &&) = delete;
  ~Client() = default;

  Client & operator=(const Client &) = delete;
  Client & operator=(Client &&) = delete;

  const ClientConfig & getConfig() const noexcept;
  void updateConfig(const std::string & config_path);
  void ping();
  std::string getTimeMetric(const std::string & server_name, const std::string & timestamp);
  std::string getIntervalMetrics(
      const std::string & server_name, const std::string & begin_timestamp, const std::string & end_timestamp);

protected:
  ClientConfig config_;
  httplib::Client client_;

  std::string get(const std::string & query);
};

#endif
