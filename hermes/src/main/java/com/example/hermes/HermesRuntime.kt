@file:Suppress("KotlinJniMissingFunction", "FunctionName")

package com.example.hermes

import androidx.annotation.VisibleForTesting
import com.facebook.jni.HybridData

class HermesRuntime {

    @VisibleForTesting
    val mHybridData: HybridData = _initHybridData()

    fun eval(script: String) = _evaluateJavascript(script)
    fun callFunction(funName: String): Any = _callFunction(funName)

    private external fun _initHybridData(): HybridData
    private external fun _evaluateJavascript(script: String): Any
    private external fun _callFunction(name: String): Any
}