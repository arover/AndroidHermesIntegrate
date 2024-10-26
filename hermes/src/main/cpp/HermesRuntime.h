//
// Created by ikvarxt on 10/25/2024.
//

#pragma once

#include <fbjni/fbjni.h>

using namespace facebook::jni;

struct HermesRuntime : public HybridClass<HermesRuntime> {
  static constexpr const char *kJavaDescriptor =
      "Lcom/example/hermes/HermesRuntime;";

  static void registerNatives() {
    registerHybrid({makeNativeMethod("nativeInitHybridData",
                                     HermesRuntime::nativeInitHybridData),
                    makeNativeMethod("nativeEvaluateJavascript",
                                     HermesRuntime::nativeEvaluateJavascript)});
  }

  static local_ref<jhybriddata> nativeInitHybridData(alias_ref<jclass>) {
    return makeCxxInstance();
  };

  static local_ref<jobject> nativeEvaluateJavascript(alias_ref<jclass>,
                                                     alias_ref<jstring> script);

private:
  friend HybridBase;
  using HybridBase::HybridBase;
};