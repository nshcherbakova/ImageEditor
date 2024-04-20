#ifndef IPLATFORMSHAREUTILS_H
#define IPLATFORMSHAREUTILS_H

#include <QObject>

namespace ShareUtils {
/*!
 * \brief The IPlatformShareUtils class is an abstract class that implements the
 * functionality for sending and viewing files through the native mobile
 * interfaces. Each mobile interface has its own derived class that handles
 * communicating with native mobile code.
 */
class IPlatformShareUtils : public QObject {
  Q_OBJECT
public:
  IPlatformShareUtils(QObject *parent) : QObject(parent) {}

  /*!
   * \brief checkMimeTypeView check whether the mimeType provided is compatible
   * with the application that will be sending/viewing the file. \param mimeType
   * mimeType to check \return true if the mimeType is supported, false
   * otherwise
   */
  virtual bool checkMimeTypeView(const QString &mimeType) = 0;

  /*!
   * \brief sendFile send a file through the native mobile share interface
   * \param filePath the absolute path to the file
   * \param title the title of the share
   * \param mimeType the mimeType of the file
   * \param requestId the ID to give the task of sending a file. Set this to a
   * value other than 0 if you want to track the completion of the task.
   */
  virtual void sendFile(const QString &filePath, const QString &title,
                        const QString &mimeType, int requestId) = 0;
  /*!
   * \brief checkPendingIntents used by android only, this checks for pending
   * intents when an application becomes active again.
   */
  virtual void checkPendingIntents() {}

  /*!
   * \brief clearTempDir android only, this provides an option to clear the temp
   * save directory.
   */
  virtual void clearTempDir() {}

signals:
  /// emits when a share finishes successfully.
  void shareFinished(int requestID);

  /// emits when a share fails because an app could not be found
  void shareNoAppAvailable(int requestID);

  /// emits when there is an error with sharing, will give message and requestID
  /// if provided
  void shareError(int requestID, QString message);

  /// emits when a URL is received
  void fileUrlReceived(QString url);
};
} // namespace ShareUtils
#endif // IPLATFORMSHAREUTILS_H
