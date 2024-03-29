#include "Network.h"
#include <stdafx.h>

namespace ImageEditor::Modules {

std::string NetworkImpl::ImageServerUrl() {
  auto url = QSettings(QSettings::Scope::UserScope)
                 .value("ImageServer")
                 .toString()
                 .toStdString();
  UNI_ASSERT(!url.empty());
  return url;
}

QNetworkAccessManager *NetworkImpl::NetworkAccessManager() {
  if (!network_access_manager_) {
    network_access_manager_ = std::make_shared<QNetworkAccessManager>();
  }
  return network_access_manager_.get();
}
} // namespace ImageEditor::Modules

namespace ImageEditor::Modules::Network {

HttpPostBinary::HttpPostBinary(INetwork *network, const std::string &url,
                               const std::string &content_type,
                               const std::string &file_name,
                               const std::vector<char> &data,
                               std::function<void(int)> finished_predicate) {
  UNI_ASSERT(!url.empty());
  spdlog::info("Post request to  {0}", url);
  QUrl qurl = QUrl(QString::fromStdString(url));

  QHttpPart receipt_part;
  receipt_part.setHeader(QNetworkRequest::ContentTypeHeader,
                         QString::fromStdString(content_type));
  receipt_part.setHeader(
      QNetworkRequest::ContentDispositionHeader,
      QVariant(QString("multipart/form-data; name=\"image\"; filename=\"%1\"")
                   .arg(QString::fromStdString(file_name))));

  receipt_part.setRawHeader("Content-Transfer-Encoding", "binary");
  receipt_part.setBody(QByteArray(&data[0], data.size()));

  QHttpMultiPart *multi_part = new QHttpMultiPart(QHttpMultiPart::FormDataType);
  multi_part->append(receipt_part);

  auto network_accesss_manager =
      dynamic_cast<NetworkImpl *>(network)->NetworkAccessManager();
  UNI_ENSURE_RETURN(network_accesss_manager);

  auto reply = network_accesss_manager->post(QNetworkRequest(qurl), multi_part);

  QObject::connect(reply, &QNetworkReply::errorOccurred,
                   [finished_predicate](QNetworkReply::NetworkError error) {
                     finished_predicate(error);
                   });
  QObject::connect(reply, &QNetworkReply::finished, [finished_predicate]() {
    finished_predicate(QNetworkReply::NoError);
  });
}
} // namespace ImageEditor::Modules::Network
