/* Copyright 2011 Google Inc.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

// This file is a part of AddressSanitizer, an address sanity checker.

#ifndef ASAN_TEST_CONFIG_H
#define ASAN_TEST_CONFIG_H

#include <vector>
#include <string>
#include <map>

#include "gtest/gtest.h"

using std::string;
using std::vector;
using std::map;

#ifndef ASAN_UAR
# error "please define ASAN_UAR"
#endif

#ifndef ASAN_HAS_EXCEPTIONS
# error "please define ASAN_HAS_EXCEPTIONS"
#endif

#ifndef ASAN_HAS_BLACKLIST
# error "please define ASAN_HAS_BLACKLIST"
#endif

#ifndef ASAN_NEEDS_SEGV
# error "please define ASAN_NEEDS_SEGV"
#endif

#endif  // ASAN_TEST_CONFIG_H
