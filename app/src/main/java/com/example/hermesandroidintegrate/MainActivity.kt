package com.example.hermesandroidintegrate

import android.annotation.SuppressLint
import android.os.Bundle
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import com.example.hermes.FbJniRunner
import com.example.hermes.Runner

class MainActivity : AppCompatActivity() {

    private lateinit var textView: TextView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        setContentView(initView())
        Runner()
        val jniRun = FbJniRunner()
        appendText(jniRun.res)
    }

    private fun initView() =
        TextView(this).apply {
            textSize = 50f
        }.also { textView = it }

    @SuppressLint("SetTextI18n")
    private fun appendText(t: String) = with(textView) {
        text = "$text\n$t"
    }

    companion object {
        // Used to load the 'hermesandroidintegrate' library on application startup.
        init {
            System.loadLibrary("hermesandroidintegrate")
        }
    }
}