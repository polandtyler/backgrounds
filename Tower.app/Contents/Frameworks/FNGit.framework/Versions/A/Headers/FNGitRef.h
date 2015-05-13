//
//  FNGitRef.h
//  FNGit
//
//  Created by Alexander Rinass on 06.12.10.
//  Copyright 2010 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FNGitCommitish.h"
#import "FNGitDefines.h"

@class FNGitCommit;
@protocol FNGitRef <NSObject, FNGitCommitIsh>
@property (nonatomic, readonly) NSString *fullRefName;
@property (nonatomic, readonly) NSString *refName;
@property (nonatomic, readonly) NSString *commitHash;
@property (nonatomic, readonly) FNGitCommit *commit;
@end

@class FNGitRepository;
@class FNGitCommit;
@interface FNGitRef : NSObject <FNGitRef>
@property (nonatomic, weak, readonly) FNGitRepository *repository;
@property (nonatomic, readonly) NSString *fullRefName;
@property (nonatomic, readonly) NSString *refName;
@property (nonatomic, readonly) NSString *commitHash;
//@property (nonatomic, readonly) NSString *treeHash;
@property (nonatomic, readonly) FNGitCommit *commit;
//@property (nonatomic, readonly) FNGitTree *tree;
@property (nonatomic, readonly) FNGitRefType refType;
@property (nonatomic, readonly, getter = isBranchRefType) BOOL branchRefType;
@property (nonatomic, readonly, getter = isRemoteBranchRefType) BOOL remoteBranchRefType;
@property (nonatomic, readonly, getter = isTagRefType) BOOL tagRefType;
@property (nonatomic, readonly, getter = isStashRefType) BOOL stashRefType;
@property (nonatomic, readonly, getter = isHeadRef) BOOL headRef;

#pragma mark - Determining the Type of a Ref Name

+ (FNGitRefType)refTypeForRefName:(NSString *)refName;

#pragma mark - Validating a Ref Name 

+ (BOOL)isValidRefName:(NSString *)refName;

#pragma mark - Normalizing and Denormalizing Ref Names

/**
 Normalizes a given ref name by always returning the full ref name by prefixing
 `refs/[heads|remotes|tags]/` if it is missing.
 */
+ (NSString *)makeFullRefName:(NSString *)refName refType:(FNGitRefType)refType;

/**
 Converts a given remote name and its local ref name to the local full remote 
 ref name, e.g. `origin` and `refs/heads/master` will return 
 `refs/remotes/origin/master`.
 
 If the remoteName is the special remote name `.`, the full local branch ref 
 name will be returned.
 */
+ (NSString *)makeFullRemoteRefNameWithRemoteName:(NSString *)remoteName refName:(NSString *)refName;

/**
 Converts a given local remote ref name to the full branch ref name on the 
 remote, e.g. `origin` and `refs/remotes/origin/master` will return
 `refs/heads/master`, which is the ref name on the remote `origin`.
 
 If the remoteName is the special remote name `.`, refName is only normalized to
 its full ref name if required.
 */
+ (NSString *)makeFullRefNameForRemoteWithName:(NSString *)remoteName refName:(NSString *)refName;

/**
 Denormalizes a given ref name by always returning the ref name without its
 `refs/[heads|remotes|tags]/` prefix if it exists. 
 */
+ (NSString *)makeRefName:(NSString *)refName refType:(FNGitRefType)refType;

#pragma mark - Retrieving Refs For a Repository

/**
 Returns all refs for the given repository or `nil` on error.
 
 If an error occurs, the error reference is set to an actual error object containing the error
 information. You may specify `nil` for this parameter if you do not want the error information.
 */
+ (NSArray *)allRefsForRepository:(FNGitRepository *)repository options:(NSDictionary *)options error:(NSError * __autoreleasing *)error;

/**
 Returns the ref for the given full ref name in the given repository or `nil` on error.
 
 If the ref could not be found, `nil` is returned and the error is also set to `nil`.
 
 If an error occurs, the error reference is set to an actual error object containing the error
 information. You may specify `nil` for this parameter if you do not want the error information.
 */
+ (id)refForFullRefName:(NSString *)fullRefName repository:(FNGitRepository *)repository options:(NSDictionary *)options error:(NSError * __autoreleasing *)error;

/**
 Returns the HEAD ref for the given repository or `nil` on error.
 
 If an error occurs, the error reference is set to an actual error object containing the error
 information. You may specify `nil` for this parameter if you do not want the error information.
 */
+ (id)headRefForRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

#pragma mark - Creating an Initial Ref For a Repository

/**
 Creates and returns a fake initial ref object named “maste“ for empty repositories or `nil` on
 error.
 
 The commit hash of the initial ref will be `nil`.
 
 If an error occurs, the error reference is set to an actual error object containing the error
 information. You may specify `nil` for this parameter if you do not want the error information.
 */
+ (id)initialRefFromHeadFileForRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

#pragma mark - Factory Methods

+ (id)refWithRepository:(FNGitRepository *)repository fullRefName:(NSString *)fullRefName commitHash:(NSString *)commitHash;

#pragma mark - Initialization

- (id)initWithRepository:(FNGitRepository *)repository fullRefName:(NSString *)fullRefName commitHash:(NSString *)commitHash;

#pragma mark - Retrieving the Associated Ref Object

/**
 Returns the associated ref object: local branch, remote branch or tag or `nil` on error.
 
 If an error occurs, the error reference is set to an actual error object containing the error
 information. You may specify `nil` for this parameter if you do not want the error information.
 */
- (id<FNGitRef>)refObject:(NSError * __autoreleasing *)error;

@end
