// Copyright (c) 2018 The Eco Chain team
// Distributed under the GPLv3 software license, check
// https://www.gnu.org/licenses/gpl-3.0.en.html for details       


#include "ecoc.h"

namespace ecoc {
    void ecocLog(const std::string message) {
    if (debug) {
      LogPrintf("ecoc: %s\n", message);
    }
  }

  void ecocLogNL(const std::string message) {
    if (debug) {
      LogPrintf("ecoc: %s", message);
    }
  }
  
  void ecocLogNL(int i) {
    if (debug) {
      LogPrintf("ecoc: %d", i);
    }
  }

  void ecocLog(int i) {
    if (debug) {
      LogPrintf("ecoc: %d\n", i);
    }
  }

  void ecocLogFun(const std::string message) {
    if (debug) {
      LogPrintf("ecoc: Entering function %s\n", message);
    }
  }
}

