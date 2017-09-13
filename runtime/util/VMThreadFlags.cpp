/*******************************************************************************
 * Copyright (c) 1991, 2014 IBM Corp. and others
 *
 * This program and the accompanying materials are made available under
 * the terms of the Eclipse Public License 2.0 which accompanies this
 * distribution and is available at https://www.eclipse.org/legal/epl-2.0/
 * or the Apache License, Version 2.0 which accompanies this distribution and
 * is available at https://www.apache.org/licenses/LICENSE-2.0.
 *
 * This Source Code may also be made available under the following
 * Secondary Licenses when the conditions for such availability set
 * forth in the Eclipse Public License, v. 2.0 are satisfied: GNU
 * General Public License, version 2 with the GNU Classpath
 * Exception [1] and GNU General Public License, version 2 with the
 * OpenJDK Assembly Exception [2].
 *
 * [1] https://www.gnu.org/software/classpath/license.html
 * [2] http://openjdk.java.net/legal/assembly-exception.html
 *
 * SPDX-License-Identifier: EPL-2.0 OR Apache-2.0
 *******************************************************************************/

#include "j9protos.h"
#include "VMAccess.hpp"

extern "C" {

void
clearEventFlag(J9VMThread *vmThread, UDATA flag)
{
	VM_VMAccess::clearPublicFlags(vmThread, flag);
}

void
clearHaltFlag(J9VMThread *vmThread, UDATA flag)
{
	VM_VMAccess::clearPublicFlags(vmThread, flag, true);
}

void
setEventFlag(J9VMThread *vmThread, UDATA flag)
{
	VM_VMAccess::setPublicFlags(vmThread, flag);
}

void
setHaltFlag(J9VMThread *vmThread, UDATA flag)
{
	VM_VMAccess::setPublicFlags(vmThread, flag, true);
}

}