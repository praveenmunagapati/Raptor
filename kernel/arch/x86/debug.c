#include "debug.h"
#include "heap.h"
#include "paging.h"

#include <liblox/net.h>

#include <kernel/tty.h>

#include <kernel/network/iface.h>
#include <kernel/network/ip.h>
#include <kernel/network/udp.h>
#include <kernel/network/ethernet.h>

#include <kernel/dispatch/events.h>

#include <kernel/debug/console.h>

#include <kernel/arch/x86/devices/pci/pci.h>

#include <kernel/rkmalloc/rkmalloc.h>

static void debug_kpused(tty_t* tty, const char* input) {
    unused(input);

    size_t size = kpused();
    int kb = size / 1024;

    tty_printf(tty, "Used: %d bytes, %d kb\n", size, kb);
}

static void debug_page_stats(tty_t* tty, const char* input) {
    unused(input);

    uintptr_t memory_total = paging_memory_total();
    uintptr_t memory_used = paging_memory_used();

    tty_printf(tty,
               "Total Memory: %d bytes, %d kb\n",
               memory_total,
               (uintptr_t) (memory_total / 1024)
    );

    tty_printf(tty,
               "Used Memory: %d bytes, %d kb\n",
               memory_used,
               (uintptr_t) (memory_used / 1024)
    );
}

static void pci_show_simple(uint32_t loc, uint16_t vid, uint16_t did, void* extra) {
    tty_t* tty = extra;

    const char* vendor = pci_vendor_lookup(vid);
    const char* dev = pci_device_lookup(vid, did);

    if (vendor == NULL) {
        vendor = "Unknown";
    }

    if (dev == NULL) {
        dev = "Unknown";
    }

    tty_printf(tty,
               "(0x%x) [%s] (0x%x) by [%s] (0x%x)\n",
               loc, dev, did, vendor, vid);
}

static void debug_pci_list(tty_t* tty, const char* input) {
    unused(input);

    pci_scan(pci_show_simple, -1, tty);
}

static void debug_fake_event(tty_t* tty, const char* input) {
    unused(tty);

    event_dispatch((char*) input, NULL);
}

void debug_x86_init(void) {
    debug_console_register_command("kpused", debug_kpused);
    debug_console_register_command("pci-list", debug_pci_list);
    debug_console_register_command("page-stats", debug_page_stats);
    debug_console_register_command("fake-event", debug_fake_event);
}
