//
//  FNGitWorkingTreeHelper.h
//  FNGit
//
//  Created by Alexander Rinass on 06.02.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FNFoundation/FNFoundation.h>
#import "FNGitDefines.h"

@class FNGitWorkingTreeEntry;
@interface FNGitWorkingTreeHelper : NSObject

/** @name Determining Unmerged File Status */

+ (BOOL)isUnmergedPathForLeftFileStatus:(FNGitFileStatus)leftFileStatus rightFileStatus:(FNGitFileStatus)rightFileStatus;

/** @name String Representation for File Status */

+ (NSString *)stringRepresentationForFileStatus:(FNGitFileStatus)fileStatus;
+ (NSString *)shortStringRepresentationForFileStatus:(FNGitFileStatus)fileStatus;

/** @name File Status From String */

+ (FNGitFileStatus)fileStatusFromString:(NSString *)fileStatusString;

/** name Creating File References for Unmerged Files */

+ (NSString *)unmergedOursFileReferenceForWorkingTreeEntry:(FNGitWorkingTreeEntry *)workingTreeEntry;
+ (NSString *)unmergedTheirsFileReferenceForWorkingTreeEntry:(FNGitWorkingTreeEntry *)workingTreeEntry;

@end
