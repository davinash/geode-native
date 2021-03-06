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

/*
 * The DistributedSystem QuickStart Example.
 * This example connects to two distributed systems.
 * This example takes the following steps:
 *
 * 1. Create a Geode Cache.
 * 2. Now it creates a Pool with poolName1.
 * 3. Adds server(localhost:40404) to a pool factory.
 * 4. Creates a generic region "root1" with the pool then creates a generic subregion "exampleRegion" with the pool.  
 * 5. Put Entries (Key and Value pairs) into the Region.
 * 6. Get Entries from the Region.
 * 7. Invalidate an Entry in the Region.
 * 8. Destroy an Entry in the Region.
 * 9. Now it creates another generic region "root2" and subregion "exampleRegion" with another pool "poolName2", which connects to the server(localhost:40405).
 * 10. Now we do put/get operations.  
 * 11. Close the Cache.
 *
 */


// Use standard namespaces
using System;

// Use the Geode namespaces
//using Apache.Geode.Client;
using Apache.Geode.Client;

namespace Apache.Geode.Client.QuickStart
{
  // The DistributedSystem QuickStart example.
  class DistributedSystem
  {
  
    static void TestDistributedSystem(Cache cache, String hostname, int port, String poolName, String regionName)
    {
      //create pool factory to create the pool.
      PoolFactory fact = PoolManager.CreateFactory();

      //adding host(endpoint) in pool
      fact.AddServer(hostname, port);

      //enabling subscription on pool
      fact.SetSubscriptionEnabled(true);

      //creating pool with name "examplePool"
      fact.Create(poolName);
	  
	    RegionFactory regionFactory = cache.CreateRegionFactory(RegionShortcut.CACHING_PROXY);

      IRegion<string, string> region = regionFactory.SetPoolName(poolName).Create<string, string>(regionName);

      Console.WriteLine("Created a generic Region.");

      // Put an Entry (Key and Value pair) into the Region using the IDictionary interface.
      region["Key1"] = "Value1";

      Console.WriteLine("Put the first Entry into the Region");

      // Put another Entry into the Region.
      region["123"] = "123";

      Console.WriteLine("Put the second Entry into the Region");

      // Get Entries back out of the Region.
      string result1 = region["Key1"];

      Console.WriteLine("Obtained the first Entry from the Region");

      string result2 = region["123"];

      Console.WriteLine("Obtained the second Entry from the Region");

      // Invalidate an Entry in the Region.
      region.Invalidate("Key1");

      Console.WriteLine("Invalidated the first Entry in the Region");

      // Destroy an Entry in the Region using the IDictionary interface.
      region.Remove("123");

      Console.WriteLine("Destroyed the second Entry in the Region");
    }
  
    static void Main(string[] args)
    {
      try
      {
        // Create a Geode Cache.
        CacheFactory cacheFactory = CacheFactory.CreateCacheFactory();

        Cache cache = cacheFactory.SetSubscriptionEnabled(true).Create();

        Console.WriteLine("Created the Geode Cache");

        //test on first distributem system
        TestDistributedSystem(cache, "localhost", 40404, "poolName1", "exampleRegion1");
        
        //test on second distributed system
        TestDistributedSystem(cache, "localhost", 40405, "poolName2", "exampleRegion2");

        // Close the Geode Cache.
        cache.Close();

        Console.WriteLine("Closed the Geode Cache");
      }
      // An exception should not occur
      catch (GeodeException gfex)
      {
        Console.WriteLine("DistributedSystem Geode Exception: {0}", gfex.Message);
      }
    }
  }
}
