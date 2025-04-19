//
// Created by ikvarxt on 4/10/2025.
//

#pragma once

#include <fbjni/fbjni.h>
#include <jsi/jsi.h>

using namespace facebook::jsi;
using namespace facebook::jni;

struct NativeFunction : JavaClass<NativeFunction> {

  static auto constexpr kJavaDescriptor = "Lcom/example/hermes/NativeFunction;";

  [[nodiscard]] local_ref<JObject>
  invoke(const alias_ref<JList<JObject>> &args) const {
    static const auto method =
        getClass()->getMethod<jobject(alias_ref<JList<JObject>>)>("invoke");
    return method(self(), args);
  }
};
