/*
   Copyright (c) 2014, The Linux Foundation. All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.
   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

void property_override(char const prop[], char const value[])
{
    prop_info *pi;

    pi = (prop_info*) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

/* Target-Specific Dalvik Heap & HWUI Configuration */
void target_ram() {
    std::string ram;

    ram = property_get("ro.boot.ram");

    // TODO: Some Models has different settings here as they have more ram
}

void num_sims() {
    std::string num_sim;

    num_sim = property_get("lge.sim_num");

    if (num_sim == "2") {
        property_set("persist.radio.multisim.config", "dsds");
        property_set("ro.hw.dualsim", "true");
    } else {
        property_set("persist.radio.multisim.config", "");
        property_set("ro.hw.dualsim", "false");
    }
}

void vendor_load_properties()
{
    std::string carrier;
    std::string devicename;

    //std::string platform;
    std::string device_boot;
    std::string sku;
    std::string radio;
    std::string device;
    std::string num_sim;

    //platform = property_get("ro.board.platform");
    //if (platform != ANDROID_TARGET)
    //    return;

    device_boot = property_get("ro.boot.device");
    property_set("ro.hw.device", device_boot.c_str());

    property_override("ro.product.device", "m216");

    sku = property_get("model.name");
    property_override("ro.product.model", sku.c_str());

    carrier = property_get("ro.boot.carrier");
    property_set("ro.carrier", carrier.c_str());

    radio = property_get("ro.boot.radio");
    property_set("ro.hw.radio", radio.c_str());

    num_sim = property_get("lge.sim_num");

    /* Common for all models */
    property_override("ro.build.product", "m216");
    target_ram();
    num_sims();

    if (sku == "LG-K420ds") {
        //TODO
    }

    if (sku == "LG-K420n") {
        //TODO
    }

    device = property_get("ro.product.device");
    INFO("Found sku id: %s setting build properties for %s device\n", sku.c_str(), device.c_str());
}
