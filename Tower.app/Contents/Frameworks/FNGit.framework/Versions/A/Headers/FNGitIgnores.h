//
//  FNGitIgnores.h
//  FNGit
//
//  Created by Alexander Rinass on 14.01.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@class FNGitRepository;
@interface FNGitIgnores : NSObject
@property (nonatomic, weak, readonly) FNGitRepository *repository;
@property (nonatomic, readonly) NSString *filePath;

#pragma mark - Retrieving Ignore Patterns

/**
 Retrieves all ignore patterns from the `.gitignores` file of the given
 repository.
 
 Returns `nil` if the ignore patterns could not be retrieved. If an `error` 
 reference was passed it will contain the error.
 */
+ (NSArray *)allIgnorePatternsFromDefaultIgnoresForRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

/**
 Retrieves all ignore patterns from the `.git/info/exclude` file of the given
 repository.
 
 Returns `nil` if the ignore patterns could not be retrieved. If an `error` 
 reference was passed it will contain the error.
 */
+ (NSArray *)allIgnorePatternsFromExcludeFileForRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

#pragma mark - Factory Methods

/**
 Returns an Ignores object for the `.gitignores` file of the given repository.
 */
+ (instancetype)defaultIgnoresForRepository:(FNGitRepository *)repository;

/**
 Returns an Ignores object for the `.git/info/exclude` file of the given repository.
 */
+ (instancetype)ignoresWithExcludeFileForRepository:(FNGitRepository *)repository;

/**
 Retrieves an ignores object for the given file.
 
 Can be used to create an ignores object for the path specified in `core.excludesfile`.
 */
+ (instancetype)ignoresWithFilePath:(NSString *)filePath;

#pragma mark - Initialization

- (instancetype)initWithRepository:(FNGitRepository *)repository filePath:(NSString *)filePath;

#pragma mark - Managing Ignore Patterns

/**
 Retrieves all ignore patterns from the file.
 */
- (NSArray *)allIgnorePatterns:(NSError * __autoreleasing *)error;

/**
 Retrieves raw ignore patterns from the file without removing comment lines.
 */
- (NSArray *)rawIgnorePatterns:(NSError * __autoreleasing *)error;

/**
 Sets the given ignore patterns for the current ignores file, replacing
 all existing ones.
 
 Returns `YES` if the ignore pattern were set or `NO` if there was an error.
 */
- (BOOL)setIgnorePatterns:(NSArray *)ignorePatterns error:(NSError * __autoreleasing *)error;

/**
 Adds the given ignore pattern to the current ignores file.
 
 Returns `YES` if the ignore pattern were successfully added or `NO` if
 there was an error.
 */
- (BOOL)addIgnorePattern:(NSString *)ignorePattern error:(NSError * __autoreleasing *)error;

/**
 Adds the given ignore patterns to the current ignores file.
 
 Returns `YES` if the ignore patterns were successfully added or
 `NO` if there was an error.
 */
- (BOOL)addIgnorePatterns:(NSArray *)ignorePatterns error:(NSError * __autoreleasing *)error;

/**
 Wether or not the given ignore pattern exists in the current
 ignores file.
 
 Returns `YES` if the ignore pattern exists and `NO` if it does
 not exist or if there was an error.
 */
- (BOOL)existsIgnorePattern:(NSString *)ignorePattern error:(NSError * __autoreleasing *)error;

/**
 Removes the given ignore pattern from the current ignores file.
 
 Returns `YES` if the ignore pattern could be removed or `NO` if 
 it did not exist or could not be removed for other reasons.
 */
- (BOOL)removeIgnorePattern:(NSString *)ignorePattern error:(NSError * __autoreleasing *)error;

/**
 Removes the given ignore patterns from the current ignores file.
 
 Returns `YES` if the ignore patterns could be removed or `NO` if
 they did not exist or could not be removed for other reasons.
 */
- (BOOL)removeIgnorePatterns:(NSArray *)ignorePatterns error:(NSError * __autoreleasing *)error;


@end
