package com.example.hermesandroidintegrate

import android.annotation.SuppressLint
import android.os.Bundle
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import com.example.hermes.HermesAndroid
import com.example.hermes.HermesPlayground

class MainActivity : AppCompatActivity() {

    private lateinit var textView: TextView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        setContentView(initView())
        appendText(HermesPlayground.run())
    }

    private fun initView() =
        TextView(this).apply {
            textSize = 20f
        }.also { textView = it }

    @SuppressLint("SetTextI18n")
    private fun appendText(t: String) = with(textView) {
        text = "$text\n$t"
    }

    companion object {
        init {
            HermesAndroid.load()
        }
    }
}