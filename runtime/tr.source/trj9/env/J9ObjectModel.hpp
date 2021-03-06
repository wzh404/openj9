/*******************************************************************************
 * Copyright (c) 2000, 2017 IBM Corp. and others
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

#ifndef J9_OBJECTMODEL_INCL
#define J9_OBJECTMODEL_INCL

/*
 * The following #define and typedef must appear before any #includes in this file
 */
#ifndef J9_OBJECTMODEL_CONNECTOR
#define J9_OBJECTMODEL_CONNECTOR
namespace J9 { class ObjectModel; }
namespace J9 { typedef J9::ObjectModel ObjectModelConnector; }
#endif

#include "env/OMRObjectModel.hpp"

#include <stdint.h>
#include "env/jittypes.h"

namespace TR { class Node; }
namespace TR { class Compilation; }

namespace J9
{

class ObjectModel : public OMR::ObjectModelConnector
   {
public:

   ObjectModel() :
         OMR::ObjectModelConnector(),
      _usesDiscontiguousArraylets(false) {}

   void initialize();

   bool mayRequireSpineChecks();

   int32_t sizeofReferenceField();
   uintptrj_t elementSizeOfBooleanArray();
   uint32_t getSizeOfArrayElement(TR::Node *node);
   int64_t maxArraySizeInElementsForAllocation(TR::Node *newArray, TR::Compilation *comp);
   int64_t maxArraySizeInElements(int32_t knownMinElementSize, TR::Compilation *comp);

   int32_t maxContiguousArraySizeInBytes();

   uintptrj_t contiguousArrayHeaderSizeInBytes();

   uintptrj_t discontiguousArrayHeaderSizeInBytes();

   bool isDiscontiguousArray(int32_t sizeInBytes);
   bool isDiscontiguousArray(int32_t sizeInElements, int32_t elementSize);

   bool generateCompressedObjectHeaders();

   bool usesDiscontiguousArraylets() { return _usesDiscontiguousArraylets; }
   bool canGenerateArraylets() { return usesDiscontiguousArraylets(); }
   bool useHybridArraylets() { return usesDiscontiguousArraylets(); }
   int32_t arrayletLeafSize() { return _arrayLetLeafSize; }
   int32_t arrayletLeafLogSize() { return _arrayLetLeafLogSize; }

   int32_t compressedReferenceShiftOffset();
   int32_t compressedReferenceShift();

   bool nativeAddressesCanChangeSize();

   uintptrj_t offsetOfObjectVftField();

   uintptrj_t offsetOfHeaderFlags();

   uintptrj_t maskOfObjectVftField();

   int32_t arraySpineShift(int32_t width);
   int32_t arrayletMask(int32_t width);
   int32_t arrayletLeafIndex(int32_t index, int32_t elementSize);
   int32_t objectAlignmentInBytes();
   uintptrj_t offsetOfContiguousArraySizeField();
   uintptrj_t offsetOfDiscontiguousArraySizeField();
   uintptrj_t objectHeaderSizeInBytes();
   uintptrj_t offsetOfIndexableSizeField();

   /**
   * \brief: Determines whether the code generator should generate read barriers for loads of object references from the heap
   *
   * Instead of reaching into the VM each time, for the performance' sake,
   * this value is cached here once at the JIT startup
   * (since it does not change throughout the lifetime of the JIT).
   *
   * \return
   *     true if concurrent scavenge of objects during garbage collection is enabled.
   */
   bool shouldGenerateReadBarriersForFieldLoads();

private:

   bool _usesDiscontiguousArraylets;
   int32_t _arrayLetLeafSize;
   int32_t _arrayLetLeafLogSize;
   bool _shouldGenerateReadBarriersForFieldLoads;
   };

}

#endif
