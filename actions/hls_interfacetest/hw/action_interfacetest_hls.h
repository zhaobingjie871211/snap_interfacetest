#ifndef __ACTION_INTERFACETEST_HLS_H__
#define __ACTION_INTERFACETEST_HLS_H__

/*
 * Copyright 2017 International Business Machines
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdint.h>
#include <string.h>
#include <ap_int.h>
#include <hls_stream.h>

#include <hls_snap.H>
#include <../sw/action_interfacetest.h>

#define CARD_DRAM_SIZE (1 * 1024 *1024 * 1024)
#define MAX_NB_OF_BYTES_READ  (4 * 1024)
#define MAX_NB_OF_WORDS_READ MAX_NB_OF_BYTES_READ/BPERDW
#define BPERCL 128                           //128Bytes for one PSL Cacheline
//typedef char word_t[BPERDW];
//typedef snapu64_t address_t;

//#define PATTERN_SIZE BPERDW
//#define TEXT_SIZE    4096 * MAX_NB_OF_BYTES_READ // used for streaming only
//#define HOST2DDR 0
//#define DDR2HOST 1

//---------------------------------------------------------------------
typedef struct {
    CONTROL Control;       /*  16 bytes */
    interfacetest_job_t Data;     /* 108 Bytes */
    uint8_t padding[SNAP_HLS_JOBSIZE - sizeof(interfacetest_job_t)];
} action_reg;

#endif  /* __ACTION_MC_HLS_H__ */
