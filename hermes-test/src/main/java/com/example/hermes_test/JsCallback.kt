package com.example.hermes_test

/**
 * A JsCallback passing from Kotlin to Native, Javascript will
 * callback [call] when they needed
 */
fun interface JsCallback {

    /**
     * This will be called from native from jni,
     * @param args could be any type, if javascript passing multiple parameters,
     * it will be packed into a [ArrayList]
     */
    fun call(args: Any?)
}