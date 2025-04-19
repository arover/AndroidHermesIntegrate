//
// Created by ikvarxt on 10/25/2024.
//

#pragma once

#include "NativeFunction.h"
#include <fbjni/fbjni.h>
#include <jsi/jsi.h>
#include <unordered_map>

using namespace facebook::jni;
using namespace facebook::jsi;

struct HermesRuntime : public HybridClass<HermesRuntime> {
public:
  static constexpr const char *kJavaDescriptor =
      "Lcom/example/hermes/HermesRuntime;";

  static void registerNatives() {
    javaClassStatic()->registerNatives({
        makeNativeMethod("_initHybridData", HermesRuntime::initHybridData),
    });

    registerHybrid(
        {makeNativeMethod("_evaluateJavascript",
                          HermesRuntime::evaluateJavascript),
         makeNativeMethod("_callFunction", HermesRuntime::callFunction),
         makeNativeMethod("_getProperty", HermesRuntime::getProperty),
         makeNativeMethod("_registerNativeFunc",
                          HermesRuntime::registerNativeFunc)});
  }

private:
  friend HybridBase;
  using HybridBase::HybridBase;
  std::shared_ptr<Runtime> rt;
  std::unordered_map<std::string, global_ref<NativeFunction>> nativeFunctions;

  HermesRuntime();

  static local_ref<jhybriddata> initHybridData(alias_ref<JClass>) {
    return makeCxxInstance();
  };

  local_ref<JObject> evaluateJavascript(alias_ref<JString> script);
  local_ref<JObject> callFunction(std::string methodName,
                                  alias_ref<JList<JObject>> args);
  local_ref<JObject> getProperty(std::string propName);
  bool registerNativeFunc(const std::string &name,
                          alias_ref<NativeFunction> func);
};