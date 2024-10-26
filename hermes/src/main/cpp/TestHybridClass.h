//
// Created by ikvarxt on 10/26/2024.
//

#pragma once

#include <fbjni/fbjni.h>

using namespace facebook::jni;

struct NativeRunner : public JavaClass<NativeRunner> {
  static auto constexpr *kJavaDescriptor = "Lcom/example/hermes/NativeRunner;";
};

struct TestHybridClass : public HybridClass<TestHybridClass, NativeRunner> {
  static auto constexpr *kJavaDescriptor =
      "Lcom/example/hermes/TestHybridClass;";

  TestHybridClass(alias_ref<jclass>) {
    log_::loge("Hybrid", "constructor");
  }

  static void registerNatives() {
    registerHybrid({
        makeNativeMethod("initHybridData", TestHybridClass::initHybridData),
        makeNativeMethod("nativeInvoke", TestHybridClass::nativeInvoke),
    });
  }

  static local_ref<jhybriddata> initHybridData(alias_ref<jclass>) {
    log_::loge("Hybrid", "initHybridData");
    return makeCxxInstance();
  }

  static local_ref<jobject> nativeInvoke(alias_ref<jclass>,
                                         alias_ref<jobject> obj) {
    auto env = Environment::current();
    auto obj_str = obj->toString();
    auto str_obj = env->NewStringUTF(obj_str.c_str());
    return make_local(str_obj);
  }

private:
  friend HybridBase;
  using HybridBase::HybridBase;
};
