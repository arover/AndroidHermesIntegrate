package com.example.hermesandroidintegrate

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
    }

    external fun nativeEval(script: String): String
}
