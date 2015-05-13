//
//  FNSSHKey.h
//  Tower
//
//  Created by Alexander Rinass on 21.09.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface FNSSHKey : NSObject {
@private
    NSString *privateKeyFilePath;
    NSString *publicKeyFilePath;
    NSString *type;
    NSString *privateKeyContents;
    NSString *publicKeyContents;
    NSString *comment;
    NSString *fingerprint;    
}
@property (retain, readonly) NSString *privateKeyFilePath;
@property (retain, readonly) NSString *publicKeyFilePath;
@property (retain, readonly) NSString *type;
@property (retain, readonly) NSString *privateKeyContents;
@property (retain, readonly) NSString *publicKeyContents;
@property (retain, readonly) NSString *comment;
@property (retain, readonly) NSString *fingerprint;
@property (readonly) BOOL isDSAType;
@property (readonly) BOOL isRSAType;

#pragma mark - Verifying SSH Keys

+ (BOOL)isSSHKeyAtFilePath:(NSString *)aFilePath;
+ (BOOL)isPrivateSSHKeyAtFilePath:(NSString *)aFilePath;
+ (BOOL)isPublicSSHKeyAtFilePath:(NSString *)aFilePath;

#pragma mark - Retrieving SSH Keys

+ (NSArray *)allSSHKeysForCurrentUser;
+ (NSArray *)allSSHKeysInDirectoryAtPath:(NSString *)aDirectoryPath;

#pragma mark - Generating SSH Keys

+ (id)SSHKeyByGeneratingNewRSAKeyAtPath:(NSString *)aFilePath;
+ (id)SSHKeyByGeneratingNewRSAKeyAtPath:(NSString *)aFilePath withComment:(NSString *)aComment;
+ (id)SSHKeyByGeneratingNewDSAKeyAtPath:(NSString *)aFilePath;
+ (id)SSHKeyByGeneratingNewDSAKeyAtPath:(NSString *)aFilePath withComment:(NSString *)aComment;

#pragma mark - Factory Methods

+ (id)SSHKeyFromPrivateKeyFileAtPath:(NSString *)aPrivateKeyFilePath;
+ (id)SSHKeyFromPublicKeyFileAtPath:(NSString *)aPublicKeyFilePath;
+ (id)SSHKeyFromPrivateKeyFileAtPath:(NSString *)aPrivateKeyFilePath publicKeyFileAtPath:(NSString *)aPublicKeyFilePath;

#pragma mark - Factory Methods

- (id)initWithPrivateKeyFilePath:(NSString *)aPrivateKeyFilePath;
- (id)initWithPublicKeyFilePath:(NSString *)aPublicKeyFilePath; 
- (id)initWithPrivateKeyFilePath:(NSString *)aPrivateKeyFilePath publicKeyFilePath:(NSString *)aPublicKeyFilePath; 

@end
