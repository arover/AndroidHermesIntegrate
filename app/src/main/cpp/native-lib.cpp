#include "runner.h"
#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_hermesandroidintegrate_MainActivity_stringFromJNI(
    JNIEnv *env, jobject /* this */) {
  std::string hello = "Hello from C++";
  return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_hermesandroidintegrate_EvLoop_evalJavascriptScript(
    JNIEnv *env, jobject, jstring script) {}

extern "C" JNIEXPORT jint JNICALL
Java_com_example_hermesandroidintegrate_Runner_eval(JNIEnv *env, jobject,
                                                    jstring script,
                                                    jstring name) {
  const char *nativeScriptChars = env->GetStringUTFChars(script, 0);
  std::string scriptName(env->GetStringUTFChars(name, 0));
  return runner_eval(nativeScriptChars, scriptName);
}