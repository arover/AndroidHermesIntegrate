//
// Created by ikvarxt on 10/25/2024.
//

#pragma once

#include <JsCallback.h>
#include <fbjni/fbjni.h>

using namespace facebook::jni;

struct FbJniRunner : public JavaClass<FbJniRunner> {

public:
  static constexpr const char *kJavaDescriptor =
      "Lcom/example/hermes/FbJniRunner;";

  static void registerNatives() {
    javaClassStatic()->registerNatives({
        makeNativeMethod("nativeEval", FbJniRunner::nativeEval),
        makeNativeMethod("getStringHello", FbJniRunner::getStringHello),
        makeNativeMethod("testJsFunctionCall", FbJniRunner::testJsFunctionCall),
        makeNativeMethod("callFuncWithArgs", FbJniRunner::callFuncWithArgs),
        makeNativeMethod("evalWithCallback", FbJniRunner::evalWithCallback),
    });
  }

private:
  static std::string nativeEval(alias_ref<FbJniRunner::javaobject>,
                                const alias_ref<jstring> &script);

  static std::string getStringHello(alias_ref<FbJniRunner::javaobject>);

  static std::string testJsFunctionCall(alias_ref<FbJniRunner::javaobject>,
                                        std::string arg);
  static std::string callFuncWithArgs(alias_ref<FbJniRunner::javaobject>,
                                      std::string script, std::string funcName,
                                      alias_ref<JArrayList<JObject>> args);
  static local_ref<JObject> evalWithCallback(alias_ref<FbJniRunner::javaobject>,
                                             std::string script,
                                             std::string callbackName,
                                             alias_ref<JsCallback> callback);
};
