//
// Created by ikvarxt on 10/26/2024.
//

#include "HermesRuntime.h"
#include <fbjni/fbjni.h>
#include <hermes/hermes.h>
#include <jsi/jsi.h>

using namespace facebook;

const char *TAG = "HermesRuntime";

HermesRuntime::HermesRuntime() {
  rt = facebook::hermes::makeHermesRuntime();
  log_::loge(TAG, "HermesRuntime construct rt=%u", &rt);
}

jni::local_ref<jobject>
HermesRuntime::nativeEvaluateJavascript(jni::alias_ref<jstring> script) {
  auto env = jni::Environment::current();
  const char *nativeScript = env->GetStringUTFChars(script.get(), nullptr);
  auto value = rt->evaluateJavaScript(
      std::make_unique<jsi::StringBuffer>(nativeScript), "eval");

  if (value.isUndefined()) {
    return make_local(env->NewStringUTF("undefined"));
  } else {
    auto res = env->NewStringUTF(value.asString(*rt).utf8(*rt).c_str());
    return make_local(res);
  }
}