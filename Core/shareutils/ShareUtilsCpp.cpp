
#include <stdafx.h>
#ifdef Q_OS_ANDROID
#include "AndroidShareUtils.h"
#else
#include "DummyShareUtils.h"
#endif

#include "ShareUtilsCpp.h"

namespace ShareUtils {

ShareUtilsCpp::ShareUtilsCpp(QObject *parent) : QObject(parent) {
#ifdef Q_OS_ANDROID
  mPlatformShareUtils = new Android::AndroidShareUtils(this);
#else
  // NOTE: The dummy is here so that the object compiles well for desktop \
    // builds, however, since this project is meant for iOS and Android native \
    // share design patterns, it doesn't really make sense to implement share \
    // methods for desktop as well. If you're interested in accessing files on \
    // desktop, Qt provides `QFileDialog` for this explicit purpose, and this \
    // class better matches the desktop design pattern.
  mPlatformShareUtils = new Dummy::DummyShareUtils(this);
#endif

  connect(mPlatformShareUtils, SIGNAL(shareFinished(int)), this,
          SLOT(onShareFinished(int)));

  connect(mPlatformShareUtils, SIGNAL(shareNoAppAvailable(int)), this,
          SLOT(onShareNoAppAvailable(int)));

  connect(mPlatformShareUtils, SIGNAL(shareError(int, QString)), this,
          SLOT(onShareError(int, QString)));

  connect(mPlatformShareUtils, SIGNAL(fileUrlReceived(QString)), this,
          SLOT(onFileUrlReceived(QString)));
}

bool ShareUtilsCpp::checkMimeTypeView(const QString &mimeType) {
  return mPlatformShareUtils->checkMimeTypeView(mimeType);
}

void ShareUtilsCpp::sendFile(const QString &filePath, const QString &title,
                             const QString &mimeType, const int &requestId) {
  mPlatformShareUtils->sendFile(filePath, title, mimeType, requestId);
}

void ShareUtilsCpp::checkPendingIntents() {
  mPlatformShareUtils->checkPendingIntents();
}

void ShareUtilsCpp::clearTempDir() { mPlatformShareUtils->clearTempDir(); }

void ShareUtilsCpp::onShareFinished(int requestCode) {
  emit shareFinished(requestCode);
}

void ShareUtilsCpp::onShareNoAppAvailable(int requestCode) {
  emit shareNoAppAvailable(requestCode);
}

void ShareUtilsCpp::onShareError(int requestCode, QString message) {
  emit shareError(requestCode, message);
}

void ShareUtilsCpp::onFileUrlReceived(QString url) {
  emit fileUrlReceived(url);
}
} // namespace ShareUtils
