/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class org_coolreader_crengine_Engine */

#ifndef _Included_org_coolreader_crengine_Engine
#define _Included_org_coolreader_crengine_Engine
#ifdef __cplusplus
extern "C" {
#endif
#undef org_coolreader_crengine_Engine_LOG_ENGINE_TASKS
#define org_coolreader_crengine_Engine_LOG_ENGINE_TASKS 0L
#undef org_coolreader_crengine_Engine_HYPH_NONE
#define org_coolreader_crengine_Engine_HYPH_NONE 0L
#undef org_coolreader_crengine_Engine_HYPH_ALGO
#define org_coolreader_crengine_Engine_HYPH_ALGO 1L
#undef org_coolreader_crengine_Engine_HYPH_DICT
#define org_coolreader_crengine_Engine_HYPH_DICT 2L
#undef org_coolreader_crengine_Engine_HYPH_BOOK
#define org_coolreader_crengine_Engine_HYPH_BOOK 0L
#undef org_coolreader_crengine_Engine_CACHE_DIR_SIZE
#define org_coolreader_crengine_Engine_CACHE_DIR_SIZE 32000000L
#undef org_coolreader_crengine_Engine_BLOCK_RENDERING_FLAGS_LEGACY
#define org_coolreader_crengine_Engine_BLOCK_RENDERING_FLAGS_LEGACY 0L
#undef org_coolreader_crengine_Engine_BLOCK_RENDERING_FLAGS_FLAT
#define org_coolreader_crengine_Engine_BLOCK_RENDERING_FLAGS_FLAT 16977969L
#undef org_coolreader_crengine_Engine_BLOCK_RENDERING_FLAGS_BOOK
#define org_coolreader_crengine_Engine_BLOCK_RENDERING_FLAGS_BOOK 20402481L
#undef org_coolreader_crengine_Engine_BLOCK_RENDERING_FLAGS_WEB
#define org_coolreader_crengine_Engine_BLOCK_RENDERING_FLAGS_WEB 2147483647L
/*
 * Class:     org_coolreader_crengine_Engine
 * Method:    initInternal
 * Signature: ([Ljava/lang/String;I)Z
 */
JNIEXPORT jboolean JNICALL Java_org_coolreader_crengine_Engine_initInternal
  (JNIEnv *, jclass, jobjectArray, jint);

/*
 * Class:     org_coolreader_crengine_Engine
 * Method:    initDictionaries
 * Signature: ([Lorg/coolreader/crengine/Engine/HyphDict;)Z
 */
JNIEXPORT jboolean JNICALL Java_org_coolreader_crengine_Engine_initDictionaries
  (JNIEnv *, jclass, jobjectArray);

/*
 * Class:     org_coolreader_crengine_Engine
 * Method:    uninitInternal
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_coolreader_crengine_Engine_uninitInternal
  (JNIEnv *, jclass);

/*
 * Class:     org_coolreader_crengine_Engine
 * Method:    getFontFaceListInternal
 * Signature: ()[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_org_coolreader_crengine_Engine_getFontFaceListInternal
  (JNIEnv *, jclass);

/*
 * Class:     org_coolreader_crengine_Engine
 * Method:    getFontFileNameListInternal
 * Signature: ()[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_org_coolreader_crengine_Engine_getFontFileNameListInternal
  (JNIEnv *, jclass);

/*
 * Class:     org_coolreader_crengine_Engine
 * Method:    getArchiveItemsInternal
 * Signature: (Ljava/lang/String;)[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_org_coolreader_crengine_Engine_getArchiveItemsInternal
  (JNIEnv *, jclass, jstring);

/*
 * Class:     org_coolreader_crengine_Engine
 * Method:    setKeyBacklightInternal
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_org_coolreader_crengine_Engine_setKeyBacklightInternal
  (JNIEnv *, jclass, jint);

/*
 * Class:     org_coolreader_crengine_Engine
 * Method:    setCacheDirectoryInternal
 * Signature: (Ljava/lang/String;I)Z
 */
JNIEXPORT jboolean JNICALL Java_org_coolreader_crengine_Engine_setCacheDirectoryInternal
  (JNIEnv *, jclass, jstring, jint);

/*
 * Class:     org_coolreader_crengine_Engine
 * Method:    scanBookPropertiesInternal
 * Signature: (Lorg/coolreader/crengine/FileInfo;)Z
 */
JNIEXPORT jboolean JNICALL Java_org_coolreader_crengine_Engine_scanBookPropertiesInternal
  (JNIEnv *, jclass, jobject);

/*
 * Class:     org_coolreader_crengine_Engine
 * Method:    scanBookCoverInternal
 * Signature: (Ljava/lang/String;)[B
 */
JNIEXPORT jbyteArray JNICALL Java_org_coolreader_crengine_Engine_scanBookCoverInternal
  (JNIEnv *, jclass, jstring);

/*
 * Class:     org_coolreader_crengine_Engine
 * Method:    drawBookCoverInternal
 * Signature: (Landroid/graphics/Bitmap;[BLjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;II)V
 */
JNIEXPORT void JNICALL Java_org_coolreader_crengine_Engine_drawBookCoverInternal
  (JNIEnv *, jclass, jobject, jbyteArray, jstring, jstring, jstring, jstring, jint, jint);

/*
 * Class:     org_coolreader_crengine_Engine
 * Method:    suspendLongOperationInternal
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_coolreader_crengine_Engine_suspendLongOperationInternal
  (JNIEnv *, jclass);

/*
 * Class:     org_coolreader_crengine_Engine
 * Method:    haveFcLangCodeInternal
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_org_coolreader_crengine_Engine_haveFcLangCodeInternal
  (JNIEnv *, jclass, jstring);

/*
 * Class:     org_coolreader_crengine_Engine
 * Method:    checkFontLanguageCompatibilityInternal
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_org_coolreader_crengine_Engine_checkFontLanguageCompatibilityInternal
  (JNIEnv *, jclass, jstring, jstring);

/*
 * Class:     org_coolreader_crengine_Engine
 * Method:    listFilesInternal
 * Signature: (Ljava/io/File;)[Ljava/io/File;
 */
JNIEXPORT jobjectArray JNICALL Java_org_coolreader_crengine_Engine_listFilesInternal
  (JNIEnv *, jclass, jobject);

/*
 * Class:     org_coolreader_crengine_Engine
 * Method:    getDomVersionCurrent
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_coolreader_crengine_Engine_getDomVersionCurrent
  (JNIEnv *, jclass);

/*
 * Class:     org_coolreader_crengine_Engine
 * Method:    isLink
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_coolreader_crengine_Engine_isLink
  (JNIEnv *, jclass, jstring);

#ifdef __cplusplus
}
#endif
#endif
