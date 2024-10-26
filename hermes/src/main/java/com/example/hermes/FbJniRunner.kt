@file:Suppress("KotlinJniMissingFunction")

package com.example.hermes

import android.util.Log

private const val TAG = "FbJniRunner"

class FbJniRunner {

    private val script = """
        function main() {
          myPrint("Hello World!", "from FbJniRunner");
          return "return value from js";
        }
        main()
    """.trimIndent()

    private val scriptError = """
        throw Error("js error");
    """.trimIndent()

    init {
        nativeEval(script).let {
            Log.d(TAG, "init: $it")
        }

        nativeEval(scriptError).let {
            Log.d(TAG, "init: $it")
        }

        getStringHello().let {
            Log.d(TAG, "get string from natve: $it")
        }
    }

    val res:String get() = getStringHello()

    private external fun nativeEval(script: String): String
    private external fun getStringHello(): String
}
