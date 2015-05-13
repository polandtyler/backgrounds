//
//  FNGitSubmoduleManager.h
//  FNGit
//
//  Created by Alexander Rinass on 12.08.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FNGitDefines.h"

@class FNGitRepository;
@interface FNGitSubmoduleManager : NSObject
@property (nonatomic, readonly) FNGitRepository *repository;

/** @name Creating Submodule Loader Objects */

+ (id)managerWithRepository:(FNGitRepository *)repository;
- (id)initWithRepository:(FNGitRepository *)repository;

/** @name Adding New Submodules */

- (BOOL)canAddSubmoduleAtPath:(NSString *)filePath error:(NSError * __autoreleasing *)error;
- (BOOL)addSubmoduleWithURL:(NSString *)remoteURL atPath:(NSString *)path options:(FNGitAddSubmoduleOptions)options error:(NSError * __autoreleasing *)error;

/** @name Deleting Submodules */

- (BOOL)removeSubmoduleAtPath:(NSString *)submodulePath options:(FNGitRemoveSubmoduleOptions)options error:(NSError * __autoreleasing *)error;

/** @name Moving Submodules */

- (BOOL)moveSubmoduleWithPath:(NSString *)submodulePath toNewPath:(NSString *)newSubmodulePath error:(NSError * __autoreleasing *)error;

/** @name Updating Submodules */

- (BOOL)updateAllSubmodulesWithOptions:(FNGitUpdateSubmoduleOptions)options error:(NSError * __autoreleasing *)error;
- (BOOL)updateSubmoduleAtPath:(NSString *)submodulePath options:(FNGitUpdateSubmoduleOptions)options error:(NSError * __autoreleasing *)error;

/** @name Synchronizing Submodule URLs */

- (BOOL)synchronizeAllSubmoduleURLs:(NSError * __autoreleasing *)error;
- (BOOL)synchronizeURLForSubmoduleAtPath:(NSString *)submodulePath error:(NSError * __autoreleasing *)error;

/** @name Restoring Submodules */

- (BOOL)restoreSubmoduleAtPath:(NSString *)submodulePath error:(NSError * __autoreleasing *)error;

@end
