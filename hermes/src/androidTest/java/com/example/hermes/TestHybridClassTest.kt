package com.example.hermes

import org.junit.Assert.assertEquals
import org.junit.Test

class TestHybridClassTest : BaseNativeTest() {

    private val hybridClass = TestHybridClass()

    @Test
    fun test_run() {
        assertEquals(hybridClass.invoke(hybridClass), hybridClass.toString())
    }
}