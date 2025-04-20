//
// Created by ikvarxt on 10/29/2024.
//
#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-static-cast-downcast"

#include <fbjni/fbjni.h>
#include <jsi/jsi.h>

using namespace facebook::jni;
using namespace facebook::jsi;

Value valueFromJObject(Runtime &runtime, alias_ref<JObject> jObject) {

  if (jObject->isInstanceOf(JBoolean::javaClassStatic())) {
    auto *jBoolean = static_cast<JBoolean *>(jObject.operator->());
    return jBoolean->booleanValue() == JNI_TRUE;

  } else if (jObject->isInstanceOf(JString::javaClassStatic())) {
    auto *jString = static_cast<JString *>(jObject.operator->());
    return String::createFromUtf8(runtime, jString->toStdString());

  } else if (jObject->isInstanceOf(JDouble::javaClassStatic())) {
    auto *jDouble = static_cast<JDouble *>(jObject.operator->());
    return jDouble->value();

  } else if (jObject->isInstanceOf(JInteger::javaClassStatic())) {
    auto *jInteger = static_cast<JInteger *>(jObject.operator->());
    return jInteger->value();

  } else if (jObject->isInstanceOf(JList<jobject>::javaClassStatic())) {
    auto *jList = static_cast<JList<jobject> *>(jObject.operator->());

    Array ret(runtime, jList->size());
    int i = 0;
    for (auto &elem : *jList) {
      ret.setValueAtIndex(runtime, i, valueFromJObject(runtime, elem));
      ++i;
    }
    return std::move(ret);

  } else if (jObject->isInstanceOf(JMap<jobject, jobject>::javaClassStatic())) {
    auto *jMap = static_cast<JMap<jobject, jobject> *>(jObject.operator->());
    Object ret(runtime);
    for (const auto &entry : *jMap) {
      if (entry.first) {
        auto propNameId = PropNameID::forUtf8(runtime, entry.first->toString());
        ret.setProperty(runtime, propNameId,
                        valueFromJObject(runtime, entry.second));
      }
    }
    return std::move(ret);
  } else {
    throw JSError(runtime,
                  "can not convert to JSI value, unknown JObject type");
  }
}

local_ref<JObject> jObjectFromValue(Runtime &runtime, const Value &value) {

  if (value.isUndefined() || value.isNull()) {
    return nullptr;

  } else if (value.isBool()) {
    return JBoolean::valueOf(value.getBool());

  } else if (value.isNumber()) {
    return JDouble::valueOf(value.getNumber());

  } else if (value.isString()) {
      return make_jstring(value.getString(runtime).utf8(runtime));

  } else if (value.isObject()) {
      auto isFunction = value.asObject(runtime).isFunction(runtime);
      return make_jstring(std::string("property is ") + (isFunction ? "function" : "object"));

  } else {
    Object obj = value.getObject(runtime);

    if (obj.isArray(runtime)) {
      Array array = obj.getArray(runtime);
      static auto arrayClass = JArrayList<JObject>::javaClassStatic();
      static auto constructor =
          arrayClass->getConstructor<JArrayList<JObject>::javaobject()>();
      auto jList = arrayClass->newObject(constructor);
      auto addMethod =
          arrayClass->getMethod<jboolean(local_ref<JObject>)>("add");
      for (size_t i = 0; i < array.size(runtime); ++i) {
        auto cur = array.getValueAtIndex(runtime, i);
        addMethod(jList, jObjectFromValue(runtime, cur));
      }
      return jList;

    } else if (obj.isFunction(runtime)) {
      throw JSError(runtime, "JS Functions are not convertible to JObject");

    } else {
      static auto hashmapClass = JHashMap<JString, JObject>::javaClassStatic();
      static auto constructor =
          hashmapClass
              ->getConstructor<JHashMap<JString, JObject>::javaobject()>();
      auto map = hashmapClass->newObject(constructor);
      auto putMethod =
          hashmapClass
              ->getMethod<jobject(local_ref<JObject>, local_ref<JObject>)>(
                  "put");

      Array names = obj.getPropertyNames(runtime);
      for (size_t i = 0; i < names.size(runtime); ++i) {
        String name = names.getValueAtIndex(runtime, i).getString(runtime);
        Value prop = obj.getProperty(runtime, name);

        if (prop.isUndefined())
          continue;

        // The JSC conversion uses JSON.stringify, which substitutes
        // null for a function, so we do the same here.  Just dropping
        // the pair might also work, but would require more testing.
        if (prop.isObject() && prop.getObject(runtime).isFunction(runtime)) {
          prop = Value::null();
        }
        putMethod(map, make_jstring(name.utf8(runtime)),
                  jObjectFromValue(runtime, prop));
      }
      return map;
    }
  }
}
#pragma clang diagnostic pop