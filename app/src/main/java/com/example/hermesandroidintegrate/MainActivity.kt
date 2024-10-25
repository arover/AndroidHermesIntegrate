package com.example.hermesandroidintegrate

import android.os.Bundle
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        setContentView(initView())
        Runner()
        FbJniRunner()
    }

    private fun initView() =
        TextView(this).apply {
            text = stringFromJNI()
            textSize = 50f
        }

    /**
     * A native method that is implemented by the 'hermesandroidintegrate' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    companion object {
        // Used to load the 'hermesandroidintegrate' library on application startup.
        init {
            System.loadLibrary("hermesandroidintegrate")
        }
    }
}