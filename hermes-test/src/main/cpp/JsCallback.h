//
// Created by ikvarxt on 10/29/2024.
//

#pragma once
#include <fbjni/fbjni.h>
#include <jsi/jsi.h>

using namespace facebook::jsi;
using namespace facebook::jni;

struct JsCallback : JavaClass<JsCallback> {

  static auto constexpr kJavaDescriptor =
      "Lcom/example/hermes_test/JsCallback;";

  void invoke(local_ref<JObject> arg) {
    const auto method = getClass()->getMethod<void(local_ref<JObject>)>("call");
    method(self(), arg);
  }
};
