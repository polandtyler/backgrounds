//
//  NSManagedObject+FNCoreDataStore.h
//  FNFoundation
//
//  Created by Alexander Rinass on 18/03/15.
//  Copyright (c) 2015 Fournova GmbH. All rights reserved.
//

#import <CoreData/CoreData.h>

/**
 Convenience methods to create managed objects in the main context
 provided by CoreDataStore.
 */
@interface NSManagedObject (FNCoreDataStore)

/** @name Getting Existing Managed Objects in Main Context */

+ (instancetype)managedObjectWithObjectID:(NSManagedObjectID *)objectID;

/** @name Creating New Managed Objects in Main Context */

+ (instancetype)create;
+ (instancetype)createWithAttributes:(NSDictionary *)attributes;

/** @name Creating Managed Objects Without Managed Object Context */

+ (instancetype)createInMemory;
+ (instancetype)createInMemoryWithAttributes:(NSDictionary *)attributes;

@end
