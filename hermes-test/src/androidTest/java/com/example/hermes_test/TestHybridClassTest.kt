package com.example.hermes_test

import org.junit.Assert.assertEquals
import org.junit.Test

class TestHybridClassTest {

    init {
        loadNativeLib()
    }

    private val hybridClass = TestHybridClass()

    @Test
    fun test_run() {
        assertEquals(hybridClass.invoke(hybridClass), hybridClass.toString())
    }
}