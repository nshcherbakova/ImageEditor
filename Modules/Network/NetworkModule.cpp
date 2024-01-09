#include "NetworkModule.h"
#include "Network.h"
#include <stdafx.h>

namespace {
using namespace ImageEditor;
using namespace ImageEditor::Modules;
INetworkInjector module() noexcept {
  return boost::di::make_injector(
      boost::di::bind<INetwork>().to<NetworkImpl>().in(boost::di::singleton));
}
} // namespace

namespace ImageEditor::Modules {
INetworkInjector InitNetworkModule() {
  return boost::di::make_injector(module());
}
} // namespace ImageEditor::Modules
