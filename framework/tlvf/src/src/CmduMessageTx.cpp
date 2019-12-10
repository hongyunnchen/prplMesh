/* SPDX-License-Identifier: BSD-2-Clause-Patent
 *
 * Copyright (c) 2016-2019 Intel Corporation
 *
 * This code is subject to the terms of the BSD+Patent license.
 * See LICENSE file for more details.
 */

#include <tlvf/CmduMessageTx.h>
#include <tlvf/ieee_1905_1/tlvEndOfMessage.h>

#include <tlvf/tlvflogging.h>

using namespace ieee1905_1;

CmduMessageTx::CmduMessageTx(uint8_t *buff, size_t buff_len) : CmduMessage(buff, buff_len) {}

CmduMessageTx::~CmduMessageTx() {}

std::shared_ptr<cCmduHeader> CmduMessageTx::create(uint16_t id, eMessageType message_type)
{
    // we set swap = true so that each class will have swap = true,
    // but since parse = false, no swap will be done till we explicitely
    // call tlvs.swap() in Finalize(), and there, we do swapping based on
    // the caller swap_needed parameter
    tlvs.reset(false, false);
    header = nullptr;
    auto cmduhdr = tlvs.addClass<cCmduHeader>();
    if (!cmduhdr)
        return nullptr;

    cmduhdr->message_type() = message_type;
    cmduhdr->message_id()   = id;
    return cmduhdr;
}

std::shared_ptr<cCmduHeader> CmduMessageTx::load()
{
    LOG(DEBUG)<<"CmduMessageTx::load";
    tlvs.reset(true, false);
    return addClass<cCmduHeader>();
}

std::shared_ptr<tlvVendorSpecific> CmduMessageTx::add_vs_tlv(tlvVendorSpecific::eVendorOUI voui)
{
    if (!getCmduHeader())
        return nullptr;

    auto tlv = addClass<tlvVendorSpecific>();
    if (!tlv)
        return nullptr;

    //set vendor specific oui
    tlv->vendor_oui() = (uint32_t)voui;

    return tlv;
}

bool CmduMessageTx::finalize(bool swap_needed)
{
    return tlvs.finalize(swap_needed);
}
