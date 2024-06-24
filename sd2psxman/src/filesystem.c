#include "irx_imports.h"
#include "module_debug.h"
#include "../sd2psxman_common.h"
#include "sd2psxman_internal.h"
#include <errno.h>



int sd2psx_init(iop_device_t *F) {
    return 0; //inside here declare stuff like semaphores and crap used by the device
}
int sd2psx_deinit(iop_device_t *F) {
    return 0; //the opposite of init
}
int sd2psx_open(iop_file_t *F, const char *name, int flags) {
    return 0;
}
int sd2psx_close(iop_file_t *F) {
    return 0;
}
int sd2psx_read(iop_file_t *F, void *ptr, int size) {
    return 0;
}
int sd2psx_write(iop_file_t *F, void *ptr, int size) {
    return 0;
}
int sd2psx_lseek(iop_file_t *F, int pos, int mode) {
    return 0;
}

int sd2psx_ioctl(iop_file_t *fd, int cmd, void *data) {
	int ret;
    switch(cmd)
	{
        case SD2PSXMAN_PING:
            ret = sd2psxman_ping(data);
            break;
        case SD2PSXMAN_GET_STATUS:
            ret = sd2psxman_get_status(data);
            break;
        case SD2PSXMAN_GET_CARD:
            ret = sd2psxman_get_card(data);
            break;
        case SD2PSXMAN_SET_CARD:
            ret = sd2psxman_set_card(data);
            break;
        case SD2PSXMAN_GET_CHANNEL:
            ret = sd2psxman_get_channel(data);
            break;
        case SD2PSXMAN_SET_CHANNEL:
            ret = sd2psxman_set_channel(data);
            break;
        //case SD2PSXMAN_GET_GAMEID: // this CMD sends payload back to EE. to implement such thing. IOMANX IOCTL is required
        //    ret = sd2psxman_get_gameid(data);
        //    break;
        case SD2PSXMAN_SET_GAMEID:
            ret = sd2psxman_set_gameid(data);
            break;
        case SD2PSXMAN_UNMOUNT_BOOTCARD:
            ret = sd2psxman_unmount_bootcard(data);
            break;
        case SD2PSXMAN_SEND_RAW_PAYLOAD:
            ret = sd2psxman_send_raw_payload(data);
            break;
        default:
			ret = -EBADRQC; // invalid request code
            printf(MODNAME": Unknown ioctl (%d) called!\n", cmd);
    }
    return ret;
}

#define NOT_SUPPORTED_OP (void*)&not_supported_operation
static int not_supported_operation() {
    return -ENOTSUP;
}

static iop_device_ops_t ds2psx_fio_ops =
{
	&sd2psx_init, //init
	&sd2psx_deinit, //deinit
	NOT_SUPPORTED_OP, //format
	&sd2psx_open, //open
	&sd2psx_close, //close
	&sd2psx_read, //read
	&sd2psx_write, //write
	&sd2psx_lseek, //lseek
	&sd2psx_ioctl, //ioctl
	NOT_SUPPORTED_OP, //remove
	NOT_SUPPORTED_OP, //mkdir
	NOT_SUPPORTED_OP, //rmdir
	NOT_SUPPORTED_OP, //dopen
	NOT_SUPPORTED_OP, //dclose
	NOT_SUPPORTED_OP, //dread
	NOT_SUPPORTED_OP, //getstat
	NOT_SUPPORTED_OP, //chstat
};

static iop_device_t sd2psxdev =
{
	"smc",
	IOP_DT_FS,
	1,
	"Filesystem access sd2psx",
	&ds2psx_fio_ops, //fill this with an instance of iop_device_ops_t
};

int register_filesystem_access(void) {
    DPRINTF("Registering %s device\n", sd2psxdev.name);
    DelDrv(sd2psxdev.name);
    if (AddDrv(&sd2psxdev)!= 0) return 0;
    return 1;
    
}

void remove_filesystem_declaration(void) {
    DelDrv(sd2psxdev.name);
}