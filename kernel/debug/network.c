#include "console.h"

#include <kernel/network/iface.h>

static void debug_network_iface_list(tty_t* tty, const char* input) {
    unused(input);

    list_t* interfaces = network_iface_get_all();

    list_for_each(node, interfaces) {
        network_iface_t* iface = node->value;

        uint8_t mac[6];
        network_iface_get_mac(iface, mac);

        tty_printf(tty, "Interface %s:\n", iface->name);

        tty_printf(tty,
                   "  MAC Address: %2x:%2x:%2x:%2x:%2x:%2x\n",
                   mac[0],
                   mac[1],
                   mac[2],
                   mac[3],
                   mac[4],
                   mac[5]
        );
    }
}

void debug_network_init(void) {
    debug_console_register_command("net-iface-list", debug_network_iface_list);
}
