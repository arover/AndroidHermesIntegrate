//
// Created by ikvarxt on 10/25/2024.
//

#include "FbJniRunner.h"
#include "ValueConverter.h"
#include "runner.h"
#include <JsCallback.h>
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

local_ref<JObject>
FbJniRunner::evalWithCallback(alias_ref<FbJniRunner::javaobject>,
                              std::string script, std::string callbackName,
                              alias_ref<JsCallback> callback) {

  std::unique_ptr<Runtime> rt = facebook::hermes::makeHermesRuntime();

  HostFunctionType myHostFunction =
      [&callback](Runtime &rt, const Value &thisVal, const Value *args,
                  size_t count) -> Value {
    try {
      local_ref<JObject> arg;
      if (count == 0) {
        arg = nullptr;
      } else if (count > 1) {
        Array jsArr(rt, count);
        for (int i = 0; i < count; i++) {
          jsArr.setValueAtIndex(rt, i, args[i]);
        }
        arg = jObjectFromValue(rt, std::move(jsArr));
      } else {
        arg = jObjectFromValue(rt, args[0]);
      }
      callback->invoke(arg);
    } catch (JSIException &e) {
      throw std::runtime_error(e.what());
    }
    return Value::undefined();
  };

  auto cbPropNameId = PropNameID::forUtf8(*rt, callbackName);
  Function callbackHostFunction =
      Function::createFromHostFunction(*rt, cbPropNameId, 0, myHostFunction);

  rt->global().setProperty(*rt, cbPropNameId, callbackHostFunction);

  auto res = rt->evaluateJavaScript(std::make_unique<StringBuffer>(script),
                                    "evalWithCallback");
  return jObjectFromValue(*rt, res);
}
