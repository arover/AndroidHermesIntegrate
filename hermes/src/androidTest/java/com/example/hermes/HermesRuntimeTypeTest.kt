package com.example.hermes

import org.junit.Assert.assertEquals
import org.junit.Assert.assertTrue
import org.junit.Before
import org.junit.Test
import kotlin.math.abs

class HermesRuntimeTypeTest : BaseNativeTest() {

    private lateinit var rt: HermesRuntime

    @Before
    fun each() {
        rt = HermesRuntime()
        rt.eval("function get(v) { return v; }")
    }

    @Test
    fun getDouble() {
        val i = rt.callFunction("get", listOf(1.3)) as Double
        assertTrue(abs(1.3 - i) < 0.001)
    }

    @Test
    fun getBool() {
        val b = rt.callFunction("get", listOf(false)) as Boolean
        assertEquals(false, b)
    }

    @Test
    fun getString() {
        val s = rt.callFunction("get", listOf("abc")) as String
        assertEquals("get string", "abc", s)
    }

    @Test
    fun getMap() {
        val strMap = rt.callFunction("get", listOf(mapOf("a" to "a_str"))) as Map<*, *>
        assertTrue("get string map has key", strMap.contains("a"))
        assertEquals("get string map", "a_str", strMap["a"])
    }

    @Test
    fun getBoolArray() {
        val boolArr = rt.callFunction("get", listOf(listOf(false))) as ArrayList<*>
        assertEquals("get bool arr", boolArr[0], false)
    }
}