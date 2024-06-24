
int sd2psxman_ping(void *data);
int sd2psxman_get_status(void *data);
int sd2psxman_get_card(void *data);
int sd2psxman_set_card(void *data);
int sd2psxman_get_channel(void *data);
int sd2psxman_set_channel(void *data);
#ifdef RPC_SUPPORT
void sd2psxman_get_gameid(void *data);
#endif
int sd2psxman_set_gameid(void *data);
int sd2psxman_unmount_bootcard(void *data);
int sd2psxman_send_raw_payload(void *data);