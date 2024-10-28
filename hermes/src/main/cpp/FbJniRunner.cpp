//
// Created by ikvarxt on 10/25/2024.
//

#include "FbJniRunner.h"
#include "ValueConverter.h"
#include "runner.h"
#include <fbjni/fbjni.h>
#include <hermes/hermes.h>
#include <jsi/jsi.h>

using namespace facebook::jni;
using namespace facebook::jsi;

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

std::string FbJniRunner::callFuncWithArgs(alias_ref<FbJniRunner::javaobject>,
                                          std::string script,
                                          std::string funcName,
                                          alias_ref<JArrayList<JObject>> args) {
  std::unique_ptr<Runtime> rt = facebook::hermes::makeHermesRuntime();

  rt->evaluateJavaScript(std::make_unique<StringBuffer>(script),
                         "callFuncWithArgs");

  Function func = rt->global().getPropertyAsFunction(*rt, funcName.c_str());

  Array jsArg(*rt, args->size());
  int i = 0;
  for (auto &elem : *args) {
    auto value = valueFromJObject(*rt, elem);
    jsArg.setValueAtIndex(*rt, i, value);
    ++i;
  }
  Value res = func.call(*rt, jsArg);

  return res.getString(*rt).utf8(*rt);
}
