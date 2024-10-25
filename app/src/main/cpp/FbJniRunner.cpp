//
// Created by ikvarxt on 10/25/2024.
//

#include "runner.h"
#include <fbjni/fbjni.h>

using namespace facebook::jni;

struct FbJniRunner : public JavaClass<FbJniRunner> {
public:
  static constexpr auto kJavaDescriptor =
      "Lcom/example/hermesandroidintegrate/FbJniRunner;";

  static void registerNatives() {
    javaClassStatic()->registerNatives(
        {makeNativeMethod("nativeEval", FbJniRunner::nativeEval)});
  }

private:
  static std::string nativeEval(alias_ref<FbJniRunner::javaobject> runner,
                                const alias_ref<jstring>& script);
};

std::string FbJniRunner::nativeEval(alias_ref<FbJniRunner::javaobject> runner,
                                    const alias_ref<jstring>& script) {
  auto env = Environment::current();
  const char *nativeScript = env->GetStringUTFChars(script.get(), nullptr);

  std::string res = runner_eval(nativeScript, "nativeEval");
  env->ReleaseStringUTFChars(script.get(), nativeScript);

  return res;
}

__attribute__((visibility("default"))) jint JNI_OnLoad(JavaVM *vm, void *) {
  return initialize(vm, [] {
    facebook::jni::log_::loge("JNI_OnLoad", "register");
    FbJniRunner::registerNatives();
  });
}
