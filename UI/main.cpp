#include "MainWindow.h"
#include <stdafx.h>
#ifdef Q_OS_ANDROID
#include <QJniObject>
#endif

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
#ifdef REQUEST_PERMISSIONS_ON_ANDROID
#include <QtAndroid>

bool requestStoragePermission() {
  using namespace QtAndroid;

  QString permission =
      QStringLiteral("android.permission.WRITE_EXTERNAL_STORAGE");
  const QHash<QString, PermissionResult> results =
      requestPermissionsSync(QStringList({permission}));
  if (!results.contains(permission) ||
      results[permission] == PermissionResult::Denied) {
    qWarning() << "Couldn't get permission: " << permission;
    spdlog::error("Couldn't get a permission.");
    return false;
  }

  return true;
}
#endif
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
#ifdef REQUEST_PERMISSIONS_ON_ANDROID
  if (!requestStoragePermission())
    return -1;
#endif
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
