package com.example.hermesandroidintegrate

import android.app.Application
import com.example.hermes.HermesAndroid

class App : Application() {

    override fun onCreate() {
        super.onCreate()
        HermesAndroid.load()
    }
}