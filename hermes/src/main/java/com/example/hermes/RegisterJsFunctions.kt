package com.example.hermes

class RegisterJsFunctions {

    var a = 0

    fun hello(str: String): String {
        return "Hello $str "
    }

    fun add(a: Int, b: Int): Int = a + b

    fun isTrue(): Boolean {
        return true
    }

    fun plus(i: Int): Int {
        a += i
        return a
    }

}