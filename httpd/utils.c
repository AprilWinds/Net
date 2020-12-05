#include "utils.h"
#include "log.h"

void assertInSameThread(struct event_loop* event_loop){
    if(event_loop->owner_thread_id != pthread_self()){
        LOG_ERR("not in the same thread");
        exit(-1);
    }
}

int isInSameThread(struct event_loop* event_loop){
    return event_loop->owner_thread_id ==pthread_self();
}