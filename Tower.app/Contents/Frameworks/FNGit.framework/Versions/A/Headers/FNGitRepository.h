//
//  FNGitRepository.h
//  FNGit
//
//  Created by Alexander Rinass on 12.01.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@class FNGitConfig;
@class FNGitIgnores;
@class FNGitIndex;
@interface FNGitRepository : NSObject
@property (nonatomic, readonly) NSURL *fileURL;
@property (nonatomic, readonly) NSString *path;
@property (nonatomic, readonly) NSString *gitDirectoryPath;
@property (nonatomic, readonly) NSString *workingTreeDirectoryPath;
@property (nonatomic, readonly) NSString *name;
@property (nonatomic, readonly, getter = isBare) BOOL bare;
@property (nonatomic, readonly, getter = isValid) BOOL valid;
@property (nonatomic, readonly, getter = isDetachedWorkingTree) BOOL detachedWorkingTree;
@property (nonatomic, readonly) FNGitConfig *config;
@property (nonatomic, readonly) FNGitIgnores *ignores;
@property (nonatomic, readonly) FNGitIgnores *excludes;
@property (nonatomic, readonly) FNGitIndex *index;

#pragma mark - Checking a Path for a Git Repository

/**
 Wether or not the path belongs to a Git repository.
 
 Note that it is _belongs_ as any subdirectory of a Git repository will pass the
 check not just the root repository path.
 */
+ (BOOL)isGitRepositoryAtPath:(NSString *)path;

#pragma mark - Retrieving the Absolute Root Repository Path for a Git Repository

/**  
 Returns the root path of a Git repository in case the given path is a 
 subdirectory of a Git repository. A non-bare repository will return the working 
 tree directory. 
 
 Returns `nil` if the given path does not belong to a Git repository.
 */
+ (NSString *)rootPathForRepositoryAtPath:(NSString *)path;

#pragma mark - Creating a new Git Repository

/** 
 Initializes a new Git repository at the given path with the given options.
 
 Returns `nil` if the repository could not be created. If an `error` reference
 was passed it will contain the error.
 */
+ (id)createRepositoryAtPath:(NSString *)path options:(NSDictionary *)options error:(NSError * __autoreleasing *)error;

#pragma mark - Factory Methods

+ (id)repositoryWithPath:(NSString *)path;

#pragma mark - Initialization

- (id)initWithPath:(NSString *)path;

#pragma mark - Querying Repository Information

/**
 Wether or not the repository is completely empty (no refs at all).
 */
- (BOOL)isEmpty;

- (BOOL)isGitSVNRepository;

- (NSString *)HEADRefName;
- (NSString *)HEADRevision;

#pragma mark - Retrieving Paths to Git Directory Components

- (NSString *)configFilePath;
- (NSString *)HEADFilePath;
- (NSString *)cherryPickHEADFilePath;
- (NSString *)mergeHEADFilePath;
- (NSString *)rebaseDirectoryPath;
- (NSString *)descriptionPath;
- (NSString *)defaultIgnoresPath;
- (NSString *)defaultExcludesPath;
- (NSString *)mergeCommitMessagePath;
- (NSString *)squashCommitMessagePath;
- (NSString *)submodulesFilePath;
- (NSString *)clonedSubmodulesDirectory;
- (NSString *)SVNDirectoryPath;
- (NSString *)SVNMetadatapath;

#pragma mark - Retrieving and Setting Repository Description

/**
 Returns the description of the repository (`.git/description`).
 
 Returns `nil` if the description could not be retrieved. If an `error`
 reference was passed it will contain the error.
 */
- (NSString *)description:(NSError * __autoreleasing *)error;

/**
 Updates the description of the repository (`.git/description`) with the given
 value.
 
 Returns `NO` if the description could not be updated. If an `error`
 reference was passed it will contain the error.
 */
- (BOOL)setDescription:(NSString *)newDescription error:(NSError * __autoreleasing *)error;

@end
