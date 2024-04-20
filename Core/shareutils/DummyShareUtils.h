#ifndef DUMMY_SHAREUTILS_H
#define DUMMY_SHAREUTILS_H

#include "IPlatformShareUtils.h"
#include <QDebug>
#include <QObject>

namespace ShareUtils::Dummy {

/*!
 * \brief The DummyShareUtils class dervies from the IPlatformShareUtils class
 * and exists only to make it so that you don't need to wrap `ShareUtils` in
 * preprocessor macros when compiling for desktop. When working with viewing and
 * sending files on desktop, you should instead use QFileDialog.
 */
class DummyShareUtils : public IPlatformShareUtils {
  Q_OBJECT
public:
  DummyShareUtils(QObject *parent) : IPlatformShareUtils(parent) {}

  /// @copydoc PlatformShareUtils::checkMimeTypeView(const QString&)
  virtual bool checkMimeTypeView(const QString &mimeType) override {
    qDebug() << __func__ << "mimType:" << mimeType;
    return false;
  }

  /// @copydoc PlatformShareUtils::sendFile(const QString&, const QString&,
  /// const QString&, int)
  virtual void sendFile(const QString &filePath, const QString &title,
                        const QString &mimeType, int requestId) override {
    qDebug() << __func__ << "filePath:" << filePath << " title: " << title
             << " mimType: " << mimeType << " requestID: " << requestId;
  }
};

} // namespace ShareUtils::Dummy

#endif // DUMMY_SHAREUTILS_H
