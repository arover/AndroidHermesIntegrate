//
// Created by ikvarxt on 10/25/2024.
//

#pragma once

#include <fbjni/fbjni.h>

using namespace facebook::jni;

struct FbJniRunner : public JavaClass<FbJniRunner> {

public:
  static constexpr const char *kJavaDescriptor =
      "Lcom/example/hermes/FbJniRunner;";

  static void registerNatives();

private:
  static std::string nativeEval(alias_ref<FbJniRunner::javaobject>,
                                const alias_ref<jstring> &script);

  static std::string getStringHello(alias_ref<FbJniRunner::javaobject>);

  static std::string testJsFunctionCall(alias_ref<FbJniRunner::javaobject>,
                                        std::string arg);
};
