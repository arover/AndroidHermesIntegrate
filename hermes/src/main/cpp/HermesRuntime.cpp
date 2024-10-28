//
// Created by ikvarxt on 10/26/2024.
//

#include "HermesRuntime.h"
#include "ValueConverter.h"
#include <fbjni/fbjni.h>
#include <hermes/hermes.h>
#include <jsi/jsi.h>

using namespace facebook::jni;
using namespace facebook::jsi;

const char *TAG = "HermesRuntime";

HermesRuntime::HermesRuntime() {
  rt = facebook::hermes::makeHermesRuntime();
  log_::loge(TAG, "HermesRuntime construct rt=%u", &rt);
}

local_ref<JObject>
HermesRuntime::nativeEvaluateJavascript(alias_ref<JString> script) {
  auto env = Environment::current();
  const char *nativeScript = env->GetStringUTFChars(script.get(), nullptr);
  auto value = rt->evaluateJavaScript(
      std::make_unique<StringBuffer>(nativeScript), "eval");

  return jObjectFromValue(*rt, value);
}

local_ref<JObject>
HermesRuntime::nativeCallFunction(alias_ref<JString> methodName) {
  auto function = rt->global().getPropertyAsFunction(
      *rt, methodName->toStdString().c_str());
  auto value = function.call(*rt);
  return jObjectFromValue(*rt, value);
}
