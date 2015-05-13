//
//  FNGitDefines.h
//  FNGit
//
//  Created by Alexander Rinaß on 09.03.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

/** @name Object Types */

typedef NS_ENUM(NSUInteger, FNGitObjectType) {
    FNGitObjectTypeNone = 0,
	FNGitObjectTypeTree,
	FNGitObjectTypeBlob,
	FNGitObjectTypeCommit,
	FNGitObjectTypeTag
};

/** @name File Modes */

typedef NS_ENUM(NSUInteger, FNGitFileMode) {
    FNGitFileModeNone = 0,
	FNGitFileModeRegular = 0100644,
	FNGitFileModeExecutable = 0100775,
	FNGitFileModeSymbolicLink = 0120000,
	FNGitFileModeDirectory = 040000,
	FNGitFileModeSubmodule = 0160000
};

/** @name Ref Types */

typedef NS_ENUM(NSUInteger, FNGitRefType) {
    FNGitRefUndefinedType = 0,
	FNGitRefBranchType = 1,
	FNGitRefRemoteBranchType = 2,
	FNGitRefTagType = 3,
    FNGitRefStashType = 4
};

/** @name Index Stages */

typedef NS_ENUM(NSUInteger, FNGitIndexStage) {
    FNGitIndexStageDefault = 0,
	FNGitIndexStageBase = 1, // Merge conflict: base version of file
	FNGitIndexStageOurs = 2, // Merge conflict: our (local) version of file
	FNGitIndexStageTheirs = 3 // Merge conflict: their (remote) version of file
};

/** @name File Statuses */

typedef NS_ENUM(NSUInteger, FNGitFileStatus) {
    FNGitFileStatusNone = 0,
	FNGitFileStatusUntracked,
    FNGitFileStatusIgnored,
    FNGitFileStatusUnchanged,
	FNGitFileStatusAdded,
    FNGitFileStatusCopied,
    FNGitFileStatusModified,
	FNGitFileStatusRenamed,
    FNGitFileStatusTypeChanged,
    FNGitFileStatusDeleted,
	FNGitFileStatusUnmerged
};

/** @name Status Options */

typedef NS_ENUM(NSInteger, FNGitStatusUntrackedFilesMode) {
    FNGitStatusUntrackedFilesModeDefault = 0,
	FNGitStatusUntrackedFilesModeNone,
	FNGitStatusUntrackedFilesModeNormal,
	FNGitStatusUntrackedFilesModeFull
};

typedef NS_ENUM(NSInteger, FNGitStatusIgnoreSubmodulesMode) {
    FNGitStatusIgnoreSubmodulesModeDefault = 0,
	FNGitStatusIgnoreSubmodulesModeNone,
	FNGitStatusIgnoreSubmodulesModeUntracked,
	FNGitStatusIgnoreSubmodulesModeDirty,
    FNGitStatusIgnoreSubmodulesModeAll
};

/** @name Submodules */

typedef NS_ENUM(NSInteger, FNGitSubmoduleConfigType) {
	FNGitSubmoduleConfigTypeNone,
    FNGitSubmoduleConfigTypeDefault, // .gitmodules
	FNGitSubmoduleConfigTypeLocal // .git/config
};

typedef NS_OPTIONS(NSUInteger, FNGitAddSubmoduleOptions) {
	FNGitAddSubmoduleOptionNone = 0,
	FNGitAddSubmoduleOptionRecursive = 1UL << 0
};

typedef NS_OPTIONS(NSUInteger, FNGitUpdateSubmoduleOptions) {
	FNGitUpdateSubmoduleOptionNone = 0,
    FNGitUpdateSubmoduleOptionInit = 1UL << 0,
	FNGitUpdateSubmoduleOptionRecursive = 1UL << 1
};

typedef NS_OPTIONS(NSUInteger, FNGitRemoveSubmoduleOptions) {
    FNGitRemoveSubmoduleOptionDefaults = 0,
    FNGitRemoveSubmoduleOptionForce = 1UL << 0,
    FNGitRemoveSubmoduleOptionKeepWorkingTree = 1UL << 1,
    FNGitRemoveSubmoduleOptionRemoveGitDirectory = 1UL << 2
};

/** @name Exporter */

typedef NS_ENUM(NSInteger, FNGitArchiveFormat) {
    FNGitArchiveFormatNone = 0,
    FNGitArchiveFormatZIP,
    FNGitArchiveFormatTar
};

/** @name Diff Tool */

typedef NS_OPTIONS(NSUInteger, FNGitDiffToolOptions) {
    FNGitDiffToolOptionsDefaults = 0,
    FNGitDiffToolOptionDirectoryDiff = 1UL << 0,
    FNGitDiffToolOptionStaged = 1UL << 1
};

/** @name Tree Options */

typedef NS_OPTIONS(NSUInteger, FNGitTreeOptions) {
    FNGitTreeOptionDefaults = 0,
    FNGitTreeOptionRecursive = 1UL << 0,
    FNGitTreeOptionIncludeFileSize = 1UL << 1
};

/** @name Working Tree Options */

extern NSString *const FNGitWorkingTreeOptionIncludeUnchangedFiles;
extern NSString *const FNGitWorkingTreeOptionIncludeAssumeUnchangedFiles;
extern NSString *const FNGitWorkingTreeOptionIncludeIgnoredFiles;
extern NSString *const FNGitWorkingTreeOptionUntrackedFilesMode;
extern NSString *const FNGitWorkingTreeOptionIgnoreSubmodulesMode;
extern NSString *const FNGitWorkingTreeOptionRecursive;

/** @name Common Constants */

extern NSString *const FNGitHEADRevision;
extern NSString *const FNGitNullObjectHash;
extern NSString *const FNGitMasterBranchName;
extern NSString *const FNGitOriginRemoteName;
extern NSString *const FNGitLocalRemoteName;
extern NSString *const FNGitNullFile;

/** @name git-svn Constants */

extern NSString *const FNGitSVNOptionStandardDirectoryLayout;
extern NSString *const FNGitSVNOptionTrunkDirectories;
extern NSString *const FNGitSVNOptionBranchesDirectories;
extern NSString *const FNGitSVNOptionTagsDirectories;
