//
//  FNGitHelpers.h
//  FNGit
//
//  Created by Alexander Rinass on 30.06.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FNFoundation/FNFoundation.h>
#import "FNGitDefines.h"

@class FNGitRepository;
@class FNGitRefSpec;

extern FNGitObjectType FNGitObjectTypeFromString(NSString *objectTypeString);
extern NSString *FNGitStringForObjectType(FNGitObjectType objectType);

extern FNGitFileMode FNGitFileModeFromString(NSString *fileModeString);
extern NSString *FNGitStringForFileMode(FNGitFileMode fileMode);

extern FNGitIndexStage FNGitIndexStageFromString(NSString *indexStageString);
extern NSString *FNGitStringForIndexStage(FNGitIndexStage indexStage);

extern FNGitFileStatus FNGitFileStatusFromString(NSString *fileStatusString);
extern NSString *FNGitStringForFileStatus(FNGitFileStatus fileStatus);
extern NSString *FNGitShortStringForFileStatus(FNGitFileStatus fileStatus);

extern NSString *FNGitShortenHash(NSString *objectHash);
extern NSString *FNGitShortenHashWithLength(NSString *objectHash, NSUInteger length);

extern NSString *FNGitMakeFullRefName(NSString *refName, FNGitRefType refType);
extern NSString *FNGitMakeShortRefName(NSString *fullRefName, FNGitRefType refType);

extern NSString *FNGitMakeFullRemoteRefName(NSString *remoteName, NSString *refName);
extern NSString *FNGitMakeFullRefNameForRemote(NSString *remoteName, NSString *refName);

extern FNGitRefSpec *FNGitMakeRefSpec(NSString *localRefName, NSString *remoteRefName);

extern NSString *FNGitMakeObjectReference(NSString *revision, NSString *filePath);

extern NSString *FNGitMakeRevisionRange(NSString *startRevision, NSString *endRevision);
extern NSString *FNGitMakeRevisionComparisonString(NSString *revision, NSString *otherRevision);

extern NSString *FNGitMakeBranchConfigSection(NSString *branchName);
extern NSString *FNGitMakeBranchConfigKey(NSString *branchName, NSString *configKey);

extern NSString *FNGitMakeRemoteConfigSection(NSString *remoteName);
extern NSString *FNGitMakeRemoteConfigKey(NSString *remoteName, NSString *configKey);

extern NSString *FNGitMakeSVNRemoteConfigSection(NSString *SVNRemoteName);
extern NSString *FNGitMakeSVNRemoteConfigKey(NSString *SVNRemoteName, NSString *configKey);

extern NSString *FNGitMakeSubmoduleConfigSection(NSString *submoduleName);
extern NSString *FNGitMakeSubmoduleConfigKey(NSString *submoduleName, NSString *configKey);

extern BOOL FNGitValidateRefName(NSString *refName);

extern NSDictionary *FNGitMakeErrorUserInfo(FNGitRepository *repository, NSDictionary *additionalUserInfo);
