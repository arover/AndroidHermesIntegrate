package com.example.hermes

interface NativeRunner {
    fun run(): String
}

object HermesPlayground {

    private val runners = listOf(
        Runner(),
        FbJniRunner(),
        TestHybridClass(),
    )

    fun run() = buildString {
        runners.forEach {
            appendLine(it.run())
            appendLine()
        }
    }
}