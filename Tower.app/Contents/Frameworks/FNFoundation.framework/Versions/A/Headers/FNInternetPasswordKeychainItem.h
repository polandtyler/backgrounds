//
//  FNInternetPasswordKeychainItem.h
//  FNFoundation
//
//  Created by Alexander Rinass on 09.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNPasswordKeychainItem.h"
#import "FNKeychainConstants.h"

@class FNKeychain;
@interface FNInternetPasswordKeychainItem : FNPasswordKeychainItem
// Represents the Internet security domain
@property (nonatomic, copy) NSString *securityDomain;

// Contains the server's domain name or IP address
@property (nonatomic, copy) NSString *host;

// Denotes the protocol for this item
@property (nonatomic) FNKeychainProtocol protocol;

// Denotes the authentication scheme for this item
//@property (nonatomic, assign) AuthenticationType authenticationType;

// Represents an Internet port number
@property (nonatomic) NSNumber *port;

// Represents a path, typically the path component of the URL
@property (nonatomic, copy) NSString *path;

//+ (BOOL)isValidProtocolForInternetPassword:(NSString *)aProtocol;

/** @name Finding Internet Password Items */

/**
 Tries to find the internet password for the given URL in all keychains.
 
 This method will extract all available components (protocol, username, host, port, path) from the
 URL and runs the actual find query with this information.
 */
+ (id)findInternetPasswordForURL:(NSURL *)URL error:(NSError * __autoreleasing *)error;
+ (id)findInternetPasswordForURL:(NSURL *)URL inKeychain:(FNKeychain *)keychain error:(NSError * __autoreleasing *)error;
+ (NSArray *)findAllInternetPasswords:(NSError * __autoreleasing *)error;
+ (NSArray *)findAllInternetPasswordsInKeychain:(FNKeychain *)keychain error:(NSError * __autoreleasing *)error;
+ (NSArray *)findAllInternetPasswordsForURL:(NSURL *)URL error:(NSError * __autoreleasing *)error;
+ (NSArray *)findAllInternetPasswordsForURL:(NSURL *)URL inKeychain:(FNKeychain *)keychain error:(NSError * __autoreleasing *)error;

/** @name Adding Internet Password Items */

+ (id)addInternetPasswordToKeychain:(FNKeychain *)keychain withURL:(NSURL *)URL password:(NSString *)password error:(NSError * __autoreleasing *)error;

/** @name Creating Objects */

+ (id)internetPasswordWithKeychain:(FNKeychain *)keychain URL:(NSURL *)URL password:(NSString *)password;

- (NSDictionary *)dictionaryRepresentation;

@end
