//
//  NSManagedObject+FNCoreDataStoreFetching.h
//  FNFoundation
//
//  Created by Alexander Rinass on 18/03/15.
//  Copyright (c) 2015 Fournova GmbH. All rights reserved.
//

#import <CoreData/CoreData.h>

/**
 Convenience methods to count or fetch managed objects in the main context
 provided by CoreDataStore.
 */
@interface NSManagedObject (FNCoreDataStoreFetching)

/** @name Counting Managed Objects in Main Context */

+ (NSUInteger)countAll:(NSError * __autoreleasing *)error;
+ (NSUInteger)countAllWithPredicate:(NSPredicate *)predicate error:(NSError * __autoreleasing *)error;

/** @name Fetching Managed Objects in Main Context */

+ (NSArray *)fetchAll:(NSError * __autoreleasing *)error;
+ (NSArray *)fetchAllWithSortDescriptors:(NSArray *)sortDescriptors error:(NSError * __autoreleasing *)error;
+ (NSArray *)fetchAllWithPredicate:(NSPredicate *)predicate sortDescriptors:(NSArray *)sortDescriptors error:(NSError * __autoreleasing *)error;

+ (instancetype)fetchFirstWithPredicate:(NSPredicate *)predicate error:(NSError * __autoreleasing *)error;
+ (instancetype)fetchFirstByAttribute:(NSString *)attribute withValue:(id)value error:(NSError * __autoreleasing *)error;

@end
