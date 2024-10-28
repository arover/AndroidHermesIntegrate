package com.example.hermes

import org.junit.Assert
import org.junit.Test

class FbJniRunnerTest : BaseNativeTest() {


    @Test
    fun testJsFunctionCall() {
        val runner = FbJniRunner()
        Assert.assertEquals("hello 22", runner.testJsFunctionCall("22"))
    }
}