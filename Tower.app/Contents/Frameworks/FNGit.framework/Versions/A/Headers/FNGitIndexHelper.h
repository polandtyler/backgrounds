//
//  FNGitIndexHelper.h
//  FNGit
//
//  Created by Alexander Rinass on 05.02.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FNGitDefines.h"

@interface FNGitIndexHelper : NSObject

/** @name Validating Assume Unchanged Flags */

+ (BOOL)isAssumeUnchangedFlag:(NSString *)flag;

/** @name Creating Index Entry References */

+ (NSString *)indexEntryReferenceWithStage:(FNGitIndexStage)stage filePath:(NSString *)filePath;

/** @name String Representation for Index Stage */

+ (NSString *)stringRepresentationForIndexStage:(FNGitIndexStage)indexStage;

/** @name Index Stage From String */

+ (FNGitIndexStage)indexStageFromString:(NSString *)indexStageString;

@end
