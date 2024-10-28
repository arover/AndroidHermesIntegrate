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
        val script = """
            function getWorld() {
              return "world";
            }
        """.trimIndent()
        val status = rt.eval(script)
        assertNull("load script", status)

        val res = rt.eval("getWorld()")
        assertEquals("get result", res, "world")
    }

    @Test
    fun testReturnValueType() {
        rt.eval("function get(v) { return v; }")

        val i = rt.eval("get(1.3)")
        assertEquals("get double", 1.3, i)

        val b = rt.eval("get(false)")
        assertEquals("get bool", false, b)

        val s = rt.eval("get('abc')")
        assertEquals("get string", "abc", s)

        val strMap = rt.eval("get( {a: 'a_str'} )") as Map<*, *>
        assertTrue("get string map has key", strMap.contains("a"))
        assertEquals("get string map", "a_str", strMap["a"])

        val boolArr = rt.eval("get([false])") as ArrayList<*>
        assertEquals("get bool arr", boolArr[0], false)
    }
}