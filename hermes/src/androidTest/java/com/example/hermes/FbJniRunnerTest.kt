package com.example.hermes

import org.junit.Assert.assertEquals
import org.junit.Assert.assertTrue
import org.junit.Before
import org.junit.Test

class FbJniRunnerTest : BaseNativeTest() {

    private lateinit var runner: FbJniRunner

    @Before
    fun each() {
        runner = FbJniRunner()
    }

    @Test
    fun testJsFunctionCall() {
        assertEquals("hello 22", runner.testJsFunctionCall("22"))
    }

    @Test
    fun testJsFuncWithArg() {
        val res = runner.callFuncWithArgs(
            script = """
                function hello(...s) { return 'hello ' + s; }
            """.trimIndent(),
            func = "hello",
            args = arrayListOf("22", "a")
        )
        assertEquals("hello 22,a", res)
    }

    @Test
    fun testJsFunctionWithCallback() {
        var i = 0
        runner.evalWithCallback(
            script = "abc()",
            callbackName = "abc",
            cb = { i++ }
        )
        assertTrue(i == 1)
    }

    @Test
    fun testJsFunctionWithCallbackArg() {
        var i = ""
        runner.evalWithCallback(
            script = "abc('ccc')",
            callbackName = "abc",
            cb = {
                i = it as String
            }
        )
        assertEquals("ccc", i)
    }

    @Test
    fun testJsFunctionWithCallbackMultipleArg() {
        var called = false
        runner.evalWithCallback(
            script = "abc('ccc', false)",
            callbackName = "abc",
            cb = { arg ->
                called = true
                val args = arg as ArrayList<*>
                println("args $args")
                assertEquals("ccc", args[0])
                assertTrue(false == args[1])
            }
        )
        assertTrue(called)
    }

}