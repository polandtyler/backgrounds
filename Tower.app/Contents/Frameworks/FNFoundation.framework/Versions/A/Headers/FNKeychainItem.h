//
//  FNKeychainItem.h
//  FNFoundation
//
//  Created by Alexander Rinass on 09.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol FNKeychainItem <NSObject>
@required

/** @name Retrieving Keychain Item Sec Type Ref */

+ (CFTypeRef)keychainItemTypeRef;

@end

@class FNKeychain;
@interface FNKeychainItem : NSObject <FNKeychainItem>
@property (nonatomic, readonly) FNKeychain *keychain;
@property (nonatomic, readonly) SecKeychainItemRef keychainItemRef;
@property (nonatomic, readonly) CFTypeRef keychainItemTypeRef;
@property (nonatomic) NSString *label;
@property (nonatomic, readonly) BOOL isModified;

/** @name Querying Keychain Items */

+ (NSDictionary *)findKeychainItemWithAttributes:(NSDictionary *)attributes error:(NSError * __autoreleasing *)error;
+ (NSDictionary *)findKeychainItemWithAttributes:(NSDictionary *)attributes inKeychain:(FNKeychain *)keychain error:(NSError * __autoreleasing *)error;
+ (NSArray *)findAllKeychainItemsWithAttributes:(NSDictionary *)attributes inKeychain:(FNKeychain *)keychain error:(NSError * __autoreleasing *)error;

/** @name Creating Objects */

- (id)initWithKeychain:(FNKeychain *)keychain attributes:(NSDictionary *)attributes;

/** @name Setting And Retrieving Keychain Item Attributes */

- (id)objectForKey:(id)key;
- (void)setObject:(id)object forKey:(id)key;

/** @name Saving And Deleting an Item */

- (BOOL)save:(NSError * __autoreleasing *)error;
- (BOOL)destroy:(NSError * __autoreleasing *)error;

@end
