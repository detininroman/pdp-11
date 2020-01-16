#pragma once

enum class Error {
    OK = 0,
    NOT_FOUND = 1,
    OVERFLOW = 2,
    DIVISION_BY_ZERO = 3,
    OUT_OF_BOUNDS = 4,
    FINISHED = 5,
    NOT_INITED = 6,
    UNKNOWN_DEVICE = 7,
    EMPTY_BACKLOG = 8
};