//See LICENSE for license details
#ifndef __TRACERS_H
#define __TRACERS_H

#include "bridges/bridge_driver.h"
#include "bridges/clock_info.h"
#include <vector>

#ifdef TRACERSBRIDGEMODULE_struct_guard

class tracers_t: public bridge_driver_t

{
    public:
        tracers_t(simif_t *sim,
                  TRACERSBRIDGEMODULE_struct * mmio_addrs,
                  int tracerno);
        ~tracers_t();

        virtual void init();
        virtual void tick();
        virtual bool terminate() { return false; }
        virtual int exit_code() { return 0; }
        virtual void finish();

    private:
        TRACERSBRIDGEMODULE_struct * mmio_addrs;
        int invalid_cycles = 0;
};
#endif // TRACERSBRIDGEMODULE_struct_guard

#endif // __TRACERS_H
