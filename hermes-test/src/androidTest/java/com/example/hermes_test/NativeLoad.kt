package com.example.hermes_test

import com.facebook.soloader.nativeloader.NativeLoader
import com.facebook.soloader.nativeloader.SystemDelegate

private var isLoad = false

fun loadNativeLib() {
    if (isLoad) return

    isLoad = true
    NativeLoader.init(SystemDelegate())
    NativeLoader.loadLibrary("hermes-test-android")
}