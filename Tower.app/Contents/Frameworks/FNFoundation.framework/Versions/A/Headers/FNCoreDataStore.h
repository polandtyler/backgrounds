//
//  FNCoreDataStore.h
//  FNFoundation
//
//  Created by Alexander Rinass on 17/03/15.
//  Copyright (c) 2015 Fournova GmbH. All rights reserved.
//

#import <CoreData/CoreData.h>
#import "FNCoreDataStoreManager.h"
#import "FNCoreDataStoreContextManager.h"
#import "FNCoreDataStoreDefaults.h"
#import "FNCoreDataStoreObserver.h"
#import "NSManagedObjectContext+FNCoreDataStore.h"
#import "NSManagedObject+FNCoreDataStore.h"
#import "NSManagedObject+FNCoreDataStoreFetching.h"

@interface FNCoreDataStore : NSObject
@property (nonatomic, copy, readonly) NSString *name;
@property (nonatomic, readonly) NSURL *managedObjectModelURL;
@property (nonatomic, readonly) NSURL *storeURL;
@property (nonatomic, copy, readonly) NSString *storeType;
@property (nonatomic, copy, readonly) NSDictionary *storeOptions;
@property (nonatomic, readonly) NSManagedObjectModel *managedObjectModel;
@property (nonatomic, readonly) NSPersistentStoreCoordinator *persistentStoreCoordinator;
@property (nonatomic, readonly) NSManagedObjectContext *persistentStoreManagedObjectContext;
@property (nonatomic, readonly) NSManagedObjectContext *mainManagedObjectContext;
@property (nonatomic, readonly) NSDictionary *allManagedObjectContextsByName;
@property (nonatomic, readonly) NSArray *allManagedObjectContexts;
@property (nonatomic, readonly, getter=isInitialized) BOOL initialized;

/** @name Getting Managed Stores */

+ (instancetype)defaultStore;
+ (instancetype)sharedStoreForName:(NSString *)name;

/** @name Creating CoreDataStore Objects */

+ (instancetype)defaultStoreWithInMemoryStoreType;
+ (instancetype)defaultStoreWithXMLStoreType;
+ (instancetype)defaultStoreWithSqliteStoreType;

+ (instancetype)storeWithManagedObjectModelURL:(NSURL *)managedObjectModelURL storeType:(NSString *)storeType storeURL:(NSURL *)storeURL storeOptions:(NSDictionary *)options;
- (instancetype)initWithManagedObjectModelURL:(NSURL *)managedObjectModelURL storeType:(NSString *)storeType storeURL:(NSURL *)storeURL storeOptions:(NSDictionary *)options;

/** @name Uninitializing the Store */

- (BOOL)initialize:(NSError *__autoreleasing *)error;
- (void)uninitialize;

/** @name Deleting the Store File */

- (BOOL)deleteStoreFile:(NSError * __autoreleasing *)error;

/** @name Rebuilding the Store */

- (BOOL)rebuild:(NSError * __autoreleasing *)error;

/** @name Managing ManagedObjectContexts */

- (NSManagedObjectContext *)managedObjectContextForName:(NSString *)name;
- (void)setManagedObjectContext:(NSManagedObjectContext *)managedObjectContext forName:(NSString *)name;
- (void)removeManagedObjectContextForName:(NSString *)name;

/** @name Observing ManagedObjectContexts for Changes */

- (void)addObserverForContext:(NSManagedObjectContext *)observedManagedObjectContext mergingChangesIntoContext:(NSManagedObjectContext *)targetManagedObjectContext;
- (void)removeObserverForContext:(NSManagedObjectContext *)observedManagedObjectContext mergingChangesIntoContext:(NSManagedObjectContext *)targetManagedObjectContext;

@end
