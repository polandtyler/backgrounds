//
//  FNCoreDataStoreManager.h
//  FNFoundation
//
//  Created by Alexander Rinass on 17/03/15.
//  Copyright (c) 2015 Fournova GmbH. All rights reserved.
//

#import <CoreData/CoreData.h>

@class FNCoreDataStore;
@interface FNCoreDataStoreManager : NSObject

/** @name Getting the Shared Instance */

+ (instancetype)sharedManager;

/** @name Getting and Setting the Default Store */

- (FNCoreDataStore *)defaultStore;
- (void)setDefaultStore:(FNCoreDataStore *)store;

/** @name Managing Store Instances */

- (FNCoreDataStore *)storeForName:(NSString *)name;
- (void)setStore:(FNCoreDataStore *)store forName:(NSString *)name;
- (void)removeStoreForName:(NSString *)name;

- (NSDictionary *)allStores;

@end

