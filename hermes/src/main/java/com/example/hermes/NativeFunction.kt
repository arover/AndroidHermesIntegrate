package com.example.hermes

interface NativeFunction {
    fun invoke(args: List<*>): Any?
}