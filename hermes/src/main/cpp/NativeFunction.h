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

    [[nodiscard]] local_ref<JObject> invoke(alias_ref<JList<JObject>> args) const {
        // need package class reference
        auto kJavaInterface = "com/example/hermes/NativeFunction";
        // get interface
        static const auto interfaceClass = findClassStatic(kJavaInterface);
        // get method from interface not class
        static const auto method = interfaceClass->getMethod<jobject(alias_ref<JList<JObject>>)>("invoke");

        return method(self(), args);
    }

};
