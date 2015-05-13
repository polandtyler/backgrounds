//
//  FNGitSubmodule.h
//  FNGit
//
//  Created by Alexander Rinass on 14.01.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FNGitSubmoduleOptions.h"
#import "FNGitDefines.h"
#import "FNGitCommitish.h"

/**
 Some settings can be overridden by the local config. The values on the 
 submodule are the effective (config) values.
 */

@class FNGitRepository;
@class FNGitCommit;
@class FNGitRemote;
@class FNGitSubmoduleConfig;
@interface FNGitSubmodule : NSObject <FNGitCommitIsh>
@property (nonatomic, weak, readonly) FNGitRepository *repository;
@property (nonatomic, readonly) NSString *name;
@property (nonatomic, readonly) NSString *path;
@property (nonatomic, readonly) NSString *URL;
@property (nonatomic, readonly) NSString *commitHash;
@property (nonatomic, readonly) NSString *describe;

/**
 The `dirty` flag returns wether or not the submodule contains lcoal 
 modifications. The value is always loaded with any ignore-submodules
 config setting overridden to return all kinds of modifications.
 */
@property (nonatomic, readonly, getter = isDirty) BOOL dirty;

@property (nonatomic, readonly) FNGitSubmoduleStatus status;
@property (nonatomic, readonly) FNGitSubmoduleStatusIgnoreMode statusIgnoreMode;
@property (nonatomic, readonly) FNGitSubmoduleUpdateStrategy updateStrategy;
@property (nonatomic, readonly) FNGitSubmoduleFormat layoutFormat;
@property (nonatomic, readonly) BOOL recursesSubmodulesOnFetch;
@property (nonatomic, readonly) NSString *upstreamBranch;
@property (nonatomic, readonly) FNGitSubmoduleConfig *config;
@property (nonatomic, readonly) FNGitSubmoduleConfig *localConfig;

/** @name Getting Submodules for a Repository */

+ (NSArray *)allSubmoduleNamesForRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;
+ (NSArray *)allSubmodulesForRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;
+ (id)submoduleForName:(NSString *)submoduleName repository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

/** @name Removing Submodules from a Repository */

+ (BOOL)removeSubmoduleAtPath:(NSString *)submodulePath inRepository:(FNGitRepository *)repository options:(FNGitRemoveSubmoduleOptions)options error:(NSError * __autoreleasing *)error;

/** @name Creating Submodule Objects */

+ (id)submoduleWithRepository:(FNGitRepository *)repository path:(NSString *)path;
- (id)initWithRepository:(FNGitRepository *)repository path:(NSString *)path;

/** @name Getting the Current Commit */

- (FNGitCommit *)commit;

/** @name Getting the Origin Remote */

- (FNGitRemote *)originRemote;

/** @name Getting the Submodule's Repository */

- (FNGitRepository *)submoduleRepository;

@end
