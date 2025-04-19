package com.example.hermesandroidintegrate

import android.annotation.SuppressLint
import android.os.Bundle
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import com.example.hermes.HermesRuntime
import com.example.hermes.NativeFunction

class MainActivity : AppCompatActivity() {

    private lateinit var textView: TextView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        setContentView(initView())

        val rt = HermesRuntime()

        rt.registerFunction("hello", object : NativeFunction {
            override fun invoke(args: List<*>): Any {
                return "hello from kotlin ${args.joinToString()}"
            }
        })
        rt.eval("var a = hello('a','b');")
        appendText(rt.getProperty("a").toString())

    }

    private fun initView() =
        TextView(this).apply {
            textSize = 20f
        }.also { textView = it }

    @SuppressLint("SetTextI18n")
    private fun appendText(t: String) = with(textView) {
        text = "$text\n$t"
    }

}