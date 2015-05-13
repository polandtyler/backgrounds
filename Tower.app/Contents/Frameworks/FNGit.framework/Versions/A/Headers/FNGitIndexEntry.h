//
//  FNGitIndexEntry.h
//  FNGit
//
//  Created by Alexander Rinass on 20.05.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FNGitFileEntry.h"

@class FNGitRepository;
@interface FNGitIndexEntry : FNGitFileEntry
@property (nonatomic, readonly) FNGitIndexStage stage;
@property (nonatomic, readonly) NSString *flag;
@property (nonatomic, readonly) BOOL isAssumeUnchangedFlagSet;
@property (nonatomic, readonly) BOOL isDefaultStage;
@property (nonatomic, readonly) BOOL isBaseStage;
@property (nonatomic, readonly) BOOL isOursStage;
@property (nonatomic, readonly) BOOL isTheirsStage;

/** @name Creating an Index Entry */

+ (id)indexEntryWithRepository:(FNGitRepository *)repository
					  filePath:(NSString *)filePath
					objectHash:(NSString *)objectHash
					  fileMode:(FNGitFileMode)fileMode
						 stage:(FNGitIndexStage)stage
						  flag:(NSString *)flag;

- (id)initWithRepository:(FNGitRepository *)repository
				filePath:(NSString *)filePath
			  objectHash:(NSString *)objectHash
				fileMode:(FNGitFileMode)fileMode
				   stage:(FNGitIndexStage)stage
					flag:(NSString *)flag;

/** @name Comparing to Another Index Entry */

- (BOOL)isEqualToIndexEntry:(FNGitIndexEntry *)object;

@end
