//
//  NSManagedObject+FNCoreDataFetching.h
//  FNFoundation
//
//  Created by Alexander Rinass on 18/03/15.
//  Copyright (c) 2015 Fournova GmbH. All rights reserved.
//

#import <CoreData/CoreData.h>

@interface NSManagedObject (FNCoreDataFetching)

/** @name Counting ManagedObjects */

+ (NSUInteger)countAllInManagedObjectContext:(NSManagedObjectContext *)managedObjectContext error:(NSError * __autoreleasing *)error;
+ (NSUInteger)countAllWithPredicate:(NSPredicate *)predicate inManagedObjectContext:(NSManagedObjectContext *)managedObjectContext error:(NSError * __autoreleasing *)error;

/** @name Fetching All ManagedObjects */

+ (NSArray *)fetchAllInManagedObjectContext:(NSManagedObjectContext *)managedObjectContext error:(NSError * __autoreleasing *)error;
+ (NSArray *)fetchAllWithSortDescriptors:(NSArray *)sortDescriptors inManagedObjectContext:(NSManagedObjectContext *)managedObjectContext error:(NSError * __autoreleasing *)error;
+ (NSArray *)fetchAllWithPredicate:(NSPredicate *)predicate sortDescriptors:(NSArray *)sortDescriptors inManagedObjectContext:(NSManagedObjectContext *)managedObjectContext error:(NSError * __autoreleasing *)error;
+ (NSArray *)fetchAllWithPredicate:(NSPredicate *)predicate sortDescriptors:(NSArray *)sortDescriptors limit:(NSUInteger)limit inManagedObjectContext:(NSManagedObjectContext *)managedObjectContext error:(NSError * __autoreleasing *)error;

/** @name Fetching Single ManagedObjects */

+ (instancetype)fetchFirstWithPredicate:(NSPredicate *)predicate inManagedObjectContext:(NSManagedObjectContext *)context error:(NSError * __autoreleasing *)error;
+ (instancetype)fetchFirstByAttribute:(NSString *)attribute withValue:(id)value inManagedObjectContext:(NSManagedObjectContext *)managedObjectContext error:(NSError * __autoreleasing *)error;

@end
