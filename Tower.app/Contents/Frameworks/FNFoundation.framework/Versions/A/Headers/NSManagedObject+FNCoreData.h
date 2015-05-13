//
//  NSManagedObject+FNCoreData.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 22.02.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <CoreData/CoreData.h>

@interface NSManagedObject (FNCoreData)

/** @name Retrieving Entity Information */

+ (NSString *)entityName;

/** @name Creating Managed Objects */

+ (instancetype)managedObjectWithObjectID:(NSManagedObjectID *)objectID inManagedObjectContext:(NSManagedObjectContext *)managedObjectContext;
+ (instancetype)createInManagedObjectContext:(NSManagedObjectContext *)managedObjectContext;
+ (instancetype)createInManagedObjectContext:(NSManagedObjectContext *)managedObjectContext attributes:(NSDictionary *)attributes;
- (instancetype)initWithManagedObjectContext:(NSManagedObjectContext *)managedObjectContext;

/** @name Refreshing ManagedObjects */

- (void)refreshMergingChanges:(BOOL)mergeChanges;

/** @name Obtaining Permanent Object ID */

- (BOOL)obtainPermanentID:(NSError * __autoreleasing *)error;

/** @name Deleting ManagedObjects */

- (void)destroy;
- (BOOL)isDestroyed;

/** @name Saving ManagedObjects */

- (BOOL)save:(NSError * __autoreleasing *)error;
- (BOOL)saveRecursive:(NSError * __autoreleasing *)error;

/** @name Batch Faulting */

- (void)batchFaultRelationshipsForKeyPaths:(NSArray *)relationshipKeyPaths;
- (void)batchFaultRelationshipForKeyPath:(NSString *)relationshipKeyPath;
- (void)batchFaultRelationshipNamed:(NSString *)relationshipName;

@end
