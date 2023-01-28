#include <jni.h>
#include <string>
#include <android/log.h>

#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, "FFmpegApp", __VA_ARGS__);

extern "C"{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

static double r2d(AVRational r)
{
    return r.num == 0 || r.den == 0 ? 0 : (double) r.num / (double) r.den;
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
extern "C"
JNIEXPORT void JNICALL
Java_com_vpaypay_ffmpegapp_MainActivity_init(JNIEnv *env, jobject thiz) {
    //初始化解封装
    av_register_all();
    //初始化网络
    avformat_network_init();
}


extern "C"
JNIEXPORT jboolean JNICALL
Java_com_vpaypay_ffmpegapp_MainActivity_avopen(JNIEnv *env, jobject thiz, jstring j_url,
                                               jobject handler) {
    int fps = 0;
    int width = 0;
    int height = 0;
    int videoStream = 0;
    int audioStream = 1;
    const char *url = env->GetStringUTFChars(j_url, 0);
    ///////////////////////////////////////////////
    //打开文件
    AVFormatContext *ic = NULL;
    int re = avformat_open_input(&ic, url, 0, 0);
    if(re != 0)
    {
        LOGW("avformat_open_input failed! %s", av_err2str(re));
        goto end;
    }
    LOGW("avformat_open_input %s success!", url);
    //获取流信息
    re = avformat_find_stream_info(ic, 0);
    if(re != 0){
        LOGW("avformat_find_stream_info failed!");
    }
    LOGW("duration=%lld nb_streams = %d", ic->duration, ic->nb_streams);
    for(int i=0;i<ic->nb_streams;i++)
    {
        AVStream *as = ic->streams[i];
        if(as->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            LOGW("视频数据");
            videoStream = i;
            fps = r2d(as->avg_frame_rate);
            LOGW("fps = %d, width=%d height=%d codec_id=%d pix_format=%d", fps,
                as->codecpar->width,
                as->codecpar->height,
                as->codecpar->codec_id,
                as->codecpar->format
            );
        }
        if(as->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)
        {
            LOGW("音频数据");
            audioStream = i;
            LOGW("sample_rate=%d channels=%d sample_format=%d",
                 as->codecpar->sample_rate,
                 as->codecpar->channels,
                 as->codecpar->format)
        }
    }
    //关闭上下文
    avformat_close_input(&ic);
    ///////////////////////////////////////////////
end:
    env->ReleaseStringUTFChars(j_url, url);
    return false;
}