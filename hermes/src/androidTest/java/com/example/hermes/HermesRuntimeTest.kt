package com.example.hermes

import org.junit.Assert.assertNotNull
import org.junit.Test

class HermesRuntimeTest : BaseNativeTest() {

    @Test
    fun initRuntime() {
        val rt = HermesRuntime()
        assertNotNull(rt.hybridData)
    }
}