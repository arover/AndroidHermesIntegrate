//
// Created by ikvarxt on 10/25/2024.
//

#pragma once

#include <fbjni/fbjni.h>
#include <jsi/jsi.h>

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
         makeNativeMethod("_callFunction", HermesRuntime::callFunction)});
  }

private:
  friend HybridBase;
  using HybridBase::HybridBase;
  std::shared_ptr<Runtime> rt;

  HermesRuntime();

  static local_ref<jhybriddata> initHybridData(alias_ref<JClass>) {
    return makeCxxInstance();
  };

  local_ref<JObject> evaluateJavascript(alias_ref<JString> script);
  local_ref<JObject> callFunction(std::string methodName,
                                  alias_ref<JList<JObject>> args);
};