//
//  FNGitWorkingTreeManager+Helpers.h
//  FNGit
//
//  Created by Alexander Rinass on 18.04.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <FNGit/FNGit.h>

// TODO: Rename to FNGitCommandArgumentsHelper

@interface FNGitWorkingTreeManager (Helpers)

+ (NSUInteger)maximumNumberOfAllowedFilePathArguments;
+ (void)setMaximumNumberOfAllowedFilePathArguments:(NSUInteger)value;

/**
 Returns the maximum number of allowed file path arguments as a shell command 
 can not an argument limit of 4096. 
 
 Pass in a boolean to determine if you need to call the git command again with
 the remaining files. To get the remaining files, use the
 `remainingFilePathsFromFilePaths: method.
 */
+ (NSArray *)filePathsForGitCommand:(NSArray *)files exceedsArgumentsLimit:(BOOL *)exceedsArgumentsLimit;

/**
 Returns a subarray of remaining file paths from the given file paths from
 index defined by `kMaxMultipleFileActionCount`.
 
 Use this method after calling `filePathsForGitCommand:exceedsArgumentsLimit:`
 and `exceedsArgumentsLimit` has returned `YES` to retrieve the remaining file
 paths.
 */
+ (NSArray *)remainingFilePathsFromFilePaths:(NSArray *)filePaths;

@end
