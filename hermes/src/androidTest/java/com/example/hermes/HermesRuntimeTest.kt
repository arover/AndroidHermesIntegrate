package com.example.hermes

import org.junit.Assert.assertEquals
import org.junit.Assert.assertNotNull
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
        assertNotNull("load script", status)

        val res = rt.eval("getWorld()")
        assertEquals("get result", res, "world")
    }
}