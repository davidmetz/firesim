// See LICENSE for license details.

#include "simif.h"

#include <stdlib.h>
#include <stdio.h>

#include <utility>
#include <map>

constexpr size_t reg_n_reads = 2;
constexpr size_t reg_n_writes = 2;

const size_t reg_w_addr_ios[reg_n_writes] = { io_writes_0_addr, io_writes_1_addr };
const size_t reg_w_data_ios[reg_n_writes] = { io_writes_0_data, io_writes_1_data };
const size_t reg_w_en_ios[reg_n_writes] = { io_writes_0_en, io_writes_1_en };

const size_t reg_r_addr_ios[reg_n_reads] = { io_reads_0_addr, io_reads_1_addr };
const size_t reg_r_data_ios[reg_n_reads] = { io_reads_0_data, io_reads_1_data };

struct Regfile_t: virtual simif_t
{
  size_t mem_depth = 10;

  Regfile_t(int argc, char** argv) {}

  void run() {
    target_reset();
    for (int cycle = 0; cycle < 100; cycle++) {
      do_iteration();
    }
  }

  void do_iteration(void) {
    for (size_t w_idx = 0; w_idx < reg_n_writes; w_idx++) {
      if (rand() % 2) {
	data_t rand_addr = rand() % mem_depth;
	data_t rand_data = rand();
	history[rand_addr] = rand_data;
	poke(reg_w_addr_ios[w_idx], rand_addr);
	poke(reg_w_data_ios[w_idx], rand_data);
	poke(reg_w_en_ios[w_idx], 1);
      } else {
	poke(reg_w_en_ios[w_idx], 0);
      }
    }
    for (size_t r_idx = 0; r_idx < reg_n_reads; r_idx++) {
      data_t rand_addr = rand() % mem_depth;
      prev_reads[r_idx] = rand_addr;
      poke(reg_r_addr_ios[r_idx], rand_addr);
    }
    step(1);
    //peek(reg_r_data_ios[0][0]);
    for (size_t r_idx = 0; r_idx < reg_n_reads; r_idx++) {
      data_t prev_addr = prev_reads[r_idx];
      if (history.count(prev_addr)) {
	expect(reg_r_data_ios[r_idx], history[prev_addr]);
      }
    }
  }

 private:
  
  std::map<data_t, data_t> history;
  std::map<size_t, data_t> prev_reads;  
};
