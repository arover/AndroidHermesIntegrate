//
// Created by ikvarxt on 10/26/2024.
//

#include "HermesRuntime.h"
#include "ValueConverter.h"
#include <fbjni/fbjni.h>
#include <hermes/hermes.h>
#include <jsi/jsi.h>
#include <vector>

using namespace facebook::jni;
using namespace facebook::jsi;

const char *TAG = "HermesRuntime";

HermesRuntime::HermesRuntime() {
  try {
    rt = facebook::hermes::makeHermesRuntime();
    log_::loge(TAG, "HermesRuntime constructed successfully");
  } catch (std::exception &e) {
    log_::loge(TAG, "Error creating HermesRuntime: %s", e.what());
    throw;
  }
}

local_ref<JObject>
HermesRuntime::evaluateJavascript(alias_ref<JString> script) {
  try {
    auto env = Environment::current();
    const char *nativeScript = env->GetStringUTFChars(script.get(), nullptr);

    auto value = rt->evaluateJavaScript(
        std::make_unique<StringBuffer>(nativeScript), "eval");

    env->ReleaseStringUTFChars(script.get(), nativeScript);

    return jObjectFromValue(*rt, value);
  } catch (std::exception &e) {
    log_::loge(TAG, "Error evaluating JavaScript: %s", e.what());
    throw;
  }
}

local_ref<JObject> HermesRuntime::callFunction(std::string methodName,
                                               alias_ref<JList<JObject>> args) {
  try {
    Function function =
        rt->global().getPropertyAsFunction(*rt, methodName.c_str());

    Value jsArgs[args->size()];

    int i = 0;
    for (auto &elem : *args) {
      auto value = valueFromJObject(*rt, elem);
      jsArgs[i] = std::move(value);
      i++;
    }

    Value res = function.call(*rt, jsArgs, args->size());
    return jObjectFromValue(*rt, res);
  } catch (std::exception &e) {
    log_::loge(TAG, "Error calling function %s: %s", methodName.c_str(),
               e.what());
    throw;
  }
}

local_ref<JObject> HermesRuntime::getProperty(std::string propName) {
  try {
    Value value = rt->global().getProperty(*rt, propName.c_str());

    return jObjectFromValue(*rt, value);
  } catch (std::exception &e) {
    log_::loge(TAG, "Error getting property %s: %s", propName.c_str(),
               e.what());
    throw;
  }
}

static local_ref<JObject> getJObjectFromJsArgs(Runtime &rt, const Value *args,
                                               size_t count) {
  local_ref<JObject> res;
  if (count == 0) {
    res = nullptr;
  } else if (count > 1) {
    Array jsArr(rt, count);
    for (int i = 0; i < count; i++) {
      jsArr.setValueAtIndex(rt, i, args[i]);
    }
    res = jObjectFromValue(rt, std::move(jsArr));
  } else {
    res = jObjectFromValue(rt, args[0]);
  }
  return res;
}

bool HermesRuntime::registerNativeFunc(const std::string &name,
                                       alias_ref<NativeFunction> func) {
  try {
    auto globalFunc = make_global(func);

    nativeFunctions[name] = std::move(globalFunc);

    log_::loge(TAG, "registered#%d %s", nativeFunctions.size(), name.c_str());

    HostFunctionType myHostFunction =
        [this, name](Runtime &rt, const Value &thisVal, const Value *args,
                     size_t count) -> Value {
      try {
        auto it = nativeFunctions.find(name);
        if (it == nativeFunctions.end()) {
          throw JSError(rt, "Native function not found: " + name);
        }

        auto arrayList = JArrayList<JObject>::create(count);
        for (size_t i = 0; i < count; i++) {
          arrayList->add(jObjectFromValue(rt, args[i]));
        }

        auto result = it->second->invoke(arrayList);

        if (result == nullptr) {
          return Value::undefined();
        }
        return valueFromJObject(rt, result);
      } catch (std::exception &e) {
        throw JSError(rt, e.what());
      }
    };

    auto funcName = PropNameID::forAscii(*rt, name);
    rt->global().setProperty(
        *rt, funcName,
        Function::createFromHostFunction(*rt, funcName, 0, myHostFunction));

    return true;
  } catch (std::exception &e) {
    log_::loge(TAG, "Error registering native function: %s", e.what());
    return true;
  }
}
