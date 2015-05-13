//
//  FNGitCommit.h
//  FNGit
//
//  Created by Alexander Rinass on 03.12.10.
//  Copyright 2010 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FNGitObject.h"
#import "FNGitCommitIsh.h"
#import "FNGitTreeIsh.h"

@class FNGitRepository;
@class FNGitActor;
@class FNGitTree;
@class FNGitCommitOutputParserResultItem;
@interface FNGitCommit : FNGitObject <FNGitCommitIsh, FNGitTreeIsh>
@property (nonatomic, readonly) NSString *commitHash;
@property (nonatomic, readonly) NSString *treeHash;
@property (nonatomic, readonly) NSArray *parentCommitHashes;
@property (nonatomic, readonly) FNGitActor *author;
@property (nonatomic, readonly) NSDate *authorDate;
@property (nonatomic, readonly) FNGitActor *committer;
@property (nonatomic, readonly) NSDate *committerDate;
@property (nonatomic, readonly) NSString *subject;
@property (nonatomic, readonly) NSString *body;
@property (nonatomic, readonly) NSString *message;
@property (nonatomic, readonly) NSArray *refs;
@property (nonatomic, readonly) NSUInteger topoOrder;
@property (nonatomic, readonly, getter = isMergeCommit) BOOL mergeCommit;
@property (nonatomic, readonly, getter = isRootCommit) BOOL rootCommit;
@property (nonatomic, readonly, getter = isSVNCommit) BOOL SVNCommit;
@property (nonatomic, readonly) NSString *SVNRepositoryUUID;
@property (nonatomic, readonly) NSString *SVNRepositoryURL;
@property (nonatomic, readonly) NSString *SVNRevision;
@property (nonatomic, readonly) FNGitTree *tree;

#pragma mark - Counting Commits For a Repository

+ (NSUInteger)countAllCommitsForRevisions:(NSArray *)revisions filePaths:(NSArray *)filePaths inRepository:(FNGitRepository *)repository options:(NSDictionary *)options error:(NSError * __autoreleasing *)error;

#pragma mark - Retrieving Commits For a Repository

/**
 Returns a single commit by commit hash.
 */
+ (id)commitForCommitHash:(NSString *)commitHash inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

+ (NSArray *)allCommitsForRevisions:(NSArray *)revisions filePaths:(NSArray *)filePaths inRepository:(FNGitRepository *)repository options:(NSDictionary *)options error:(NSError * __autoreleasing *)error;

/**
 Returns all commits that revision branch B has but not revision branch A.
 
 This is equals the "revA..revB" Git syntax.
 */
+ (NSArray *)allCommitsFromRevision:(NSString *)revision toRevision:(NSString *)otherRevision inRepository:(FNGitRepository *)repository options:(NSDictionary *)options error:(NSError * __autoreleasing *)error;

/**
 Returns all commits for revision A and B that are not on both branches.
 
 This is equals the "revA...revB" Git syntax.
 */
+ (NSArray *)allCommitsByComparingRevision:(NSString *)revision withRevision:(NSString *)otherRevision inRepository:(FNGitRepository *)repository options:(NSDictionary *)options error:(NSError * __autoreleasing *)error;

+ (NSArray *)allCommitHashesFromRevision:(NSString *)startRevision toRevision:(NSString *)endRevision inRepository:(FNGitRepository *)repository options:(NSDictionary *)options error:(NSError * __autoreleasing *)error;
+ (NSArray *)allCommitHashesByComparingRevision:(NSString *)revision withRevision:(NSString *)otherRevision inRepository:(FNGitRepository *)repository options:(NSDictionary *)options error:(NSError * __autoreleasing *)error;
+ (NSArray *)allCommitHashesForRevisions:(NSArray *)revisions filePaths:(NSArray *)filePaths inRepository:(FNGitRepository *)repository options:(NSDictionary *)options error:(NSError * __autoreleasing *)error;

#pragma mark - Factory Methods

+ (id)commitWithRepository:(FNGitRepository *)repository commitObject:(FNGitCommitOutputParserResultItem *)commitObject;

+ (id)commitWithRepository:(FNGitRepository *)repository commitHash:(NSString *)commitHash treeHash:(NSString *)treeHash parentCommitHashes:(NSArray *)parentCommitHashes author:(FNGitActor *)author authorDate:(NSDate *)authorDate committer:(FNGitActor *)committer committerDate:(NSDate *)committerDate message:(NSString *)message;

#pragma mark - Initialization

- (id)initWithRepository:(FNGitRepository *)repository commitHash:(NSString *)commitHash treeHash:(NSString *)treeHash parentCommitHashes:(NSArray *)parentCommitHashes author:(FNGitActor *)author authorDate:(NSDate *)authorDate committer:(FNGitActor *)committer committerDate:(NSDate *)committerDate message:(NSString *)message;

@end
