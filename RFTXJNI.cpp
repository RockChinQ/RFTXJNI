#include "RFTXJNI.h"
#include <conio.h>
#include <iostream>
using namespace std;

jstring charTojstring(JNIEnv* env, const char* pat)
{
	//定义java String类 strClass
	jclass strClass = (env)->FindClass("Ljava/lang/String;");
	//获取String(byte[],String)的构造器,用于将本地byte[]数组转换为一个新String
	jmethodID ctorID = (env)->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
	//建立byte数组
	jbyteArray bytes = (env)->NewByteArray(strlen(pat));
	//将char* 转换为byte数组
	(env)->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte*)pat);
	// 设置String, 保存语言类型,用于byte数组转换至String时的参数
	jstring encoding = (env)->NewStringUTF("GB2312");
	//将byte数组转换为java String,并输出
	return (jstring)(env)->NewObject(strClass, ctorID, bytes, encoding);
}
static bool debugMode = false;


JNIEXPORT void JNICALL Java_jni_JniInterface_setDebugMode
(JNIEnv *env, jclass cls, jboolean debug) {
	debugMode = debug;
}

JNIEXPORT jstring JNICALL Java_jni_JniInterface_getstr
(JNIEnv* env, jclass cls) {
	char b[3];
	b[0] = _getch();
	if(debugMode)
		printf("%d ", b[0]);
	if (b[0] > 127||b[0]<0) {
		b[1] = _getch();
		if (debugMode)
		{
			printf("%d", b[1]);
		}
		b[2] = '\0';
	}
	else {
		b[1] = '\0';
	}

	return charTojstring(env, b);

}
