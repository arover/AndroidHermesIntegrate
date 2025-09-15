plugins {
    alias(libs.plugins.android.application)
    alias(libs.plugins.jetbrains.kotlin.android)
}

android {
    namespace = "com.example.hermesandroidintegrate"
    compileSdk = 34

    defaultConfig {
        applicationId = "com.example.hermesandroidintegrate"
        minSdk = 29
        targetSdk = 34
        versionCode = 1
        versionName = "1.0"

        testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"
        ndk {
            abiFilters += "arm64-v8a"//, "armeabi-v7a", "x86_64", "x86"  // Add more ABIs as needed
        }
    }

    buildTypes {
        release {
            isMinifyEnabled = false
            proguardFiles(getDefaultProguardFile("proguard-android-optimize.txt"), "proguard-rules.pro")
        }
    }

    packaging {
        jniLibs.pickFirsts += listOf(
            "**/libc++_shared.so",
            "**/libfbjni.so"
        )
    }
}

kotlin {
    jvmToolchain(17)
}

dependencies {

    implementation(project(":hermes"))

    implementation(libs.androidx.core.ktx)
    implementation(libs.androidx.appcompat)
    testImplementation(libs.junit)
    androidTestImplementation(libs.androidx.junit)
}