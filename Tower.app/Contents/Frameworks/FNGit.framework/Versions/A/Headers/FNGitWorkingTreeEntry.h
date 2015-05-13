//
//  FNGitWorkingTreeEntry.h
//  FNGit
//
//  Created by Alexander Rinass on 20.05.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import "FNGitFileEntry.h"

@class FNGitDiff;
@class FNGitBlob;
@class FNGitIndexEntry;
@class FNGitTreeEntry;
@class FNGitRepository;
@interface FNGitWorkingTreeEntry : FNGitFileEntry
@property (nonatomic, readonly) NSString *originalFilePath;
@property (nonatomic, readonly) NSString *absoluteFilePath;
@property (nonatomic, readonly) FNGitFileStatus currentStatus;
@property (nonatomic, readonly) FNGitFileStatus stagedStatus;
@property (nonatomic, readonly) FNGitIndexEntry *stagedVersion;
@property (nonatomic, readonly) FNGitTreeEntry *baseVersion;
@property (nonatomic, readonly) FNGitFileStatus unmergedOursStatus;
@property (nonatomic, readonly) FNGitFileStatus unmergedTheirsStatus;
@property (nonatomic, readonly) FNGitIndexEntry *unmergedBaseVersion;
@property (nonatomic, readonly) FNGitIndexEntry *unmergedOursVersion;
@property (nonatomic, readonly) FNGitIndexEntry *unmergedTheirsVersion;
@property (nonatomic, readonly, getter = isUnmergedFile) BOOL unmergedFile;
@property (nonatomic, readonly, getter = isAssumeUnchangedFile) BOOL assumeUnchangedFile;
@property (nonatomic, readonly, getter = isIgnoredFile) BOOL ignoredFile;
@property (nonatomic, readonly) BOOL hasLoadedIndexVersions;

/** @name Retrieving Working Tree Entries */

/**
 A convenience method to retrieve the same result as the default “git status“
 would.
 
 Note that this will override whatever the user has configured for the Git 
 config value `status.showUntrackedFiles` and use the Git default value `Normal`
 to enforce the default behaviour for untracked files.
 */
+ (NSArray *)changedWorkingTreeEntriesForRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

/**
 Retrieves all working tree entries for the given file path by default.
 
 Additional options can be passed in to filter the working tree entries.
 
 By default, this will return all files that are tracked by Git with additional
 information from “git status“, including all untracked files _independent_ of 
 what the user has configured for the Git config value 
 `status.showUntrackedFiles`.
 
 To get the same result as “git status“ on the CLI, you need to pass the
 options `FNGitWorkingTreeOptionShowModifiedFiles` and 
 `FNGitWorkingTreeOptionShowDefaultUntrackedFiles`. 
 */
+ (NSArray *)workingTreeEntriesForFilePath:(NSString *)filePath inRepository:(FNGitRepository *)repository options:(NSDictionary *)options error:(NSError * __autoreleasing *)error;

/**
 Retrieves the working tree entry at the given path.
 
 This will also return untracked or ignored working tree entries.
 */
+ (FNGitWorkingTreeEntry *)workingTreeEntryForFilePath:(NSString *)filePath inRepository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

/** @name Creating Working Tree Entries */

/**
 Creates a new working tree entry object.
 */
- (id)initWithRepository:(FNGitRepository *)repository filePath:(NSString *)filePath fileMode:(FNGitFileMode)fileMode leftStatus:(FNGitFileStatus)leftStatus rightStatus:(FNGitFileStatus)rightStatus;

/** @name Retrieving Diffs for the Working Tree Entry */ 

- (FNGitDiff *)compareWorkingTreeWithIndexWithOptions:(NSDictionary *)options error:(NSError * __autoreleasing *)error;
- (FNGitDiff *)compareIndexWithBaseWithOptions:(NSDictionary *)options error:(NSError * __autoreleasing *)error;
- (FNGitDiff *)compareUnmergedVersionsWithOptions:(NSDictionary *)options error:(NSError * __autoreleasing *)error;

/** @name Retrieving Blob Objects */

- (FNGitBlob *)blobForCurrentVersion:(NSError * __autoreleasing *)error;
- (FNGitBlob *)blobForStagedVersion:(NSError * __autoreleasing *)error;
- (FNGitBlob *)blobForBaseVersion:(NSError * __autoreleasing *)error;
- (FNGitBlob *)blobForUnmergedOursVersion:(NSError * __autoreleasing *)error;
- (FNGitBlob *)blobForUnmergedTheirsVersion:(NSError * __autoreleasing *)error;
- (FNGitBlob *)blobForUnmergedBaseVersion:(NSError * __autoreleasing *)error;

/** @name Comparing to Another WorkingTreeEntry */

- (BOOL)isEqualToWorkingTreeEntry:(FNGitWorkingTreeEntry *)object;

@end
