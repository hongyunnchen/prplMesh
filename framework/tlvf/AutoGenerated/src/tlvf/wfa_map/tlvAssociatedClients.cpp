///////////////////////////////////////
// AUTO GENERATED FILE - DO NOT EDIT //
///////////////////////////////////////

/* SPDX-License-Identifier: BSD-2-Clause-Patent
 *
 * Copyright (c) 2016-2019 Intel Corporation
 *
 * This code is subject to the terms of the BSD+Patent license.
 * See LICENSE file for more details.
 */

#include <tlvf/wfa_map/tlvAssociatedClients.h>
#include <tlvf/tlvflogging.h>

using namespace wfa_map;

tlvAssociatedClients::tlvAssociatedClients(uint8_t* buff, size_t buff_len, bool parse, bool swap_needed) :
    BaseClass(buff, buff_len, parse, swap_needed) {
    m_init_succeeded = init();
}
tlvAssociatedClients::tlvAssociatedClients(std::shared_ptr<BaseClass> base, bool parse, bool swap_needed) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse, swap_needed){
    m_init_succeeded = init();
}
tlvAssociatedClients::~tlvAssociatedClients() {
}
const eTlvTypeMap& tlvAssociatedClients::type() {
    return (const eTlvTypeMap&)(*m_type);
}

const uint16_t& tlvAssociatedClients::length() {
    return (const uint16_t&)(*m_length);
}

uint8_t& tlvAssociatedClients::bss_list_length() {
    return (uint8_t&)(*m_bss_list_length);
}

std::tuple<bool, tlvAssociatedClients::sBssInfo&> tlvAssociatedClients::bss_list(size_t idx) {
    bool ret_success = ( (m_bss_list_idx__ > 0) && (m_bss_list_idx__ > idx) );
    size_t ret_idx = ret_success ? idx : 0;
    if (!ret_success) {
        TLVF_LOG(ERROR) << "Requested index is greater than the number of available entries";
    }
    return std::forward_as_tuple(ret_success, m_bss_list[ret_idx]);
}

bool tlvAssociatedClients::alloc_bss_list(size_t count) {
    if (m_lock_order_counter__ > 0) {;
        TLVF_LOG(ERROR) << "Out of order allocation for variable length list bss_list, abort!";
        return false;
    }
    if (count == 0) {
        TLVF_LOG(WARNING) << "can't allocate 0 bytes";
        return false;
    }
    size_t len = sizeof(sBssInfo) * count;
    if(getBuffRemainingBytes() < len )  {
        TLVF_LOG(ERROR) << "Not enough available space on buffer - can't allocate";
        return false;
    }
    m_lock_order_counter__ = 0;
    uint8_t *src = (uint8_t *)&m_bss_list[*m_bss_list_length];
    uint8_t *dst = src + len;
    if (!m_parse__) {
        size_t move_length = getBuffRemainingBytes(src) - len;
        std::copy_n(src, move_length, dst);
    }
    m_bss_list_idx__ += count;
    *m_bss_list_length += count;
    if (!buffPtrIncrementSafe(len)) { return false; }
    if(m_length){ (*m_length) += len; }
    if (!m_parse__) { 
        for (size_t i = m_bss_list_idx__ - count; i < m_bss_list_idx__; i++) { m_bss_list[i].struct_init(); }
    }
    return true;
}

void tlvAssociatedClients::class_swap()
{
    tlvf_swap(16, reinterpret_cast<uint8_t*>(m_length));
    for (size_t i = 0; i < (size_t)*m_bss_list_length; i++){
        m_bss_list[i].struct_swap();
    }
}

size_t tlvAssociatedClients::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(eTlvTypeMap); // type
    class_size += sizeof(uint16_t); // length
    class_size += sizeof(uint8_t); // bss_list_length
    return class_size;
}

bool tlvAssociatedClients::init()
{
    if (getBuffRemainingBytes() < kMinimumLength) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_type = (eTlvTypeMap*)m_buff_ptr__;
    if (!m_parse__) *m_type = eTlvTypeMap::TLV_ASSOCIATED_CLIENTS;
    if (!buffPtrIncrementSafe(sizeof(eTlvTypeMap))) { return false; }
    m_length = (uint16_t*)m_buff_ptr__;
    if (!m_parse__) *m_length = 0;
    if (!buffPtrIncrementSafe(sizeof(uint16_t))) { return false; }
    m_bss_list_length = (uint8_t*)m_buff_ptr__;
    if (!m_parse__) *m_bss_list_length = 0;
    if (!buffPtrIncrementSafe(sizeof(uint8_t))) { return false; }
    if(m_length && !m_parse__){ (*m_length) += sizeof(uint8_t); }
    m_bss_list = (sBssInfo*)m_buff_ptr__;
    uint8_t bss_list_length = *m_bss_list_length;
    m_bss_list_idx__ = bss_list_length;
    if (!buffPtrIncrementSafe(sizeof(sBssInfo)*(bss_list_length))) { return false; }
    if (m_parse__ && m_swap__) { class_swap(); }
    if (m_parse__) {
        if (*m_type != eTlvTypeMap::TLV_ASSOCIATED_CLIENTS) {
            TLVF_LOG(ERROR) << "TLV type mismatch. Expected value: " << int(eTlvTypeMap::TLV_ASSOCIATED_CLIENTS) << ", received value: " << int(*m_type);
            return false;
        }
    }
    return true;
}

sClientInfo::sClientInfo(uint8_t* buff, size_t buff_len, bool parse, bool swap_needed) :
    BaseClass(buff, buff_len, parse, swap_needed) {
    m_init_succeeded = init();
}
sClientInfo::sClientInfo(std::shared_ptr<BaseClass> base, bool parse, bool swap_needed) :
BaseClass(base->getBuffPtr(), base->getBuffRemainingBytes(), parse, swap_needed){
    m_init_succeeded = init();
}
sClientInfo::~sClientInfo() {
}
sMacAddr& sClientInfo::mac() {
    return (sMacAddr&)(*m_mac);
}

uint16_t& sClientInfo::time_since_last_association_sec() {
    return (uint16_t&)(*m_time_since_last_association_sec);
}

void sClientInfo::class_swap()
{
    m_mac->struct_swap();
    tlvf_swap(16, reinterpret_cast<uint8_t*>(m_time_since_last_association_sec));
}

size_t sClientInfo::get_initial_size()
{
    size_t class_size = 0;
    class_size += sizeof(sMacAddr); // mac
    class_size += sizeof(uint16_t); // time_since_last_association_sec
    return class_size;
}

bool sClientInfo::init()
{
    if (getBuffRemainingBytes() < kMinimumLength) {
        TLVF_LOG(ERROR) << "Not enough available space on buffer. Class init failed";
        return false;
    }
    m_mac = (sMacAddr*)m_buff_ptr__;
    if (!buffPtrIncrementSafe(sizeof(sMacAddr))) { return false; }
    if (!m_parse__) { m_mac->struct_init(); }
    m_time_since_last_association_sec = (uint16_t*)m_buff_ptr__;
    if (!buffPtrIncrementSafe(sizeof(uint16_t))) { return false; }
    if (m_parse__ && m_swap__) { class_swap(); }
    return true;
}


