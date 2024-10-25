package com.example.hermesandroidintegrate

class Runner {

    private val script = """
        function main() {
          myPrint("Hello World!", stringList);
        }
        main()
    """.trimIndent()

    init {
        eval(script, "hello")
    }

    private external fun eval(script: String, name: String): Int


}