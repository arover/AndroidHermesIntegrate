@file:Suppress("KotlinJniMissingFunction")

package com.example.hermes_test

class Runner {

    private val script = """
        function main() {
          myPrint("Hello World!", stringList);
        }
        main()
    """.trimIndent()

    fun run(): String {
        return "Simple Runner: ${eval(script)}"
    }

    private external fun eval(script: String): Int
}