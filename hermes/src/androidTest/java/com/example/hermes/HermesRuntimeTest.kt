package com.example.hermes

import org.junit.Assert.assertEquals
import org.junit.Assert.assertNotNull
import org.junit.Assert.assertNull
import org.junit.Assert.assertTrue
import org.junit.Before
import org.junit.Test

class HermesRuntimeTest : BaseNativeTest() {

    private lateinit var rt: HermesRuntime

    @Before
    fun each() {
        rt = HermesRuntime()
    }

    @Test
    fun initRuntime() {
        assertNotNull(rt.mHybridData)
    }

    @Test
    fun noEval() {
        val res = rt.eval("'hello'")
        assertNotNull(res)
        assertTrue(res is String)
    }

    @Test
    fun preloadScript() {
        val script = "function getWorld() { return 'world'; } "
        val status = rt.eval(script)
        assertNull("load script", status)

        val res = rt.callFunction("getWorld")
        assertEquals("get result", res, "world")
    }

    @Test
    fun callJsFunction() {
        rt.eval("function hello(s) { return 'hello ' + s; }")
        val s = rt.callFunction("hello", listOf("hermes"))
        assertEquals("call js function", "hello hermes", s)
    }

    @Test
    fun getJsProperty() {
        rt.eval("var a = { b: false, c: 'cc' };")
        val map = rt.getProperty("a") as Map<*, *>
        assertTrue("bool", map["b"] == false)
        assertTrue("string", map["c"] == "cc")
    }

    @Test
    fun testRegisterNativeFunction() {
        rt.registerFunction("hello", object : NativeFunction {
            override fun invoke(args: List<*>): Any {
                return "hello ${args.size}"
            }
        })
        rt.eval("var r = hello('a','b');")
        val r = rt.getProperty("r") as String
        assertEquals(r, "hello 2")
    }

    @Test
    fun registerMultiNativeFunction() {
        rt.registerFunction("hello", object : NativeFunction {
            override fun invoke(args: List<*>): Any {
                return "hello ${args.size}"
            }
        })
        rt.registerFunction("hello2", object : NativeFunction {
            override fun invoke(args: List<*>): Any {
                return "hello ${args.size}"
            }
        })
        rt.eval("var r = hello('a','b');")
        rt.eval("var r2 = hello2('a','b');")
        val r = rt.getProperty("r") as String
        assertEquals(r, "hello 2")
        val r2 = rt.getProperty("r2") as String
        assertEquals(r2, r)
    }
}