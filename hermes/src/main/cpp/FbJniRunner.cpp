//
// Created by ikvarxt on 10/25/2024.
//

#include "FbJniRunner.h"
#include "runner.h"
#include <fbjni/fbjni.h>
#include <hermes/hermes.h>
#include <jsi/jsi.h>

using namespace facebook::jni;
using namespace facebook::jsi;

void FbJniRunner::registerNatives() {
  javaClassStatic()->registerNatives({
      makeNativeMethod("nativeEval", FbJniRunner::nativeEval),
      makeNativeMethod("getStringHello", FbJniRunner::getStringHello),
      makeNativeMethod("testJsFunctionCall", FbJniRunner::testJsFunctionCall),
  });
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
  return "Hello from FbJniRunner";
}

std::string FbJniRunner::testJsFunctionCall(alias_ref<FbJniRunner::javaobject>,
                                            std::string arg) {

  auto rt = facebook::hermes::makeHermesRuntime();

  const char *funcDeclaration = "function hello(s) { return 'hello ' + s; }";
  rt->evaluateJavaScript(std::make_unique<StringBuffer>(funcDeclaration),
                         "test");

  Function helloFunc = rt->global().getPropertyAsFunction(*rt, "hello");

  auto res = helloFunc.call(*rt, String::createFromUtf8(*rt, arg));

  return res.getString(*rt).utf8(*rt);
}
