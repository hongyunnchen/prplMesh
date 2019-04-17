/*
 * INTEL CONFIDENTIAL
 * Copyright 2016 Intel Corporation All Rights Reserved.
 *
 * The source code contained or described herein and all documents related to
 * the source code ("Material") are owned by Intel Corporation or its
 * suppliers or licensors.  Title to the Material remains with Intel
 * Corporation or its suppliers and licensors.  The Material contains trade
 * secrets and proprietary and confidential information of Intel or its
 * suppliers and licensors.  The Material is protected by worldwide copyright
 * and trade secret laws and treaty provisions. No part of the Material may
 * be used, copied, reproduced, modified, published, uploaded, posted,
 * transmitted, distributed, or disclosed in any way without Intel's prior
 * express written permission.
 *
 * No license under any patent, copyright, trade secret or other intellectual
 * property right is granted to or conferred upon you by disclosure or
 * delivery of the Materials,  either expressly, by implication, inducement,
 * estoppel or otherwise.  Any license under such intellectual property
 * rights must be express and approved by Intel in writing.
 */

#include "bwl_utils.h"

#include <wlioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/types.h>
 
int bwl_wl_ioctl(char *name, int cmd, void *buf, int len)
{
    struct ifreq ifr;
    wl_ioctl_t ioc;
    int ret = 0;
    int s;

    /*
    * open socket to kernel
    */
    if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        return errno;
    }

    /*
    * do it
    */
    ioc.cmd = cmd;
    ioc.buf = buf;
    ioc.len = len;
    strncpy(ifr.ifr_name, name, IFNAMSIZ);
    ifr.ifr_data = (caddr_t) & ioc;
    if ((ret = ioctl(s, SIOCDEVPRIVATE, &ifr)) < 0) {
        if (cmd != WLC_GET_MAGIC) {
            perror(ifr.ifr_name);
        }
    }

    /*
    * cleanup
    */
    close(s);
    return ret;
} 