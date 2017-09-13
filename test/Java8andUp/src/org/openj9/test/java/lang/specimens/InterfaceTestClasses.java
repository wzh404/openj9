package org.openj9.test.java.lang.specimens;

/*******************************************************************************
 * Copyright (c) 1998, 2017 IBM Corp. and others
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

public abstract class InterfaceTestClasses{

	public interface I1 {
		default void m1() {
		}
		default void m2() {
		}
		default void m3() {
		}
	}

	public interface I2 extends I1 {
		void m1();
		void m2();
		void m3();
	}
	public interface I3 extends I1, I2 {
		void m1();
		void m2();
		void m3();
	}
	public abstract class SuperDuperClass implements I1, I2, I3{}
	public abstract class SuperClass extends SuperDuperClass implements I1, I2, I3{}
	public abstract class SubClass extends SuperClass implements I1, I2, I3 {}

}