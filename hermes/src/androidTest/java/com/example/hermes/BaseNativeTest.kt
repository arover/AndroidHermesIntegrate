package com.example.hermes

import org.junit.BeforeClass

open class BaseNativeTest {


    companion object {

        private var initialized = false

        @JvmStatic
        @BeforeClass
        fun setupTest() {
            if (initialized) return

            initialized = true
            HermesAndroid.load()
        }
    }
}