#pragma once
// values stated in bytes
#define RAM_SIZE (256*256/8)
#define VIDEO_SIZE (256*256/8) // starting at 0x2000
#define ROM_SIZE (256*256/8) // staring at 0x4000 to 0x6000

enum ButtonType {
    REG0,
    REG1,
    REG2,
    REG3,
    REG4,
    REG5,
    REG6,
    REG7,
    RUN,
    STEP,
    STOP,
    START,
    N_FLAG,
    Z_FLAG,
    V_FLAG,
    C_FLAG,
    SYNC,
    CONV,
    TICKS,
};