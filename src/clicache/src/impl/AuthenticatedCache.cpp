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

//#include "../geode_includes.hpp"
#include "../Cache.hpp"
#include "../DistributedSystem.hpp"
#include "../Region.hpp"
#include "../RegionAttributes.hpp"
#include "../QueryService.hpp"
#include "../FunctionService.hpp"
#include "../Execution.hpp"
#include "AuthenticatedCache.hpp"
#include "PdxInstanceFactoryImpl.hpp"
using namespace System;

namespace Apache
{
  namespace Geode
  {
    namespace Client
    {

      bool AuthenticatedCache::IsClosed::get( )
      {
        return NativePtr->isClosed( );
      }

      void AuthenticatedCache::Close( )
      {
        _GF_MG_EXCEPTION_TRY2

          NativePtr->close(  );

        _GF_MG_EXCEPTION_CATCH_ALL2
      }
      
			//TODO::split
      generic<class TKey, class TValue>
      IRegion<TKey, TValue>^ AuthenticatedCache::GetRegion( String^ path )
      {
        _GF_MG_EXCEPTION_TRY2

          ManagedString mg_path( path );
          apache::geode::client::RegionPtr& nativeptr(
            NativePtr->getRegion( mg_path.CharPtr ) );

          return Client::Region<TKey, TValue>::Create( nativeptr.ptr( ) );

        _GF_MG_EXCEPTION_CATCH_ALL2
      }
      
      generic<class TKey, class TResult>
      Client::QueryService<TKey, TResult>^ AuthenticatedCache::GetQueryService( )
      {
        _GF_MG_EXCEPTION_TRY2

          return Client::QueryService<TKey, TResult>::Create( NativePtr->getQueryService( ).ptr( ) );

        _GF_MG_EXCEPTION_CATCH_ALL2
      }

      generic<class TKey, class TValue>
      array<IRegion<TKey, TValue>^>^ AuthenticatedCache::RootRegions( )
      {
        apache::geode::client::VectorOfRegion vrr;
        NativePtr->rootRegions( vrr );
        array<IRegion<TKey, TValue>^>^ rootRegions =
          gcnew array<IRegion<TKey, TValue>^>( vrr.size( ) );

        for( System::Int32 index = 0; index < vrr.size( ); index++ )
        {
          apache::geode::client::RegionPtr& nativeptr( vrr[ index ] );
          rootRegions[ index ] = Client::Region<TKey, TValue>::Create( nativeptr.ptr( ) );
        }
        return rootRegions;
      }

       IPdxInstanceFactory^ AuthenticatedCache::CreatePdxInstanceFactory(String^ className)
        {
          return gcnew Internal::PdxInstanceFactoryImpl(className);;
    }  // namespace Client
  }  // namespace Geode
}  // namespace Apache

}
