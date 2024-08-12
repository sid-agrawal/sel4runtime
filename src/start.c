/*
 * Copyright 2019, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#include <sel4/sel4.h>
#include <sel4runtime.h>
#include <sel4runtime/start.h>

extern void sel4gpi_set_exit_cb(void);

void __sel4runtime_start_main(
    int (*main)(),
    unsigned long argc,
    char const *const *argv,
    char const *const *envp,
    auxv_t const auxv[]
)
{
    __sel4runtime_load_env(argc, argv, envp, auxv);

    sel4runtime_exit(main(argc, argv, envp));
}

void __sel4runtime_start_main_osm(
    int (*main)(),
    unsigned long argc,
    char const *const *argv,
    char const *const *envp,
    auxv_t const auxv[])
{
    __sel4runtime_load_env(argc, argv, envp, auxv);
    sel4gpi_set_exit_cb();
    sel4runtime_exit(main(argc, argv, envp));
}

void __sel4runtime_start_entry_osm(
    int (*entry)(),
    unsigned long argc,
    char const *const *argv)
{
    sel4gpi_set_exit_cb();
    sel4runtime_exit_no_destruct(entry(argc, (char **)argv));
}
