package com.example.hermes

class NativeLib {

    /**
     * A native method that is implemented by the 'hermes' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    companion object {
        // Used to load the 'hermes' library on application startup.
        init {
            System.loadLibrary("hermes")
        }
    }
}