//
//  FNGitCommitGraphDrawer.h
//  FNGit
//
//  Created by Alexander Rinass on 20.05.10.
//  Copyright 2010 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FNGitCommitGraphDrawerCommitLines.h"
#import "FNGitCommitGraphLines.h"

@class FNGitCommit;
@interface FNGitCommitGraphDrawer : NSObject
@property (nonatomic, readonly) FNGitCommitGraphDrawerCommitLines *commitLines;
	
#pragma mark - Factory methods
	
+ (id)graphDrawer;
+ (id)graphDrawerWithCommitLines:(FNGitCommitGraphDrawerCommitLines *)aCommitLinesState;

#pragma mark - Initialization
	
- (id)initWithCommitLines:(FNGitCommitGraphDrawerCommitLines *)aCommitLinesState;

#pragma mark - Create Graph Drawing Info for a Commit

- (FNGitCommitGraphLines *)drawGraphForCommit:(FNGitCommit *)aCommit error:(NSError * __autoreleasing *)error;
- (FNGitCommitGraphLines *)drawGraphForCommitHash:(NSString *)aCommitHash parentCommitHashes:(NSArray *)parentCommitHashes error:(NSError * __autoreleasing *)error;

@end
