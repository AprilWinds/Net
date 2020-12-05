#include "channel.h"

struct channel* channel_new(int fd, int events, event_read_callback rf, event_write_callback wf, void* data){
    struct channel* chan = maclloc(sizeof(struct channel));
    chan->data =data;
    chan->fd = fd;
    chan->eventWriteCallback = wf;
    chan->eventReadCallback  = rf;
    return  chan;
}


int channel_write_event_is_enabled(struct channel* channel){
    return channel->events&EVENT_WRITE;
}

// int channel_write_event_enabled(struct channel* channel){

// }

// int channel_write_event_disabled(struct channel* channel){

// }

