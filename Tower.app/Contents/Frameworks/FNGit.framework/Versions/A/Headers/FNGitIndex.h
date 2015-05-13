//
//  FNGitIndex.h
//  FNGit
//
//  Created by Alexander Rinass on 01.06.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FNGitDefines.h"

/** @name Index Options */

typedef NS_OPTIONS(NSUInteger, FNGitIndexOptions) {
    FNGitIndexOptionNone = 0,
    FNGitIndexOptionFilterAssumeUnchangedFiles = 1UL << 0,
    FNGitIndexOptionFilterSubmodules = 1UL << 1
};

@class FNGitRepository;
@class FNGitIndexEntry;
@interface FNGitIndex : NSObject
@property (nonatomic, weak, readonly) FNGitRepository *repository;

/** @name Creating a Git Index Object */

+ (id)indexWithRepository:(FNGitRepository *)repository;
- (id)initWithRepository:(FNGitRepository *)repository;

/** @name Retrieving Index Entries */

/**
 Returns all index entries at all stages or `nil` on error.
 
 If an error occurs, the error reference is set to an actual error object containing the error
 information. You may specify nil for this parameter if you do not want the error information.
 */
- (NSArray *)allIndexEntries:(NSError * __autoreleasing *)error;

/**
 Returns all index entries for the given file paths at all stages or `nil` on error.
 
 You can pass additional options to further filter entries.
 
 If no given file paths match can be found in the index, `nil` is returned and error is set to `nil` as well.
 
 If an error occurs, the error reference is set to an actual error object containing the error
 information. You may specify nil for this parameter if you do not want the error information.
 */
- (NSArray *)indexEntriesForFilePaths:(NSArray *)filePaths options:(FNGitIndexOptions)options error:(NSError * __autoreleasing *)error;

/**
 Returns all index entries for the given file path at all stages or `nil` on error.
 
 If the index entry does not exist, `nil` is returned and error is set to `nil` as well.
 
 If an error occurs, the error reference is set to an actual error object containing the error
 information. You may specify nil for this parameter if you do not want the error information.
 */
- (NSArray *)indexEntriesForFilePath:(NSString *)filePath error:(NSError * __autoreleasing *)error;

/**
 Returns the index entry at default stage or `nil` if it does not exist or on error.
 
 If the index entry does not exist at this stage, `nil` is returned and error set to `nil` as well.
 
 If an error occurs, the error reference is set to an actual error object containing the error
 information. You may specify nil for this parameter if you do not want the error information.
 */
- (FNGitIndexEntry *)indexEntryForFilePath:(NSString *)filePath error:(NSError * __autoreleasing *)error;

/**
 Returns the index entry at the given stage or `nil` if it does not exist or on error.
 
 If the index entry does not exist at the given stage, `nil` is returned and error set to `nil` as well.
 
 If an error occurs, the error reference is set to an actual error object containing the error
 information. You may specify nil for this parameter if you do not want the error information.
 */
- (FNGitIndexEntry *)indexEntryForFilePath:(NSString *)filePath atStage:(FNGitIndexStage)stage error:(NSError * __autoreleasing *)error;

@end
