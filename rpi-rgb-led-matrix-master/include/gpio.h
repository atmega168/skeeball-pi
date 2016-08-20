// -*- mode: c++; c-basic-offset: 2; indent-tabs-mode: nil; -*-
// Copyright (C) 2013 Henner Zeller <h.zeller@acm.org>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation version 2.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://gnu.org/licenses/gpl-2.0.txt>

#ifndef RPI_GPIO_H
#define RPI_GPIO_H

#include <stdint.h>

// Putting this in our namespace to not collide with other things called like
// this.
namespace rgb_matrix {
// For now, everything is initialized as output.
class GPIO {
 public:
  // Available bits that actually have pins.
  static const uint32_t kValidBits;
  uint8_t writeCycles;

  GPIO();

  // Initialize before use. Returns 'true' if successful, 'false' otherwise
  // (e.g. due to a permission problem).
  bool Init();

  // Initialize outputs.
  // Returns the bits that are actually set.
  uint32_t InitOutputs(uint32_t outputs);

  // Set the bits that are '1' in the output. Leave the rest untouched.
  inline void SetBits(uint32_t value) {
    volatile uint8_t i = writeCycles;
    do {
      gpio_port_[0x1C / sizeof(uint32_t)] = value;
    } while(--i);
  }

  // Clear the bits that are '1' in the output. Leave the rest untouched.
  inline void ClearBits(uint32_t value) {
    volatile uint8_t i = writeCycles;
    do {
      gpio_port_[0x28 / sizeof(uint32_t)] = value;
    } while(--i);
  }

  // Write all the bits of "value" mentioned in "mask". Leave the rest untouched.
  inline void WriteMaskedBits(uint32_t value, uint32_t mask) {
    // Writing a word is two operations. The IO is actually pretty slow, so
    // this should probably  be unnoticable.
    ClearBits(~value & mask);
    SetBits(value & mask);
  }

  inline void Write(uint32_t value) { WriteMaskedBits(value, output_bits_); }

 private:
  uint32_t output_bits_;
  volatile uint32_t *gpio_port_;
};
}  // end namespace rgb_matrix
#endif  // RPI_GPIO_H
