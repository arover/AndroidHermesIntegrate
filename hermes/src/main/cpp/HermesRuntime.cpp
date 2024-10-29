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
HermesRuntime::evaluateJavascript(alias_ref<JString> script) {
  auto env = Environment::current();
  const char *nativeScript = env->GetStringUTFChars(script.get(), nullptr);
  auto value = rt->evaluateJavaScript(
      std::make_unique<StringBuffer>(nativeScript), "eval");

  return jObjectFromValue(*rt, value);
}

local_ref<JObject> HermesRuntime::callFunction(std::string methodName,
                                               alias_ref<JList<JObject>> args) {
  Function function =
      rt->global().getPropertyAsFunction(*rt, methodName.c_str());

  Value jsArgs[args->size()];

  int i = 0;
  for (auto &elem : *args) {
    auto value = valueFromJObject(*rt, elem);
    jsArgs[i] = std::move(value);
    i++;
  }

  Value res = function.call(*rt, jsArgs, args->size());
  return jObjectFromValue(*rt, res);
}

local_ref<JObject> HermesRuntime::getProperty(std::string propName) {
  Value value = rt->global().getProperty(*rt, propName.c_str());
  return jObjectFromValue(*rt, value);
}
