#pragma once
#ifndef IMAGEEDITOR_MODILES_NETWORK_NETWORK_H
#define IMAGEEDITOR_MODILES_NETWORK_NETWORK_H

#include "INetwork.h"

class QNetworkAccessManager;
namespace ImageEditor::Modules {
class NetworkImpl final : public INetwork {
public:
  explicit NetworkImpl() = default;
  NetworkImpl(const NetworkImpl &) = delete;
  NetworkImpl &operator=(const NetworkImpl &) = delete;

public: // INetwork
  virtual std::string ImageServerUrl();

protected:
  friend class Network::HttpPostBinary;
  QNetworkAccessManager *NetworkAccessManager();

private:
  using QNetworkAccessManagerPtr = std::shared_ptr<QNetworkAccessManager>;
  QNetworkAccessManagerPtr network_access_manager_;
};
} // namespace ImageEditor::Modules

#endif // IMAGEEDITOR_MODILES_NETWORK_NETWORK_H
