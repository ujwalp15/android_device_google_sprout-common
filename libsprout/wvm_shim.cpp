/*
 * Copyright (C) 2016 The CyanogenMod Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

 #define LOG_TAG "libshim"

 #include <cutils/log.h>
 #include <stdint.h>
 #include <stdlib.h>
 #include <string.h>
 #include <libexif/exif-entry.h>
 #include <media/stagefright/MediaBufferGroup.h>
 #include <media/IMediaSource.h>
 #include <media/stagefright/MediaSource.h>

 extern "C" {

 /* liblog */
 extern int __hi_log_print(){ return 0; }
 extern int __android_janklog_print() { return 0; }
 extern int __android_logPower_print() { return 0; }
 extern int __android_log_exception_write() { return 0; }

 /* libexif */
 extern void exif_entry_gps_initialize(ExifEntry * e, ExifTag tag)
 {
     ALOGD("ExifTag = %d", (int)tag);
     exif_entry_initialize(e,tag);
 }

 /* libcutils */
 extern void atrace_async_begin_body_HwCam(const char* name,int32_t cookie) {}

 /* libaudio_route */
 extern int pop_seq_init(){return 0;};
 extern int pop_seq_set(){return 0;};

 /* wpa_supplicant_hisi */
 extern int __android_log_vprint(int prio, const char *tag, const char *fmt, va_list ap) {return 0;}
 extern int __chr_printLog(){return 0;}

 /* libwvm */

 extern int _ZN7android16MediaBufferGroupC1Ej(unsigned int);
 extern int _ZN7android16MediaBufferGroupC1Ev() {
     return _ZN7android16MediaBufferGroupC1Ej(0);
 }

 extern int _ZN7android16MediaBufferGroup14acquire_bufferEPPNS_11MediaBufferEb(void *obj,android::MediaBuffer **out,
 								bool nonBlocking, size_t requestedSize) {
     android::MediaBufferGroup *mbg = static_cast<android::MediaBufferGroup *>(obj);
     return mbg->acquire_buffer(out,nonBlocking,requestedSize);

 }

 extern void _ZNK7android11MediaSource11ReadOptions9getSeekToEPxPNS1_8SeekModeE(void * obj, int64_t time_us, android::MediaSource::ReadOptions::SeekMode mode) {
     android::IMediaSource::ReadOptions *rop = static_cast<android::IMediaSource::ReadOptions *>(obj);
     rop->setSeekTo(time_us, mode);
 }

 extern bool _ZNK7android11MediaSource11ReadOptions14getNonBlockingEv(void * obj) {
     android::IMediaSource::ReadOptions *rop = static_cast<android::IMediaSource::ReadOptions *>(obj);
     return rop->getNonBlocking();
 }

 }
