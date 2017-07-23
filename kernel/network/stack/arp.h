#pragma once

#include <kernel/network/arp.h>
#include <kernel/network/iface.h>

void network_stack_arp_init(void);
void arp_lookup(network_iface_t*, uint32_t addr, uint8_t* hw);
list_t* arp_get_known(network_iface_t*);
void arp_ask(network_iface_t*, uint32_t);