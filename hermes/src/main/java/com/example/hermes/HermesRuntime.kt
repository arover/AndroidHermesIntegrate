@file:Suppress("KotlinJniMissingFunction")

package com.example.hermes

import androidx.annotation.VisibleForTesting
import com.facebook.jni.HybridData

class HermesRuntime {

    @VisibleForTesting
    val mHybridData: HybridData = nativeInitHybridData()

    fun eval(script: String) = nativeEvaluateJavascript(script)
    fun callFunction(funName: String): Any =
        nativeCallFunction(funName)

    private external fun nativeInitHybridData(): HybridData
    private external fun nativeEvaluateJavascript(script: String): Any
    private external fun nativeCallFunction(name: String): Any
}