//
//  FNGenericPasswordKeychainItem.h
//  FNFoundation
//
//  Created by Alexander Rinass on 09.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNPasswordKeychainItem.h"

@class FNKeychain;
@interface FNGenericPasswordKeychainItem : FNPasswordKeychainItem
// Represents the service associated with this item
@property (nonatomic, copy) NSString *service;

// Contains a user-defined attribute
@property (nonatomic, copy) NSData *genericData;

/** @name Finding Generic Password Items */

+ (NSArray *)findAllGenericPasswordItemsInKeychain:(FNKeychain *)keychain error:(NSError * __autoreleasing *)error;
+ (id)findGenericPasswordItemForAccount:(NSString *)account service:(NSString *)service error:(NSError * __autoreleasing *)error;
+ (id)findGenericPasswordItemForAccount:(NSString *)account service:(NSString *)service inKeychain:(FNKeychain *)keychain error:(NSError * __autoreleasing *)error;

/** @name Adding Generic Password Items */

+ (id)addGenericPasswordToKeychain:(FNKeychain *)keychain withAccount:(NSString *)account service:(NSString *)service password:(NSString *)password error:(NSError * __autoreleasing *)error;

/** @name Creating Objects */

+ (id)genericPasswordItemWithKeychain:(FNKeychain *)keychain account:(NSString *)account service:(NSString *)service password:(NSString *)password;

- (NSDictionary *)dictionaryRepresentation;

@end
