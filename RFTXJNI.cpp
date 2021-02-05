#include "RFTXJNI.h"
#include <conio.h>
#include <iostream>
using namespace std;

jstring charTojstring(JNIEnv* env, const char* pat)
{
	//����java String�� strClass
	jclass strClass = (env)->FindClass("Ljava/lang/String;");
	//��ȡString(byte[],String)�Ĺ�����,���ڽ�����byte[]����ת��Ϊһ����String
	jmethodID ctorID = (env)->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
	//����byte����
	jbyteArray bytes = (env)->NewByteArray(strlen(pat));
	//��char* ת��Ϊbyte����
	(env)->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte*)pat);
	// ����String, ������������,����byte����ת����Stringʱ�Ĳ���
	jstring encoding = (env)->NewStringUTF("GB2312");
	//��byte����ת��Ϊjava String,�����
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
