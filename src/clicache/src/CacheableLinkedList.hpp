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

#pragma once

#include "geode_defs.hpp"
#include "CacheableVector.hpp"


using namespace System;
using namespace System::Collections::Generic;

namespace Apache
{
  namespace Geode
  {
    namespace Client
    {

      /// <summary>
      /// A mutable <c>IGeodeSerializable</c> vector wrapper that can serve as
      /// a distributable object for caching. This class extends .NET generic
      /// <c>List</c> class.
      /// </summary>
      ref class CacheableLinkedList
        : public IGeodeSerializable
      {
        System::Collections::Generic::LinkedList<Object^>^ m_linkedList;
      public:
        /// <summary>
        /// Allocates a new empty instance.
        /// </summary>
        inline CacheableLinkedList(System::Collections::Generic::LinkedList<Object^>^ list)
        {
          m_linkedList = list;
        }


        /// <summary>
        /// Static function to create a new empty instance.
        /// </summary>
        inline static CacheableLinkedList^ Create()
        {
          return gcnew CacheableLinkedList(gcnew System::Collections::Generic::LinkedList<Object^>());
        }

        /// <summary>
        /// Static function to create a new empty instance.
        /// </summary>
        inline static CacheableLinkedList^ Create(System::Collections::Generic::LinkedList<Object^>^ list)
        {
          return gcnew CacheableLinkedList(list);
        }


        // Region: IGeodeSerializable Members

        /// <summary>
        /// Returns the classId of the instance being serialized.
        /// This is used by deserialization to determine what instance
        /// type to create and deserialize into.
        /// </summary>
        /// <returns>the classId</returns>
        virtual property System::UInt32 ClassId
        {
          virtual System::UInt32 get()
          {
            return GeodeClassIds::CacheableLinkedList;
          }
        }

        // Region: IGeodeSerializable Members

        virtual void ToData(DataOutput^ output)
        {
          if (m_linkedList != nullptr)
          {
            output->WriteArrayLen(m_linkedList->Count);
            for each (Object^ obj in m_linkedList) {
              //TODO::split
              output->WriteObject(obj);
            }
          }
          else
            output->WriteByte(0xFF);
        }

        virtual IGeodeSerializable^ FromData(DataInput^ input)
        {
          int len = input->ReadArrayLen();
          for (int i = 0; i < len; i++)
          {
            m_linkedList->AddLast(input->ReadObject());
          }
          return this;
        }

        /*System::UInt32 ObjectSize::get()
        {
        //TODO::
        System::UInt32 size = static_cast<System::UInt32> (sizeof(CacheableVector^));
        for each (IGeodeSerializable^ val in this) {
        if (val != nullptr) {
        size += val->ObjectSize;
        }
        }
        return m_linkedList->Count;
        }*/

        virtual property System::UInt32 ObjectSize
        {
          virtual System::UInt32 get()
          {
            return m_linkedList->Count;
          }
        }

        virtual property System::Collections::Generic::LinkedList<Object^>^ Value
        {
          virtual System::Collections::Generic::LinkedList<Object^>^ get()
          {
            return m_linkedList;
          }
        }
        // End Region: IGeodeSerializable Members

        /// <summary>
        /// Factory function to register this class.
        /// </summary>
        static IGeodeSerializable^ CreateDeserializable()
        {
          return gcnew CacheableLinkedList(gcnew System::Collections::Generic::LinkedList<Object^>());
        }
      };
    }  // namespace Client
  }  // namespace Geode
}  // namespace Apache

