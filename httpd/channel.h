#ifndef CHANNEL_H
#define CHANNEL_H

#include "common.h"
#include "event_loop.h"
#include "buffer.h"

#define EVENT_TIMEOUT 0x01
#define EVENT_READ    0x02
#define EVENT_WRITE   0x03
#define EVENT_SIGNAL  0x08


typedef int (*event_read_callback) (void* data);
typedef int (*event_write_callback) (void* data);

struct channel{
    int fd;
    int events;
    event_read_callback eventReadCallback;
    event_write_callback eventWriteCallback;
    void *data;
};

struct channel* channel_new(int fd, int events, event_read_callback rf, event_write_callback wf, void* data);

int channel_write_event_is_enabled(struct channel* channel);
int channel_write_event_enabled(struct channel* channel);
int channel_write_event_disabled(struct channel* channel);




#endif