//
//  NSPersistentStoreCoordinator+FNCoreData.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 06.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <CoreData/CoreData.h>

@interface NSPersistentStoreCoordinator (FNCoreData)

+ (NSPersistentStoreCoordinator *)persistentStoreCoordinatorWithManagedObjectModel:(NSManagedObjectModel *)createManagedObjectModel storeType:(NSString *)storeType storeURL:(NSURL *)storeURL options:(NSDictionary *)options error:(NSError * __autoreleasing *)error;

@end
