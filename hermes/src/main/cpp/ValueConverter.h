//
// Created by ikvarxt on 10/28/2024.
//

#pragma once

#include <fbjni/fbjni.h>
#include <jsi/jsi.h>

using namespace facebook::jni;
using namespace facebook::jsi;

Value valueFromJObject(Runtime &runtime, alias_ref<JObject> jObject);

local_ref<JObject> jObjectFromValue(Runtime &runtime, const Value &value);
