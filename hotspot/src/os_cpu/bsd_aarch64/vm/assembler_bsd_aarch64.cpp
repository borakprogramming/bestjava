/*
 * Copyright (c) 2020, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 *
 */

#include "precompiled.hpp"
#include "asm/macroAssembler.hpp"
#include "asm/macroAssembler.inline.hpp"
#include "runtime/os.hpp"
#include "runtime/threadLocalStorage.hpp"

void MacroAssembler::get_thread(Register dst) {
  RegSet saved_regs = RegSet::range(r0, r17) + RegSet::range(r19, r20) + lr - dst;
  push(saved_regs, sp);
  mov(c_rarg0, ThreadLocalStorage::thread_index());
  mov(r19, CAST_FROM_FN_PTR(address, pthread_getspecific));
  blr(r19);
  if (dst != c_rarg0) {
    mov(dst, c_rarg0);
  }
  // restore pushed registers
  pop(saved_regs, sp);
}

