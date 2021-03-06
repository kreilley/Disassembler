/*
 * Copyright (c) 2021 Farzon Lotfi All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __abstract_factory_h__
#define __abstract_factory_h__
#include "interfaces/pch.h"
#include <memory>

#include "dynamicLibMgr.h"

class ILoad {
public:
  virtual bool LoadLibraryFromPath(std::string sLoadPath) = 0;
  virtual function_union &getLoadedLibrary() = 0;
  ILoad() {}
};

typedef std::shared_ptr<ILoad> Load_ptr;

namespace Helpers {

template <typename Derived> std::shared_ptr<ILoad> makeShared() {
  return std::make_shared<Derived>();
}
}; // namespace Helpers

class AbstractOSFactory;
typedef std::shared_ptr<AbstractOSFactory> AbstractOSFactory_ptr;

class AbstractOSFactory {
public:
  virtual Load_ptr getLoadLib() = 0;

  static AbstractOSFactory_ptr createFactory();
};

#endif // __abstract_factory_h__