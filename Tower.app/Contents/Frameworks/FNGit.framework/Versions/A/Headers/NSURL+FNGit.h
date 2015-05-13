//
//  NSURL+FNGit.h
//  FNGit
//
//  Created by Alexander Rinass on 30.06.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@interface NSURL (FNGit)

#pragma mark - Factory Methods

/**
 This will escape URL characters if required for absolute file paths.
 */
+ (id)URLWithGitURLString:(NSString *)aGitURLString;

#pragma mark - Accessing Git URL attributes

/**
 Returns the Git URL as a valid NSURL.
 
 This will transform any non-official URL-style (e.g. absolute path instead of file protocol,
 SCP syntax or git+ssh protocol) into an official URL.
 */
- (NSURL *)gitURL;
- (NSString *)gitURLString;

/**
 Returns the username for a Git URL.
 
 This basically returns what the method `user` of NSURL would return, but internally converts
 SCP-Style SSH-URLs to the `ssh://` scheme before calling the method, as NSURL does not recognize them.
 */
- (NSString *)gitURLUsername;

/**
 Returns the hostname for a Git URL.
 
 This basically returns what the method `host` of NSURL would return, but internally converts
 SCP-Style SSH-URLs to the `ssh://` scheme before calling the method, as NSURL does not recognize them.
 */
- (NSString *)gitURLHostname;

/**
 Returns the path for a Git URL.
 
 This basically returns what the method `path` of NSURL would return, but internally converts
 SCP-Style SSH-URLs to the `ssh://` scheme before calling the method, as NSURL does not recognize them.
 */
- (NSString *)gitURLPath;

/**
 Returns the protocol for a Git URL.
 
 This basically returns what the method `scheme` of NSURL would return, but also returns `ssh` for
 SCP-Style SSH-URLs, as NSURL does not recognize them.
 */
- (NSString *)gitURLProtocol;

#pragma mark - Detecting the URL Protocol

- (BOOL)isSVNSSHProtocol;
- (BOOL)isFileProtocol;
- (BOOL)isGitProtocol;
- (BOOL)isSSHProtocol;
- (BOOL)isHTTPProtocol;
- (BOOL)isHTTPSProtocol;
- (BOOL)isFTPProtocol;
- (BOOL)isFTPSProtocol;

#pragma mark - Validating the URL

- (BOOL)isValidGitURL;
- (BOOL)isValidGitURLProtocol;

#pragma mark - Detecting Read-Only Protocols for Git URLs

- (BOOL)isAnonymousProtocol;

#pragma mark - Detecting Git URLs Requiring Authentication

- (BOOL)requiresAuthentication;

@end
