//
// Created by ikvarxt on 10/26/2024.
//

#include "HermesRuntime.h"
#include <fbjni/fbjni.h>

using namespace facebook::jni;

local_ref<jobject>
HermesRuntime::nativeEvaluateJavascript(alias_ref<jclass>,
                                        alias_ref<jstring> script) {
  auto env = Environment::current();

  return make_local(script);
}