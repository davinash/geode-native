#pragma once

#ifndef GEODE_CACHECONFIG_H_
#define GEODE_CACHECONFIG_H_

/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file
 */
// CacheConfig.h: interface for the CacheConfig class.
//
//////////////////////////////////////////////////////////////////////

#if _MSC_VER > 1000
#pragma warning(disable : 4786)
#endif  // _MSC_VER > 1000

#include <geode/geode_globals.hpp>
#include <string>
#include <map>
#include "RegionConfig.hpp"
#include <geode/ExceptionTypes.hpp>
#include <geode/DistributedSystem.hpp>

//
// Sneaky structure forward decl;
//

struct _xmlNode;
struct _xmlDoc;
typedef struct _xmlDoc xmlDoc;
typedef struct _xmlNode xmlNode;

namespace apache {
namespace geode {
namespace client {

typedef std::map<std::string, RegionConfigPtr> RegionConfigMapT;

class CPPCACHE_EXPORT CacheConfig {
 public:
  CacheConfig(const char* xmlFileName);

  bool parse();

  bool parseRegion(xmlNode* node);

  bool parseAttributes(const char* name, xmlNode* node);

  RegionConfigMapT& getRegionList();

  virtual ~CacheConfig();

 private:
  CacheConfig();

  xmlDoc* m_doc;
  xmlNode* m_root_element;

  RegionConfigMapT m_regionList;
};
}  // namespace client
}  // namespace geode
}  // namespace apache

#endif  // GEODE_CACHECONFIG_H_
