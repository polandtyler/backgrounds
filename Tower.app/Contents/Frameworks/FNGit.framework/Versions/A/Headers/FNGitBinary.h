//
//  FNGitBinary.h
//  FNGit
//
//  Created by Alexander Rinass on 06.10.09.
//  Copyright 2009 puremedia. All rights reserved.
//
//  Represents a Git Command Line Binary. 
//

#import <Foundation/Foundation.h>

/**
 Represents a Git binary.
 */

@interface FNGitBinary : NSObject

/**
 The path to the Git binary.
 */
@property (nonatomic, readonly) NSString *path;

/**
 The path to the base directory that holds all Git subcommands.
 */
@property (nonatomic, readonly) NSString *libexecPath;
@property (nonatomic, readonly) NSString *perlLibraryPath;
@property (nonatomic, readonly) NSString *templatesDirectoryPath;
@property (nonatomic, readonly) NSString *version;
@property (nonatomic, readonly, getter = isValid) BOOL valid;
@property (nonatomic) NSArray *additionalPaths;

#pragma mark - Setting and Retrieving the Default Git Binary

/** @name Setting and Retrieving the Default Git Binary */

/**
 Sets the default Git binary.
 */
+ (void)setDefaultGitBinary:(id)gitBinary;

/**
 Returns the default Git binary as set by `setDefaultGitBinary:`.
 
 If no Git binary has been set, it will return the system Git binary.
 */
+ (id)defaultGitBinary;

#pragma mark - Retrieving the Minimum Version Requirement

/** @name Retrieving the Minimum Version Requirement */

/**
 Returns the minimum version that is required to power the FNGit library.
 */
+ (NSString *)minimumVersionRequirement;

#pragma mark - Validating a Git Binary

/** @name Validating a Git Binary */

/**
 Wether or not the binary at the given path is a Git binary.
 */
+ (BOOL)isGitBinaryAtPath:(NSString *)path;

#pragma mark - Factory Methods

/** @name Factory Methods */

+ (id)gitBinaryWithPath:(NSString *)path;
+ (id)gitBinaryWithPath:(NSString *)path libexecPath:(NSString *)libexecPath;

#pragma mark - Initializing

/** @name Initializing */

- (id)initWithPath:(NSString *)path;
- (id)initWithPath:(NSString *)path libexecPath:(NSString *)libexecPath;

@end
