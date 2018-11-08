/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class JoyCar */

#ifndef _Included_JoyCar
#define _Included_JoyCar
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     JoyCar
 * Method:    initializeWiringPi
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_JoyCar_initializeWiringPi
  (JNIEnv *, jobject);

/*
 * Class:     JoyCar
 * Method:    initializePCF8591
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_JoyCar_initializePCF8591
  (JNIEnv *, jobject);

/*
 * Class:     JoyCar
 * Method:    readUpDown
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_JoyCar_readUpDown
  (JNIEnv *, jobject);

/*
 * Class:     JoyCar
 * Method:    readLeftRight
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_JoyCar_readLeftRight
  (JNIEnv *, jobject);

/*
 * Class:     JoyCar
 * Method:    isButtonPressed
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_JoyCar_isButtonPressed
  (JNIEnv *, jobject);

/*
 * Class:     JoyCar
 * Method:    initializeServo
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_JoyCar_initializeServo
  (JNIEnv *, jobject);

/*
 * Class:     JoyCar
 * Method:    turnRight
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_JoyCar_turnRight
  (JNIEnv *, jobject);

/*
 * Class:     JoyCar
 * Method:    turnLeft
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_JoyCar_turnLeft
  (JNIEnv *, jobject);

/*
 * Class:     JoyCar
 * Method:    turnAtAngle
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_JoyCar_turnAtAngle
  (JNIEnv *, jobject, jint);

/*
 * Class:     JoyCar
 * Method:    initializeMotor
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_JoyCar_initializeMotor
  (JNIEnv *, jobject);

/*
 * Class:     JoyCar
 * Method:    runMotor
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_JoyCar_runMotor
  (JNIEnv *, jobject, jint);

#ifdef __cplusplus
}
#endif
#endif