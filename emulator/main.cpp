#include "emulator.hpp"

int main() {
  Emulator::instance().initROM("rom.raw");
  return 0;
}
