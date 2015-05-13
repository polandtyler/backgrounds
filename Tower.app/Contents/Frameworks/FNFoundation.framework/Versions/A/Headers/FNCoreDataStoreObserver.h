//
//  FNCoreDataStoreObserver.h
//  FNFoundation
//
//  Created by Alexander Rinass on 17/03/15.
//  Copyright (c) 2015 Fournova GmbH. All rights reserved.
//

#import <CoreData/CoreData.h>

@interface FNCoreDataStoreObserver : NSObject

- (void)addObserverForContext:(NSManagedObjectContext *)observedManagedObjectContext mergingChangesIntoContext:(NSManagedObjectContext *)targetManagedObjectContext;
- (void)removeObserverForContext:(NSManagedObjectContext *)observedManagedObjectContext mergingChangesIntoContext:(NSManagedObjectContext *)targetManagedObjectContext;
- (void)removeAllObserversForContext:(NSManagedObjectContext *)observedManagedObjectContext;

- (void)removeAllObservers;

@end
