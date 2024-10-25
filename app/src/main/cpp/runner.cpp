//
// Created by admin on 10/24/2024.
//

#include <android/log.h>
#include <hermes/hermes.h>
#include <iostream>
#include <fbjni/fbjni.h>

static const char *TAG = "runner";

/// Print all arguments separated by spaces.
static facebook::jsi::Value hostMyPrint(facebook::jsi::Runtime &rt,
                                        const facebook::jsi::Value &,
                                        const facebook::jsi::Value *args,
                                        size_t count) {
  for (size_t i = 0; i < count; ++i) {
    if (i)
      std::cout << ' ';
    std::cout << args[i].toString(rt).utf8(rt);
    __android_log_print(ANDROID_LOG_INFO, TAG, "MyPrint: %s",
                        args[i].toString(rt).utf8(rt).c_str());
  }
  std::cout << std::endl;
  return facebook::jsi::Value::undefined();
}

void registerNatives(facebook::jsi::Runtime &rt) {
  rt.global().setProperty(rt, "myPrint",
                          facebook::jsi::Function::createFromHostFunction(
                              rt,
                              facebook::jsi::PropNameID::forAscii(rt, "print"),
                              0, hostMyPrint));
  rt.global().setProperty(
      rt, "stringList",
      facebook::jsi::Array::createWithElements(rt, "abc", "bcd"));
}

int runner_eval(const char *script, std::string &name) {

  // You can Customize the runtime config here.
  auto runtimeConfig =
      hermes::vm::RuntimeConfig::Builder().withIntl(false).build();

  // Create the Hermes runtime.
  auto runtime = facebook::hermes::makeHermesRuntime(runtimeConfig);

  registerNatives(*runtime);

  // Execute some JS.
  int status = 0;
  try {
    runtime->evaluateJavaScript(
        std::make_unique<facebook::jsi::StringBuffer>(script), name);
  } catch (facebook::jsi::JSError &e) {
    // Handle JS exceptions here.
    __android_log_print(ANDROID_LOG_INFO, TAG, "JS Exception: %s",
                        e.getStack().c_str());
    std::cerr << "JS Exception: " << e.getStack() << std::endl;
    status = 1;
  } catch (facebook::jsi::JSIException &e) {
    // Handle JSI exceptions here.
    __android_log_print(ANDROID_LOG_INFO, TAG, "JSI Exception: %s", e.what());
    std::cerr << "JSI Exception: " << e.what() << std::endl;
    status = 1;
  }

  return status;
}
