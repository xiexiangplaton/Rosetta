// ==============================================================================
// Copyright 2020 The LatticeX Foundation
// This file is part of the Rosetta library.
//
// The Rosetta library is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// The Rosetta library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with the Rosetta library. If not, see <http://www.gnu.org/licenses/>.
// ==============================================================================
#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <random>
using namespace std;

namespace emp {
class PRG;
}
typedef __m128i block;

namespace rosetta {

class MpcPRG {
#define BLOCK_COUNT 2048
  uint64_t counter_ = 0;
  block data_[BLOCK_COUNT];

  int index64 = 0;
  int index08 = 0;
  int index01 = 0;
  block block64{0};
  block block08{0};
  block block01{0};

  shared_ptr<emp::PRG> prg_ = nullptr;
  std::string kdefault =
    std::string("\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00");

 public:
  MpcPRG();
  MpcPRG(const std::string& key);

 private:
  block newRandomBlocks();

 public:
  /**
   * \param key, 16 bytes
   */
  void reseed(const void* key, uint64_t id = 0);
  void reseed(const std::string& key);
  void randomDatas(void* data, int nbytes);
  uint64_t get64Bits();
  uint8_t get8Bits();
  uint8_t getBit();
};

} // namespace rosetta
