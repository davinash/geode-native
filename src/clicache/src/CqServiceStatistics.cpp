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

//#include "geode_includes.hpp"
#include "CqServiceStatistics.hpp"


namespace Apache
{
  namespace Geode
  {
    namespace Client
    {

	System::UInt32 CqServiceStatistics::numCqsActive( )
	{
	  return NativePtr->numCqsActive( );
	}
    System::UInt32 CqServiceStatistics::numCqsCreated( )
	{
	  return NativePtr->numCqsCreated( );
	}
    System::UInt32 CqServiceStatistics::numCqsClosed( )
	{
	  return NativePtr->numCqsClosed( );
	}
    System::UInt32 CqServiceStatistics::numCqsStopped( )
	{
	  return NativePtr->numCqsStopped( );
	}
    System::UInt32 CqServiceStatistics::numCqsOnClient( )
	{
	  return NativePtr->numCqsOnClient( );
    }  // namespace Client
  }  // namespace Geode
}  // namespace Apache

 } //namespace 
