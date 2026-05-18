#include "client.hpp"

Client::Client(const ClientConfig & config):
  config_(config),
  client_(config_.getGetStrategy().scheme + "://" + config_.getGetStrategy().host + ':' + config_.getGetStrategy().port)
{}

const ClientConfig & Client::getConfig() const noexcept
{
  return config_;
}

void Client::updateConfig(const std::string & config_path)
{
  ClientConfig newConfig;
  newConfig.load(config_path);
  config_ = newConfig;
}

void Client::ping()
{
  get("/");
}

std::string Client::getTimeMetric(const std::string & server_name, const std::string & timestamp)
{
  if (config_.getServers().find(server_name) == config_.getServers().end())
  {
    throw std::invalid_argument("invalid server name");
  }

  return get(config_.getGetStrategy().endpoint + "?name=" + server_name + "&time=" + timestamp);
}

std::string Client::getIntervalMetrics(
    const std::string & server_name, const std::string & begin_timestamp, const std::string & end_timestamp)
{
  if (config_.getServers().find(server_name) == config_.getServers().end())
  {
    throw std::invalid_argument("invalid server name");
  }

  return get(config_.getGetStrategy().endpoint + "?name=" + server_name + "&begin=" + begin_timestamp
      + "&end=" + end_timestamp);
}

std::string Client::get(const std::string & query)
{
  auto res = client_.Get(query);
  if (!res)
  {
    throw std::runtime_error(httplib::to_string(res.error()));
  }
  if (res->status != 200)
  {
    throw std::runtime_error("HTTP error: " + std::to_string(res->status));
  }

  return res->body;
}
