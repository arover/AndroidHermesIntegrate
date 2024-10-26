@file:Suppress("KotlinJniMissingFunction")

package com.example.hermes

class Runner : NativeRunner {

    private val script = """
        function main() {
          myPrint("Hello World!", stringList);
        }
        main()
    """.trimIndent()

    override fun run(): String {
        return "Simple Runner: ${eval(script)}"
    }

    private external fun eval(script: String): Int
}