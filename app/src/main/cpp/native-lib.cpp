#include <jni.h>
#include <string>
#include <android/log.h>

#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, "FFmpegApp", __VA_ARGS__);
extern "C"{
#include <libavcodec/avcodec.h>
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_vpaypay_ffmpegapp_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    hello += avcodec_configuration();
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_vpaypay_ffmpegapp_MainActivity_start(JNIEnv *env, jobject thiz) {
    // TODO: implement start()
}

extern "C"
JNIEXPORT void JNICALL
Java_com_vpaypay_ffmpegapp_MainActivity_stop(JNIEnv *env, jobject thiz) {
    // TODO: implement stop()
}


extern "C"
JNIEXPORT jboolean JNICALL
Java_com_vpaypay_ffmpegapp_MainActivity_open(JNIEnv *env, jobject thiz, jstring j_url,
                                             jobject handler) {

    const char *url = env->GetStringUTFChars(j_url, 0);
    FILE *fp = fopen(url, "rb");
    if(!fp)
    {
        LOGW("File %s open failed!", url);
    }
    else
    {
        LOGW("File %s open succeed!", url);
        fclose(fp);
    }
    env->ReleaseStringUTFChars(j_url, url);
    return false;
}