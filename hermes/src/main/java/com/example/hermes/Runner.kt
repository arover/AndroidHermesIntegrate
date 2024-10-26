@file:Suppress("KotlinJniMissingFunction")

package com.example.hermes

class Runner {

    private val script = """
        function main() {
          myPrint("Hello World!", stringList);
        }
        main()
    """.trimIndent()

    init {
        eval(script)
    }

    private external fun eval(script: String): Int
}