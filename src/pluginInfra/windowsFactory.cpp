// Copyright (c) 2021 Farzon Lotfi All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "windowsFactory.h"
#include "interfaces/pch.h"
#include <Windows.h>

Load_ptr WindowsFactory::getLoadLib() {
  return Helpers::makeShared<WindowsDLibLoad>();
}

bool WindowsDLibLoad::LoadLibraryFromPath(std::string sLoadPath) {
  mProcHinstance = LoadLibrary(sLoadPath.c_str());
  if (mProcHinstance == nullptr) {
    std::cerr << "LoadLibrary  failed with error code " << GetLastError()
              << std::endl;
    return false;
  }

  for (int i = 0; i < disasmImpl::NUM_FUNCTIONS; i++) {
    mDllFunctions.func_ptr[i] = reinterpret_cast<func_ptr_t>(GetProcAddress(
        mProcHinstance, DynamicLibMgr::getDynamicLibFunctionName(i)));
    assert(mDllFunctions.func_ptr[i] != nullptr);
    if (mDllFunctions.func_ptr[i] == nullptr) {
      return false;
    }
  }
  return true;
}

function_union &WindowsDLibLoad::getLoadedLibrary() { return mDllFunctions; }

WindowsDLibLoad::~WindowsDLibLoad() {
  if (mProcHinstance != nullptr) {
    FreeLibrary(mProcHinstance);
  }
}