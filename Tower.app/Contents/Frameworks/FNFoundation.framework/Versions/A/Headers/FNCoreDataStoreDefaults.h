//
//  FNCoreDataStoreDefaults.h
//  FNFoundation
//
//  Created by Alexander Rinass on 17/03/15.
//  Copyright (c) 2015 Fournova GmbH. All rights reserved.
//

#import <CoreData/CoreData.h>

/**
 The class determines defaults when creating default CoreDataStores.
 
 The default managed object model URL is determined by:
 
 `[defaultBundle URLForResource:defaultManagedObjectModelName withExtension:@"momd"]`
 
 The default store URL is determined by:
 
 `defaultStoreDirectoryURL/defaultStoreName.defaultStoreExtension`
 */
@interface FNCoreDataStoreDefaults : NSObject

/**
 The default bundle is the main bundle. This property may not be nil when
 creating default stores.
 
 For test cases, you need to set this manually.
 */
@property (nonatomic) NSBundle *defaultBundle;

/**
 The default managed object model name is the bundle name from
 `defaultBundle`.
 */
@property (nonatomic, copy) NSString *defaultManagedObjectModelName;

/**
 The default store name is the bundle name from `defaultBundle`.
 */
@property (nonatomic, copy) NSString *defaultStoreName;

/**
 The default store directory URL is the application support directory, appended
 by the the bundle identifier from `defaultBundle`.
 */
@property (nonatomic) NSURL *defaultStoreDirectoryURL;

@property (nonatomic) id defaultMergePolicy;

/** @name Creating Instances */

+ (instancetype)sharedDefaults;

/** @name Managing Default Store Extensions */

- (NSString *)defaultExtensionForStoreType:(NSString *)storeType;
- (void)setDefaultExtension:(NSString *)fileExtension forStoreType:(NSString *)storeType;
- (NSDictionary *)allDefaultStoreExtensions;

/** @name Managing Default Store Options */

- (NSDictionary *)defaultStoreOptionsForStoreType:(NSString *)storeType;
- (void)setDefaultStoreOptions:(NSDictionary *)options forStoreType:(NSString *)storeType;;
- (NSDictionary *)allDefaultStoreOptions;

@end
