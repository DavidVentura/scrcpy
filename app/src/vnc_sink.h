#ifndef SC_VNC_SINK_H
#define SC_VNC_SINK_H

#include "common.h"

#include <libswscale/swscale.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <rfb/rfb.h>

#include "coords.h"
#include "control_msg.h"
#include "controller.h"
#include "trait/frame_sink.h"
#include "frame_buffer.h"
#include "util/tick.h"

struct plugin {
    char name[4];
    bool needs_video_decoder;
    bool sink_initialized;
    bool should_be_init;
    //struct sc_delay_buffer delay_buffer;
    void* plugindata;
    void* frame_source;

    struct sc_frame_sink frame_sink; // frame sink trait

    bool (*init)(const void* plugindata);
    bool (*destroy)(const void* plugindata);
};

struct sc_vnc_sink {
    char* vncservername;
    struct plugin *plugin;
    struct sc_controller *controller;

    struct SwsContext * ctx;
    rfbScreenInfoPtr screen;
    uint16_t scrWidth;
    uint16_t scrHeight;
    uint8_t bpp;

    bool was_down;
};


bool
sc_vnc_sink_init(struct sc_vnc_sink *vs);

void
sc_vnc_sink_destroy(struct sc_vnc_sink *vs);

void
ptr_add_event(int buttonMask, int x, int y, rfbClientPtr cl);
#endif
