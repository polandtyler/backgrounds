//
//  FNCoreDataStoreContextManager.h
//  FNFoundation
//
//  Created by Alexander Rinass on 17/03/15.
//  Copyright (c) 2015 Fournova GmbH. All rights reserved.
//

#import <CoreData/CoreData.h>

extern NSString *const FNCoreDataStoreContextPersistentStoreContextName;
extern NSString *const FNCoreDataStoreContextMainContextName;

@class FNCoreDataStore;
@interface FNCoreDataStoreContextManager : NSObject
@property (nonatomic, readonly) NSDictionary *allManagedObjectContextsByName;
@property (nonatomic, readonly) NSArray *allManagedObjectContexts;

/** @name Managing ManagedObjectContexts */

- (NSManagedObjectContext *)managedObjectContextForName:(NSString *)name;
- (void)setManagedObjectContext:(NSManagedObjectContext *)managedObjectContext forName:(NSString *)name;
- (void)removeManagedObjectContextForName:(NSString *)name;
- (void)removeAllManagedObjectContexts;

@end
