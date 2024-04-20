#ifndef ANDROID_SHAREUTILS_H
#define ANDROID_SHAREUTILS_H

#include "IPlatformShareUtils.h"
#include <QDebug>
#include <QObject>
#include <QtCore/private/qandroidextras_p.h>

namespace ShareUtils::Android {
/*!
 * \brief The AndroidShareUtils class dervies from the IPlatformShareUtils class
 * and implements communication between the android native share and the Qt
 * application.
 */
class AndroidShareUtils : public IPlatformShareUtils,
                          public QAndroidActivityResultReceiver {
  Q_OBJECT
public:
  AndroidShareUtils(QObject *parent = nullptr);

  /// @copydoc IPlatformShareUtils::checkMimeTypeView(const QString&)
  bool checkMimeTypeView(const QString &mimeType) override;

  /// @copydoc IPlatformShareUtils::sendFile(const QString&, const QString&,
  /// const QString&, int)
  void sendFile(const QString &filePath, const QString &title,
                const QString &mimeType, int requestId) override;

  /// @copydoc IPlatformShareUtils::viewFile(const QString&, const QString&,
  /// const QString&, int)
  /*  void viewFile(const QString& filePath,
                const QString& title,
                const QString& mimeType,
                int requestId) override;*/

  /// @copydoc IPlatformShareUtils::checkPendingIntents()
  void checkPendingIntents() override;

  /// @copydoc IPlatformShareUtils::clearTempDir()
  void clearTempDir() override;

  void handleActivityResult(int receiverRequestCode, int resultCode,
                            const QJniObject &data) override;

  void onActivityResult(int requestCode, int resultCode);

  /// gets single instance of the AndroidShareUtils
  static AndroidShareUtils *getInstance();

public slots:
  void setFileUrlReceived(const QString &url);

  bool checkFileExits(const QString &url);

private:
  static AndroidShareUtils *mInstance;

  QString mSavePath;

  void processActivityResult(int requestCode, int resultCode);
};
} // namespace ShareUtils::Android

#endif // ANDROID_SHAREUTILS_H
