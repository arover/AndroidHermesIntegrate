//
// Created by ikvarxt on 10/25/2024.
//

#pragma once

#include <fbjni/fbjni.h>
#include <jsi/jsi.h>

using namespace facebook::jni;

struct HermesRuntime : public HybridClass<HermesRuntime> {
public:
  static constexpr const char *kJavaDescriptor =
      "Lcom/example/hermes/HermesRuntime;";

  static void registerNatives() {
    javaClassStatic()->registerNatives({
        makeNativeMethod("nativeInitHybridData",
                         HermesRuntime::nativeInitHybridData),
    });

    registerHybrid({makeNativeMethod("nativeEvaluateJavascript",
                                     HermesRuntime::nativeEvaluateJavascript)});
  }

private:
  friend HybridBase;
  using HybridBase::HybridBase;
  std::shared_ptr<facebook::jsi::Runtime> rt;

  HermesRuntime();

  static local_ref<jhybriddata> nativeInitHybridData(alias_ref<jclass>) {
    return makeCxxInstance();
  };

  local_ref<jobject> nativeEvaluateJavascript(alias_ref<jstring> script);
};