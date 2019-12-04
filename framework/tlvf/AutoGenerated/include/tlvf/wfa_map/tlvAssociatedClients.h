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

#ifndef _TLVF_WFA_MAP_TLVASSOCIATEDCLIENTS_H_
#define _TLVF_WFA_MAP_TLVASSOCIATEDCLIENTS_H_

#include <cstddef>
#include <stdint.h>
#include <tlvf/swap.h>
#include <string.h>
#include <memory>
#include <tlvf/BaseClass.h>
#include "tlvf/wfa_map/eTlvTypeMap.h"
#include <tuple>
#include "tlvf/common/sMacAddr.h"

namespace wfa_map {

class sClientInfo;

class tlvAssociatedClients : public BaseClass
{
    public:
        tlvAssociatedClients(uint8_t* buff, size_t buff_len, bool parse = false, bool swap_needed = false);
        tlvAssociatedClients(std::shared_ptr<BaseClass> base, bool parse = false, bool swap_needed = false);
        ~tlvAssociatedClients();

        typedef struct sBssInfo {
            sMacAddr bssid;
            uint16_t clients_associated_list_length;
            sClientInfo* clients_associated_list; //TLVF_TODO: not supported yet
            void struct_swap(){
                bssid.struct_swap();
                tlvf_swap(16, reinterpret_cast<uint8_t*>(&clients_associated_list_length));
            }
            void struct_init(){
                bssid.struct_init();
            }
        } __attribute__((packed)) sBssInfo;
        
        const eTlvTypeMap& type();
        const uint16_t& length();
        uint8_t& bss_list_length();
        std::tuple<bool, sBssInfo&> bss_list(size_t idx);
        bool alloc_bss_list(size_t count = 1);
        void class_swap();
        static size_t get_initial_size();

    private:
        bool init();
        eTlvTypeMap* m_type = nullptr;
        uint16_t* m_length = nullptr;
        uint8_t* m_bss_list_length = nullptr;
        sBssInfo* m_bss_list = nullptr;
        size_t m_bss_list_idx__ = 0;
        int m_lock_order_counter__ = 0;
};

class sClientInfo : public BaseClass
{
    public:
        sClientInfo(uint8_t* buff, size_t buff_len, bool parse = false, bool swap_needed = false);
        sClientInfo(std::shared_ptr<BaseClass> base, bool parse = false, bool swap_needed = false);
        ~sClientInfo();

        sMacAddr& mac();
        uint16_t& time_since_last_association_sec();
        void class_swap();
        static size_t get_initial_size();

    private:
        bool init();
        sMacAddr* m_mac = nullptr;
        uint16_t* m_time_since_last_association_sec = nullptr;
};

}; // close namespace: wfa_map

#endif //_TLVF/WFA_MAP_TLVASSOCIATEDCLIENTS_H_
