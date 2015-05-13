//
//  NSManagedObjectContext+FNCoreDataStore.h
//  FNFoundation
//
//  Created by Alexander Rinass on 18/03/15.
//  Copyright (c) 2015 Fournova GmbH. All rights reserved.
//

#import <CoreData/CoreData.h>

/**
 Convenience methods to access contexts provided by CoreDataStore.
 */
@interface NSManagedObjectContext (FNCoreDataStore)

/** @name Retrieving the Managed Object Contexts */

/**
 Returns the master context which is associated with the persistent store.
 */
+ (NSManagedObjectContext *)masterPersistentStoreContext;

/**
 Returns the main context that is used on the main queue
 (NSMainQueueConcurrencyType).
 
 Always use `performBlock:` or `performBlockAndWait:` to perform tasks on this
 context.
 */
+ (NSManagedObjectContext *)mainContext;

+ (NSManagedObjectContext *)masterBackgroundContext;

/**
 Returns a new child context of the main context for use in background tasks.
 
 Always use `performBlock:` or `performBlockAndWait:` to perform tasks on this
 context.
 */
+ (NSManagedObjectContext *)createBackgroundContextFromMainContext;

+ (NSManagedObjectContext *)createWorkerContextFromMasterBackgroundContext;

@end
