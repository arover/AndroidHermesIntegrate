@file:Suppress("KotlinJniMissingFunction", "FunctionName")

package com.example.hermes

import androidx.annotation.VisibleForTesting
import com.facebook.jni.HybridData

class HermesRuntime {

    @VisibleForTesting
    val mHybridData: HybridData = _initHybridData()

    fun eval(script: String) = _evaluateJavascript(script)

    fun registerFunction(name: String, func: NativeFunction) =
        _registerNativeFunc(name, func)

    fun callFunction(funName: String, args: List<Any> = listOf()): Any =
        _callFunction(funName, args)

    fun getProperty(propName: String): Any = _getProperty(propName)

    private external fun _initHybridData(): HybridData

    private external fun _evaluateJavascript(script: String): Any
    private external fun _callFunction(name: String, args: List<Any>): Any
    private external fun _getProperty(propName: String): Any
    private external fun _registerNativeFunc(name: String, funcRef: NativeFunction): Boolean
}