//
//  FNKeychain.h
//  Tower
//
//  Created by Alexander Rinass on 01.02.10.
//  Copyright 2010 puremedia GmbH. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "FNKeychainConstants.h"

@class FNInternetPasswordKeychainItem;
@class FNGenericPasswordKeychainItem;
@interface FNKeychain : NSObject
@property (nonatomic, readonly) __attribute__((NSObject)) SecKeychainRef keychainRef;
@property (nonatomic, readonly) NSString *path;
@property (nonatomic, readonly) BOOL isDefaultKeychain;

+ (BOOL)supportsProtocol:(NSString *)protocol;

/** @name Finding Keychain Items */

/**
 Tries to find the internet password for the given URL in the current keychain.
 
 This method will extract all available components (protocol, username, host, port, path) from the
 URL and runs the actual find query with this information.
 */
+ (FNInternetPasswordKeychainItem *)findInternetPasswordForURL:(NSURL *)URL error:(NSError * __autoreleasing *)error;

/**
 Tries to find the generic password for the given parameters in the current keychain.
 */
+ (FNGenericPasswordKeychainItem *)findGenericPasswordItemForAccount:(NSString *)account service:(NSString *)service error:(NSError * __autoreleasing *)error;

/** @name Creating Objects */

/**
 Returns the user's default keychain.
 */
+ (FNKeychain *)defaultKeychain;

/**
 Creates a Keychain object with the given reference.
 */
+ (FNKeychain *)keychainWithKeychainRef:(SecKeychainRef)aKeychain;

/**
 Creates a new Keychain with the given path and password.
 */
+ (FNKeychain *)keychainWithPath:(NSString *)path password:(NSString *)password error:(NSError * __autoreleasing *)error;

/**
 Creates a new Keychain object with the given reference.
 
 If `NULL` is passed as reference, the user's default keychain is used.
 */
- (FNKeychain *)initWithKeychainRef:(SecKeychainRef)aKeychain;

/** @name Finding Keychain Items */

- (FNInternetPasswordKeychainItem *)findInternetPasswordForURL:(NSURL *)URL error:(NSError * __autoreleasing *)error;
- (NSArray *)findAllInternetPasswordsForURL:(NSURL *)URL error:(NSError * __autoreleasing *)error;
- (NSArray *)findAllInternetPasswords:(NSError * __autoreleasing *)error;

- (NSArray *)findAllGenericPasswords:(NSError * __autoreleasing *)error;
- (FNGenericPasswordKeychainItem *)findGenericPasswordItemForAccount:(NSString *)account service:(NSString *)service error:(NSError * __autoreleasing *)error;

/** @name Adding Keychain Items */

- (FNInternetPasswordKeychainItem *)addInternetPasswordWithURL:(NSURL *)URL password:(NSString *)password error:(NSError * __autoreleasing *)error;
- (FNInternetPasswordKeychainItem *)createOrUpdateInternetPasswordWithURL:(NSURL *)URL password:(NSString *)password error:(NSError * __autoreleasing *)error;
- (FNGenericPasswordKeychainItem *)addGenericPasswordWithAccount:(NSString *)account service:(NSString *)service password:(NSString *)password error:(NSError * __autoreleasing *)error;
- (FNGenericPasswordKeychainItem *)createOrUpdateGenericPasswordWithAccount:(NSString *)account service:(NSString *)service password:(NSString *)password error:(NSError * __autoreleasing *)error;

/** @name Deleting the Current Keychain */

/**
 Deletes the referenced keychain file.
 
 The user's default keychain cannot be deleted and will raise an exception if tried.
 */
- (BOOL)destroy:(NSError * __autoreleasing *)error;

@end
