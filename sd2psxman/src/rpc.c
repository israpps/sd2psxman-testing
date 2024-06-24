#include "irx_imports.h"
#include "module_debug.h"
#include "../sd2psxman_common.h"
#include "sd2psxman_internal.h"

#ifndef RPC_SUPPORT
#error RPC_SUPPORT not enabled. rpc.c should not be compiling
#endif


//TODO: adjust rpc buffer size
u8 sd2psxman_rpc_buffer[268] __attribute__((__aligned__(4)));
int RPCThreadID;

extern McCommandHandler_t McCommandHandler;
static SifRpcDataQueue_t sd2psxman_queue;
static SifRpcServerData_t sd2psxman_server;

static void *sd2psxman_rpc_handler(unsigned int CMD, void *rpcBuffer, int size)
{
    if (McCommandHandler == NULL)
    {
        DPRINTF("ERROR: CANNOT SEND COMMANDS IF 'McCommandHandler' HAS NOT BEEN INTERCEPTED, PLEASE LOAD MCMAN BEFORE USING SD2PSXMAN FEATURES\n");
        return rpcBuffer;
    }
   
    switch(CMD)
	{
        case SD2PSXMAN_PING:
            sd2psxman_ping(rpcBuffer);
            break;
        case SD2PSXMAN_GET_STATUS:
            sd2psxman_get_status(rpcBuffer);
            break;
        case SD2PSXMAN_GET_CARD:
            sd2psxman_get_card(rpcBuffer);
            break;
        case SD2PSXMAN_SET_CARD:
            sd2psxman_set_card(rpcBuffer);
            break;
        case SD2PSXMAN_GET_CHANNEL:
            sd2psxman_get_channel(rpcBuffer);
            break;
        case SD2PSXMAN_SET_CHANNEL:
            sd2psxman_set_channel(rpcBuffer);
            break;
        case SD2PSXMAN_GET_GAMEID:
            sd2psxman_get_gameid(rpcBuffer);
            break;
        case SD2PSXMAN_SET_GAMEID:
            sd2psxman_set_gameid(rpcBuffer);
            break;
        case SD2PSXMAN_UNMOUNT_BOOTCARD:
            sd2psxman_unmount_bootcard(rpcBuffer);
            break;
        case SD2PSXMAN_SEND_RAW_PAYLOAD:
            sd2psxman_send_raw_payload(rpcBuffer);
            break;
        default:
            printf(MODNAME": Unknown CMD (%d) called!\n", CMD);
    }

    return rpcBuffer;
}

static void threadRpcFunction(void *arg)
{
	(void)arg;
	DPRINTF("RPC Thread Started\n");
    sceSifSetRpcQueue( &sd2psxman_queue , GetThreadId() );
	sceSifRegisterRpc( &sd2psxman_server, SD2PSXMAN_IRX, (void *)sd2psxman_rpc_handler,(u8 *)&sd2psxman_rpc_buffer,NULL,NULL, &sd2psxman_queue );
	sceSifRpcLoop( &sd2psxman_queue );
}

int sd2psxman_CreateRPCService() {

	iop_thread_t T;
	T.attr = TH_C;
	T.option = 0;
	T.thread = &threadRpcFunction;
	T.stacksize = 0x800;
	T.priority = 0x1e;

	DPRINTF("Creating RPC thread.\n");
	RPCThreadID = CreateThread(&T);
	if (RPCThreadID < 0)
	{
		DPRINTF("CreateThread failed. (%i)\n", RPCThreadID);
        return 0;
	}
#ifdef DEBUG
	int TSTAT = 
#endif
    StartThread(RPCThreadID, NULL);
    DPRINTF("Thread started (%d)\n", TSTAT);
    return 1;
}

int sd2psxman_StopRPCService() {
    DPRINTF("Stopping RPC Thread\n");
    return DeleteThread(RPCThreadID);
}
