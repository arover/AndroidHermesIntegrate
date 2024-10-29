@file:Suppress("KotlinJniMissingFunction", "FunctionName")

package com.example.hermes

import androidx.annotation.VisibleForTesting
import com.facebook.jni.HybridData

class HermesRuntime {

    @VisibleForTesting
    val mHybridData: HybridData = _initHybridData()

    fun eval(script: String) = _evaluateJavascript(script)

    // TODO: 10/28/2024 vararg will erase arg type that passing to jni, Why
    // fun callFunction(funName: String, vararg arg: Any): Any =
    //     _callFunction(funName, listOf(arg))

    fun callFunction(funName: String, args: List<Any> = listOf()): Any =
        _callFunction(funName, args)

    fun getProperty(propName: String): Any = _getProperty(propName)

    private external fun _initHybridData(): HybridData

    private external fun _evaluateJavascript(script: String): Any
    private external fun _callFunction(name: String, args: List<Any>): Any
    private external fun _getProperty(propName: String): Any
    private external fun _registerNativeFunction()
}