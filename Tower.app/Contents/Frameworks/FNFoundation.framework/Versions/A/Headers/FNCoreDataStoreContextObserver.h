//
//  FNCoreDataStoreContextObserver.h
//  FNFoundation
//
//  Created by Alexander Rinass on 17/03/15.
//  Copyright (c) 2015 Fournova GmbH. All rights reserved.
//

#import <CoreData/CoreData.h>

@interface FNCoreDataStoreContextObserver : NSObject
@property (nonatomic, readonly) NSManagedObjectContext *managedObjectContext;
@property (nonatomic, readonly) id observer;
@property (nonatomic, readonly) NSSet *targetManagedObjectContexts;

+ (instancetype)contextObserverWithManagedObjectContext:(NSManagedObjectContext *)managedObjectContext observer:(id)observer;
- (instancetype)initWithManagedObjectContext:(NSManagedObjectContext *)managedObjectContext observer:(id)observer;

- (void)addTargetManagedObjectContext:(NSManagedObjectContext *)targetManagedObjectContext;
- (void)removeTargetManagedObjectContext:(NSManagedObjectContext *)targetManagedObjectContext;

@end
