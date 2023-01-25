#include <jni.h>
#include <string>
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