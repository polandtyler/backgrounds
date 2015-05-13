//
//  FNGitChangesetEntry.h
//  FNGit
//
//  Created by Alexander Rinass on 12.07.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FNGitDefines.h"

@interface FNGitChangesetEntry : NSObject
@property (nonatomic, readonly) NSString *filePath;
@property (nonatomic, readonly) NSString *oldFilePath;
@property (nonatomic, readonly) FNGitFileStatus fileStatus;
@property (nonatomic, readonly) NSUInteger fileStatusSimilarityIndex;
@property (nonatomic, readonly) FNGitFileMode fileMode;
@property (nonatomic, readonly) FNGitFileMode originalFileMode;
@property (nonatomic, readonly) NSArray *originalFileModes;
@property (nonatomic, readonly) NSString *objectHash;
@property (nonatomic, readonly) NSString *originalObjectHash;
@property (nonatomic, readonly) NSArray *originalObjectHashes;
@property (nonatomic, readonly) BOOL isCombinedDiff;
@property (nonatomic, readonly) NSUInteger linesAdded;
@property (nonatomic, readonly) NSUInteger linesDeleted;
@property (nonatomic, readonly) BOOL isFileStatusAdded;
@property (nonatomic, readonly) BOOL isFileStatusDeleted;
@property (nonatomic, readonly) BOOL isFileStatusModified;
@property (nonatomic, readonly) BOOL isFileStatusRenamed;
@property (nonatomic, readonly) BOOL isFileStatusCopied;
@end
