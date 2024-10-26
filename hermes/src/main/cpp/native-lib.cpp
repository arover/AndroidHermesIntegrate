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
Java_com_example_hermes_EvLoop_evalJavascriptScript(
    JNIEnv *env, jobject, jstring script) {}

extern "C" JNIEXPORT jint JNICALL
Java_com_example_hermes_Runner_eval(JNIEnv *env, jobject,
                                                    jstring script) {
  const char *scriptBuffer = env->GetStringUTFChars(script, nullptr);
  auto res = runner_eval(scriptBuffer, "Runner_eval_script");
  env->ReleaseStringUTFChars(script, scriptBuffer);
  return 0;
}