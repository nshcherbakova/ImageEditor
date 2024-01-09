#pragma once
#ifndef IMAGEEDITOR_MODILES_NETWORK_INETWORK_H
#define IMAGEEDITOR_MODILES_NETWORK_INETWORK_H
#include <Modules/types.h>

namespace ImageEditor::Modules {
struct INetwork {
  virtual ~INetwork() = default;
  virtual std::string ImageServerUrl() = 0;
};
} // namespace ImageEditor::Modules
namespace ImageEditor::Modules::Network {
class HttpPostBinary {
public:
  HttpPostBinary(INetwork *network, const std::string &url,
                 QVariant content_type, QString file_name, QByteArray byte_arr,
                 std::function<void(int)> finished_predicate);
};
} // namespace ImageEditor::Modules::Network

#endif // IMAGEEDITOR_MODILES_NETWORK_INETWORK_H
