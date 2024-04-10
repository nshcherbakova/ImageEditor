#include "MainWindow.h"
#include <QOpenGLFunctions_4_0_Core>
#include <stdafx.h>

using namespace ImageEditor;
using namespace UI;

static const char *c_org_str = "natshch";
static const char *c_app_str = "ImageEditor";
static const char *c_font_str = ":/Fonts/buttons_font";
static const char *c_splash_screen_image_str = ":/Images/splash_screen";
static const char *c_log_str = "/logs/ImageEditorLog.txt";
static const char *c_logger_str = "logger";

static const char *c_settings_image_server_str = "ImageServer";
static const char *c_image_server_def_host_port_str =
    "http://192.168.86.187:8081/";

#ifdef Q_OS_ANDROID
bool requestStoragePermission() {
  const QVector<QString> permissions(
      {"android.permission.WRITE_EXTERNAL_STORAGE",
       "android.permission.READ_EXTERNAL_STORAGE",
       "android.permission.READ_MEDIA_IMAGES"});

  for (const QString &permission : permissions) {
    auto result = QtAndroidPrivate::checkPermission(permission);
    if (result.result() == QtAndroidPrivate::PermissionResult::Denied) {
      QFuture<QtAndroidPrivate::PermissionResult> resultHash =
          QtAndroidPrivate::requestPermission(permission);
      if (resultHash.result() == QtAndroidPrivate::PermissionResult::Denied)
        return false;
    }
  }

  return true;
}

void accessAllFiles() {
  if (QOperatingSystemVersion::current() <
      QOperatingSystemVersion(QOperatingSystemVersion::Android, 11)) {
    qDebug()
        << "it is less then Android 11 - ALL FILES permission isn't possible!";
    return;
  }
  // Here you have to set your PackageName

  jboolean value = QJniObject::callStaticMethod<jboolean>(
      "android/os/Environment", "isExternalStorageManager");
  if (value == false) {
    qDebug() << "requesting ACTION_MANAGE_APP_ALL_FILES_ACCESS_PERMISSION";

    QJniObject activity = QNativeInterface::QAndroidApplication::context();
    QJniObject packageManager = activity.callObjectMethod(
        "getPackageManager", "()Landroid/content/pm/PackageManager;");
    QJniObject packageName =
        activity.callObjectMethod("getPackageName", "()Ljava/lang/String;");

    QJniObject ACTION_MANAGE_APP_ALL_FILES_ACCESS_PERMISSION =
        QJniObject::getStaticObjectField(
            "android/provider/Settings",
            "ACTION_MANAGE_APP_ALL_FILES_ACCESS_PERMISSION",
            "Ljava/lang/String;");
    QJniObject intent("android/content/Intent", "(Ljava/lang/String;)V",
                      ACTION_MANAGE_APP_ALL_FILES_ACCESS_PERMISSION.object());
    QJniObject jniPath =
        QJniObject::fromString("package:" + packageName.toString());
    QJniObject jniUri = QJniObject::callStaticObjectMethod(
        "android/net/Uri", "parse", "(Ljava/lang/String;)Landroid/net/Uri;",
        jniPath.object<jstring>());
    QJniObject jniResult = intent.callObjectMethod(
        "setData", "(Landroid/net/Uri;)Landroid/content/Intent;",
        jniUri.object<jobject>());
    QtAndroidPrivate::startActivity(intent, 0);
  } else {
    qDebug() << "SUCCESS ACTION_MANAGE_APP_ALL_FILES_ACCESS_PERMISSION";
  }
}
#endif

int main(int argc, char *argv[]) {
  try {
    QString logs_path = QDir::currentPath() + c_log_str;
    auto logger = spdlog::basic_logger_mt(
        c_logger_str, QDir().toNativeSeparators(logs_path).toStdString());
    spdlog::set_default_logger(logger);
  } catch (const spdlog::spdlog_ex &ex) {
#ifndef Q_OS_IOS
    // TODO fix iOS exception
    UNI_ASSERT(false);
#endif
  }
  spdlog::info("Initialyse ImageEditor");

  QSurfaceFormat fmt;
  fmt.setSamples(16);
#ifndef Q_OS_ANDROID
  // fmt.setRenderableType(QSurfaceFormat::OpenGL);
  fmt.setMajorVersion(3);
  fmt.setMinorVersion(3);
#endif
  fmt.setProfile(QSurfaceFormat::OpenGLContextProfile::CoreProfile);

  QSurfaceFormat::setDefaultFormat(fmt);

  QApplication a(argc, argv);

  SplashScreen splash({c_splash_screen_image_str});
  splash.showFullScreen();

  QCoreApplication::setOrganizationName(c_org_str);
  QCoreApplication::setApplicationName(c_app_str);
  QSettings(QSettings::Scope::UserScope)
      .setValue(c_settings_image_server_str, c_image_server_def_host_port_str);

  QFontDatabase::addApplicationFont(c_font_str);

#ifdef Q_OS_ANDROID
  // #ifdef REQUEST_PERMISSIONS_ON_ANDROID
  // requestStoragePermission();
  // #endif
  // accessAllFiles();

  QJniObject activity = QNativeInterface::QAndroidApplication::context();
  if (activity.isValid()) {
    int orientation = QJniObject::getStaticField<int>(
        "android.content.pm.ActivityInfo", "SCREEN_ORIENTATION_PORTRAIT");
    activity.callMethod<void>("setRequestedOrientation" // method name
                              ,
                              "(I)V" // signature
                              ,
                              orientation);
  }
#endif
  MainWindow main_window;
  // main_window.setFormat();

  auto image =
      Modules::InitEditableImageModule().create<Modules::IEditableImagePtr>();
  auto filters = Core::InitFiltersModule().create<Core::IFilterPtrArr>();
  auto filters_frame = Modules::InitFramesModule(image, std::move(filters))
                           .create<Modules::IFramePtr>();
  auto network = Modules::InitNetworkModule().create<Modules::INetworkPtr>();
  auto filters_widget =
      UI::InitWidgetsModule(main_window, std::move(filters_frame),
                            std::move(image), std::move(network))
          .create<IWidget *>();

  spdlog::info("Run ImageEditor");
  main_window.show();
  filters_widget->onShow(true);

  splash.finish(&main_window);

  auto exec_result = a.exec();

  spdlog::info("ImageEditor was closed");
  return exec_result;
}
