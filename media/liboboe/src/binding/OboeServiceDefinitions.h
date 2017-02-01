/*
 * Copyright (C) 2016 The Android Open Source Project
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

#ifndef BINDING_OBOESERVICEDEFINITIONS_H
#define BINDING_OBOESERVICEDEFINITIONS_H

#include <stdint.h>
#include <utils/RefBase.h>
#include <binder/TextOutput.h>
#include <binder/IInterface.h>

#include <oboe/OboeAudio.h>

using android::NO_ERROR;
using android::IBinder;

namespace android {

enum oboe_commands_t {
    OPEN_STREAM = IBinder::FIRST_CALL_TRANSACTION,
    CLOSE_STREAM,
    GET_STREAM_DESCRIPTION,
    START_STREAM,
    PAUSE_STREAM,
    FLUSH_STREAM,
    REGISTER_AUDIO_THREAD,
    UNREGISTER_AUDIO_THREAD
};

} // namespace android

namespace oboe {

enum oboe_commands_t {
    OPEN_STREAM = IBinder::FIRST_CALL_TRANSACTION,
    CLOSE_STREAM,
    GET_STREAM_DESCRIPTION,
    START_STREAM,
    PAUSE_STREAM,
    FLUSH_STREAM,
    REGISTER_AUDIO_THREAD,
    UNREGISTER_AUDIO_THREAD
};

// TODO Expand this to include all the open parameters.
typedef struct OboeServiceStreamInfo_s {
    int32_t             deviceId;
    int32_t             samplesPerFrame;  // number of channels
    oboe_sample_rate_t  sampleRate;
    oboe_audio_format_t audioFormat;
} OboeServiceStreamInfo;

// This must be a fixed width so it can be in shared memory.
enum RingbufferFlags : uint32_t {
    NONE = 0,
    RATE_ISOCHRONOUS = 0x0001,
    RATE_ASYNCHRONOUS = 0x0002,
    COHERENCY_DMA = 0x0004,
    COHERENCY_ACQUIRE_RELEASE = 0x0008,
    COHERENCY_AUTO = 0x0010,
};

// This is not passed through Binder.
// Client side code will convert Binder data and fill this descriptor.
typedef struct RingBufferDescriptor_s {
    uint8_t* dataAddress;       // offset from read or write block
    int64_t* writeCounterAddress;
    int64_t* readCounterAddress;
    int32_t  bytesPerFrame;     // index is in frames
    int32_t  framesPerBurst;    // for ISOCHRONOUS queues
    int32_t  capacityInFrames;  // zero if unused
    RingbufferFlags flags;
} RingBufferDescriptor;

// This is not passed through Binder.
// Client side code will convert Binder data and fill this descriptor.
typedef struct EndpointDescriptor_s {
    // Set capacityInFrames to zero if Queue is unused.
    RingBufferDescriptor upMessageQueueDescriptor;   // server to client
    RingBufferDescriptor downMessageQueueDescriptor; // client to server
    RingBufferDescriptor upDataQueueDescriptor;      // eg. record
    RingBufferDescriptor downDataQueueDescriptor;    // eg. playback
} EndpointDescriptor;

} // namespace oboe

#endif //BINDING_OBOESERVICEDEFINITIONS_H