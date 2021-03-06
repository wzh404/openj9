/*******************************************************************************
 * Copyright (c) 2000, 2016 IBM Corp. and others
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

#include "codegen/Linkage.hpp"

namespace TR { class AutomaticSymbol; }
namespace TR { class CodeGenerator; }
namespace TR { class RegisterDependencyConditions; }
namespace TR { class ResolvedMethodSymbol; }
namespace TR { class Snippet; }

namespace TR {

class S390CHelperLinkage : public TR::Linkage
   {
   uint32_t _preservedRegisterMapForGC;
   TR::RealRegister::RegNum _methodMetaDataRegister;
   TR::RealRegister::RegNum _returnAddressRegister;
	// Following Regs are needed only in the case of zOS.
#if defined(J9ZOS390)
	TR::RealRegister::RegNum _DSAPointerRegister;
#if defined(TR_HOST_32BIT)
	TR::RealRegister::RegNum _CAAPointerRegister;
#endif
#endif
public:

   S390CHelperLinkage(TR::CodeGenerator * cg, TR_S390LinkageConventions elc=TR_JavaHelper, TR_LinkageConventions lc=TR_CHelper);

   virtual void createPrologue(TR::Instruction * cursor) { TR_ASSERT(false, "Not Implemented"); }
   virtual void createEpilogue(TR::Instruction * cursor) { TR_ASSERT(false, "Not Implemented"); }
   
   virtual void mapStack(TR::ResolvedMethodSymbol *symbol) { TR_ASSERT(false, "Not Implemented"); }
   virtual void mapSingleAutomatic(TR::AutomaticSymbol *p, uint32_t &stackIndex) { TR_ASSERT(false, "Not Implemented"); }
   virtual bool hasToBeOnStack(TR::ParameterSymbol * parm) { TR_ASSERT(false, "Not Implemented"); return false; }
   virtual void initS390RealRegisterLinkage() { TR_ASSERT(false, "Not Implemented"); }
   virtual TR::RealRegister::RegNum setMethodMetaDataRegister(TR::RealRegister::RegNum r) { return _methodMetaDataRegister = r; }
   virtual TR::RealRegister::RegNum getMethodMetaDataRegister() { return _methodMetaDataRegister; }
   virtual TR::RealRegister::RegNum setReturnAddressRegister(TR::RealRegister::RegNum r) { return _returnAddressRegister = r; }
   virtual TR::RealRegister::RegNum getReturnAddressRegister() { return _returnAddressRegister; }
#if defined(J9ZOS390)
	virtual TR::RealRegister::RegNum setDSAPointerRegister(TR::RealRegister::RegNum r) { return _DSAPointerRegister = r; }
	virtual TR::RealRegister::RegNum getDSAPointerRegister() { return _DSAPointerRegister; }
#if defined(TR_HOST_32BIT)
	virtual TR::RealRegister::RegNum setCAAPointerRegister(TR::RealRegister::RegNum r) { return _CAAPointerRegister = r; }
	virtual TR::RealRegister::RegNum getCAAPointerRegister() { return _CAAPointerRegister; }
#endif
#endif  

   virtual TR::Register * buildIndirectDispatch(TR::Node * callNode) 
      { 
      TR_ASSERT(false, "Indirect dispatch is currently not supported");
      return NULL; 
      }
   virtual TR::Register * buildDirectDispatch(TR::Node * callNode)
      {
      return buildDirectDispatch(callNode,NULL);
      }
   TR::Register* buildDirectDispatch(TR::Node *callNode, TR_Stack<TR::Register*>& paramInRegister)
   	{
   	return buildDirectDispatch(callNode, NULL, paramInRegister);
   	}
   TR::Register *buildDirectDispatch(TR::Node *callNode, TR::RegisterDependencyConditions** deps)
   	{
   	TR_Stack<TR::Register*> paramInRegisters(cg()->trMemory());
   	return buildDirectDispatch(callNode, deps, paramInRegisters);
   	}
   TR::Register *buildDirectDispatch(TR::Node *callNode, TR::RegisterDependencyConditions** deps, TR_Stack<TR::Register*>& paramInRegisters);
   };
}
