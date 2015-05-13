//
//  FNSSHAgent.h
//  Tower
//
//  Created by Alexander Rinass on 21.09.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface FNSSHAgent : NSObject

#pragma mark - Retrieving the Default Mac OS X SSH Agent

+ (id)defaultAgent;

#pragma mark - Retrieving SSH Agent Status

- (BOOL)isServiceLoaded;
- (BOOL)isServiceRunning;

#pragma mark - Managing the SSH Agent Service

- (BOOL)loadService:(NSError **)error;
- (BOOL)unloadService:(NSError **)error;
- (BOOL)startService:(NSError **)error;
- (BOOL)stopService:(NSError **)error;

#pragma mark - Retrieving all SSH Keys Managed by the SSH Agent

- (NSArray *)allSSHKeys;

#pragma mark - Adding and Removing SSH Keys

- (BOOL)isSSHKeyAtFilePathAdded:(NSString *)aFilePath;
- (BOOL)addSSHKeyAtFilePath:(NSString *)aFilePath;
- (BOOL)removeSSHKeyForFilePath:(NSString *)aFilePath;

@end
