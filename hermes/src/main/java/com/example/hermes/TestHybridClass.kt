@file:Suppress("KotlinJniMissingFunction")

package com.example.hermes

import com.facebook.jni.HybridData

class TestHybridClass : NativeRunner {

    @Suppress("unused")
    private val hybridData: HybridData = initHybridData()

    override fun run(): String {
        return "HybridClass: ${nativeInvoke(this)}"
    }

    operator fun invoke(obj: Any): Any = nativeInvoke(obj)

    private external fun nativeInvoke(data: Any): Any

    private external fun initHybridData(): HybridData
}