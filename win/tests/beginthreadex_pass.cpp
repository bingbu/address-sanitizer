/* Copyright 2012 Google Inc.
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

#define _MT  // needed to make _beginthreadex available.

#include <windows.h>
#include <process.h>

#include "common.h"

unsigned int WINAPI thread_proc(void *context) {
  volatile char stack_buffer[42];
  for (int i = 0; i < sizeof(stack_buffer); ++i)
    stack_buffer[i] = 42;
  return 0;
}

int main(void) {
  HANDLE thr = (HANDLE)_beginthreadex(NULL, 0, thread_proc, NULL, 0, NULL);
  CHECK(thr > 0);
  CHECK(WAIT_OBJECT_0 == WaitForSingleObject(thr, INFINITE));
  CloseHandle(thr);
  return 0;
}
