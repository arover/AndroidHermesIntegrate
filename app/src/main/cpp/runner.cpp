//
// Created by ikvarxt on 10/24/2024.
//

#include <android/log.h>
#include <fbjni/fbjni.h>
#include <hermes/hermes.h>
#include <iostream>

using namespace facebook;

static const char *TAG = "runner";

/// Print all arguments separated by spaces.
static jsi::Value hostMyPrint(jsi::Runtime &rt, const jsi::Value &,
                              const jsi::Value *args, size_t count) {
  for (size_t i = 0; i < count; ++i) {
    if (i)
      std::cout << ' ';
    std::cout << args[i].toString(rt).utf8(rt);
    __android_log_print(ANDROID_LOG_INFO, TAG, "MyPrint: %s",
                        args[i].toString(rt).utf8(rt).c_str());
  }
  std::cout << std::endl;
  return jsi::Value::undefined();
}

void registerNatives(jsi::Runtime &rt) {
  rt.global().setProperty(
      rt, "myPrint",
      jsi::Function::createFromHostFunction(
          rt, jsi::PropNameID::forAscii(rt, "print"), 0, hostMyPrint));
  rt.global().setProperty(rt, "stringList",
                          jsi::Array::createWithElements(rt, "abc", "bcd"));
}

std::string runner_eval(const char *script, std::string name) {

  // Create the Hermes runtime.
  auto runtime = facebook::hermes::makeHermesRuntime();

  registerNatives(*runtime);

  // Execute some JS.
  std::string res;
  try {
    auto value = runtime->evaluateJavaScript(
        std::make_unique<jsi::StringBuffer>(script), name);
    res = value.toString(*runtime).utf8(*runtime);
  } catch (jsi::JSError &e) {
    // Handle JS exceptions here.
    jni::log_::loge(TAG, "JS Exception: %s", e.getStack().c_str());
    res = e.getStack();
  } catch (jsi::JSIException &e) {
    // Handle JSI exceptions here.
    jni::log_::loge(TAG, "JSI Exception: %s", e.what());
    res = e.what();
  }
  return res;
}
