//
//  NSManagedObjectContext+FNCoreData.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 06.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <CoreData/CoreData.h>

@interface NSManagedObjectContext (FNCoreData)

#if MAC_OS_X_VERSION_MIN_REQUIRED <= MAC_OS_X_VERSION_10_9
@property (nonatomic) NSString *name_;
#else
#warning Property backport for `NSManagedObjectContext` `name` no longer required
#endif

/** @name Saving Contexts Recursively */

- (BOOL)saveRecursive:(NSError *__autoreleasing *)error;

- (BOOL)obtainPermanentIDs:(NSError *__autoreleasing *)error;

@end
