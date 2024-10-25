//
// Created by ikvarxt on 10/25/2024.
//

#include "runner.h"
#include <fbjni/fbjni.h>
#include <FbJniRunner.h>

using namespace facebook::jni;

void FbJniRunner::registerNatives() {
  javaClassStatic()->registerNatives(
      {makeNativeMethod("nativeEval", FbJniRunner::nativeEval),
       makeNativeMethod("getStringHello", FbJniRunner::getStringHello)});
}

std::string FbJniRunner::nativeEval(alias_ref<FbJniRunner::javaobject>,
                              const alias_ref<jstring> &script) {
  auto env = Environment::current();
  const char *nativeScript = env->GetStringUTFChars(script.get(), nullptr);

  std::string res = runner_eval(nativeScript, "nativeEval");
  env->ReleaseStringUTFChars(script.get(), nativeScript);

  return res;
}

std::string FbJniRunner::getStringHello(alias_ref<FbJniRunner::javaobject>) {
  return "Hello";
}
