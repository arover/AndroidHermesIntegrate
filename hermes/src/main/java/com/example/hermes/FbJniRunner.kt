@file:Suppress("KotlinJniMissingFunction")

package com.example.hermes

class FbJniRunner : NativeRunner {

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

    override fun run() = buildString {
        appendLine("FbJniRunner:")
        appendLine(nativeEval(script))
        appendLine(nativeEval(scriptError))
        appendLine(getStringHello())
    }

    val res: String get() = getStringHello()

    private external fun nativeEval(script: String): String
    private external fun getStringHello(): String
    external fun testJsFunctionCall(arg: String): String
    external fun callFuncWithArgs(script: String, func: String, args: ArrayList<Any>): String
}
