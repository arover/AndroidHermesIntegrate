package com.example.hermes

import org.junit.Assert
import org.junit.Test

class FbJniRunnerTest : BaseNativeTest() {


    @Test
    fun testJsFunctionCall() {
        val runner = FbJniRunner()
        Assert.assertEquals("hello 22", runner.testJsFunctionCall("22"))
    }

    @Test
    fun testJsFuncWithArg() {
        val runner = FbJniRunner()
        val res = runner.callFuncWithArgs(
            script = """
                function hello(...s) { return 'hello ' + s; }
            """.trimIndent(),
            func = "hello",
            args = arrayListOf("22", "a")
        )
        Assert.assertEquals("hello 22,a", res)
    }
}