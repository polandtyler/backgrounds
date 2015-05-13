//
//  FNGitDiff.h
//  FNGit
//
//  Created by Alexander Rinass on 14.01.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FNGitDiffChunk.h"
#import "FNGitObject.h"
#import "FNGitDefines.h"

@class FNGitRepository;
@interface FNGitDiff : NSObject
@property (nonatomic, weak, readonly) FNGitRepository *repository;
@property (nonatomic, readonly) NSString *rawDiff;
@property (nonatomic, readonly) NSString *filePath;
@property (nonatomic, readonly) NSString *oldFilePath;
@property (nonatomic, readonly) NSArray *extendedHeaders;
@property (nonatomic, readonly) NSArray *chunks;
@property (nonatomic, readonly) BOOL isBinary;
@property (nonatomic, readonly) BOOL isCombinedDiff;
@property (nonatomic, readonly) NSUInteger totalChunks;
@property (nonatomic, readonly) FNGitFileStatus fileStatus;
@property (nonatomic, readonly) NSUInteger fileStatusSimilarityIndex;
@property (nonatomic, readonly) NSString *objectHash;
@property (nonatomic, readonly) NSString *originalObjectHash;
@property (nonatomic, readonly) NSArray *originalObjectHashes;
@property (nonatomic, readonly) FNGitFileMode fileMode;
@property (nonatomic, readonly) FNGitFileMode originalFileMode;
@property (nonatomic, readonly) NSArray *originalFileModes;
@property (nonatomic, readonly) NSUInteger linesAdded;
@property (nonatomic, readonly) NSUInteger linesDeleted;
@property (nonatomic, readonly) BOOL isFileStatusAdded;
@property (nonatomic, readonly) BOOL isFileStatusDeleted;
@property (nonatomic, readonly) BOOL isFileStatusModified;
@property (nonatomic, readonly) BOOL isFileStatusRenamed;
@property (nonatomic, readonly) BOOL isFileStatusCopied;
@property (nonatomic, readonly) NSString *header;

#pragma mark - Generating Diffs

/**
 Returns all diffs for a given commit allDiffsByComparingd to its ancestor(s).
 
 If the commit is a merge commit, no commit will be produced (which is also the
 Git default) unless you pass in the option to show merge commits.
 
 Returns `nil` if the revision could not be allDiffsByComparingd to its ancestor(s). If an
 `error` reference was passed it will contain the error.
 */
+ (NSArray *)allDiffsByComparingRevisionWithAncestorForRevision:(NSString *)aRevision filePaths:(NSArray *)arrayOfFilePaths repository:(FNGitRepository *)repository options:(NSDictionary *)options error:(NSError * __autoreleasing *)error;

/**
 Compares two revisions and returns the differences.
 
 You can also create merge diffs with this method by passing in the merge commit
 hash and all parent commit hashes. This will give you the same output which
 `git log -p -m -c` gives.
 
 Returns `nil` if the given revisions could not be allDiffsByComparingd. If an `error` 
 reference was passed it will contain the error.
 */
+ (NSArray *)allDiffsByComparingRevisions:(NSArray *)arrayOfRevisions forFilePaths:(NSArray *)arrayOfFilePaths repository:(FNGitRepository *)repository options:(NSDictionary *)options error:(NSError * __autoreleasing *)error;

/**
 Compares the current working tree with the index.
 
 This will give you diffs for unstaged vs. staged changes.
 
 Returns `nil` if the comparison fails. If an `error` reference was passed it
 will contain the error.
 */
+ (NSArray *)allDiffsByComparingWorkingTreeWithIndexWithForFilePaths:(NSArray *)arrayOfFilePaths repository:(FNGitRepository *)repository options:(NSDictionary *)options error:(NSError * __autoreleasing *)error;


+ (NSArray *)allDiffsByComparingWorkingTreeWithRevision:(NSString *)aRevision forFilePaths:(NSArray *)arrayOfFilePaths repository:(FNGitRepository *)repository options:(NSDictionary *)options error:(NSError * __autoreleasing *)error;

/**
 Compares the index with the current base revision (`HEAD`).
 
 This will give you diffs for staged vs. base changes.
 
 Returns `nil` if the comparison fails. If an `error` reference was passed it
 will contain the error.
 */
+ (NSArray *)allDiffsByComparingIndexWithBaseForFilePaths:(NSArray *)arrayOfFilePaths repository:(FNGitRepository *)repository	options:(NSDictionary *)options error:(NSError * __autoreleasing *)error;

/**
 Compares the index with another revision.
 
 Returns `nil` if the comparison fails. If an `error` reference was passed it
 will contain the error.
 */
+ (NSArray *)allDiffsByComparingIndexWithRevision:(NSString *)aRevision forFilePaths:(NSArray *)arrayOfFilePaths repository:(FNGitRepository *)repository options:(NSDictionary *)options error:(NSError * __autoreleasing *)error;

+ (id)diffByComparingBlob:(NSString *)aBlobHash withBlob:(NSString *)anotherBlobHash forRepository:(FNGitRepository *)repository options:(NSDictionary *)options error:(NSError * __autoreleasing *)error;

#pragma mark - Creating Patches for Chunks

- (NSString *)patchForChunkAtIndex:(NSUInteger)aChunkIndex;
- (NSString *)patchForChunkAtIndex:(NSUInteger)aChunkIndex linesWithIndexes:(NSIndexSet *)linesIndexes recalculateLineNumbers:(BOOL)recalculateLineNumbers;

#pragma mark - Comparing to Another Diff

- (BOOL)isEqualToDiff:(FNGitDiff *)otherDiff;

@end
