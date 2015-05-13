//
//  FNGitCommitGraphDrawerCommitLines.h
//  FNGit
//
//  Created by Alexander Rinass on 12.07.10.
//  Copyright 2010 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FNGitCommitGraphDrawerCommitLine.h"

@interface FNGitCommitGraphDrawerCommitLines : NSObject {
@private
	NSMutableArray *commitLines;
	NSUInteger lastCommitLineID;
}

#pragma mark - Querying the CommitLines Status

- (BOOL)isEmpty;

#pragma mark - 

- (NSUInteger)nextCommitLineIndex;

#pragma mark - Retrieving a Copy of the current CommitLines

- (NSArray *)currentCommitLines;

#pragma mark - Managing Commit Lines

/**
 Starts a new commit line that points towards the given commit hash and returns
 the commit line ID.
 
 If a commit line pointing towards the given commit hash already exists, it is
 reused unless the flag "isHead" is true, which forces a new line to be created.
 */
- (NSUInteger)commitLineWithCommitHash:(NSString *)aCommitHash isHead:(BOOL)isHead;

/**
 Updates the commit line identified by the given ID with the given commit hash.
 The commit line will then point towards the new commit hash.
 */
- (void)updateCommitLineWithID:(NSUInteger)aCommitLineID withCommitHash:(NSString *)aCommitHash;

/**
 Ends the commit line with the given commit line ID.
 */
- (void)endCommitLineWithID:(NSUInteger)aCommitLineID;

#pragma mark - Finding CommitLines

/**
 Returns the line index of the commit line identified by the given commit line 
 ID.
 
 If the commit line with the given ID cannot be found, NSNotFound is returned.
 */
- (NSUInteger)indexOfCommitLineWithID:(NSUInteger)aCommitLineID;

/**
 Returns an array of CommitLine objects that point towards the given commit
 hash.
 */
- (NSArray *)allCommitLinesPointingTowardsCommitHash:(NSString *)aCommitHash;

@end
