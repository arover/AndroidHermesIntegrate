package com.example.hermes

import com.facebook.soloader.nativeloader.NativeLoader
import com.facebook.soloader.nativeloader.SystemDelegate

object HermesAndroid {

    fun load() {
        NativeLoader.init(SystemDelegate())
        NativeLoader.loadLibrary("hermes-android")
    }
}