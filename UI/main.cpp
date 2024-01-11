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
static const char *c_log_str = "/logs/ImageEditorLog.txt";
static const char *c_logger_str = "logger";

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
    auto logger = spdlog::basic_logger_mt(
        c_logger_str, QDir::currentPath().toStdString() + c_log_str);
    spdlog::set_default_logger(logger);
  } catch (const spdlog::spdlog_ex &ex) {
    UNI_ASSERT(false);
  }
  spdlog::info("Initialyse ImageEditor");

  QSurfaceFormat fmt;
  fmt.setSamples(16);
  QSurfaceFormat::setDefaultFormat(fmt);
  QApplication a(argc, argv);

  QCoreApplication::setOrganizationName(c_org_str);
  QCoreApplication::setApplicationName(c_app_str);
  QSettings(QSettings::Scope::SystemScope)
      .setValue("ImageServer", "http://localhost:8081/");

  QFontDatabase::addApplicationFont(c_font_str);

#ifdef Q_OS_ANDROID
#ifdef REQUEST_PERMISSIONS_ON_ANDROID
  if (!requestStoragePermission())
    return -1;
#endif

  QJniObject activity = QJniObject::callStaticObjectMethod(
      "org/qtproject/qt5/android/QtNative", "activity",
      "()Landroid/app/Activity;");
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

  spdlog::info("ImageEditor was closed");
  return a.exec();
}
