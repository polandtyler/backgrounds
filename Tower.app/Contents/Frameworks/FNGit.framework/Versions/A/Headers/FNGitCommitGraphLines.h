//
//  FNGitCommitGraphLines.h
//  FNGit
//
//  Created by Alexander Rinass on 05.05.10.
//  Copyright 2010 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FNGitCommitGraphLine.h"

@interface FNGitCommitGraphLines : NSObject
/**
 The index of the graph line, that the commit itself lies on.
 */
@property (nonatomic) NSUInteger commitIndex;

/**
 All active graph lines that need to be drawn.
 */
@property (nonatomic) NSMutableArray *commitLines;

#pragma mark - Tasks

- (void)addCommitGraphLine:(FNGitCommitGraphLine *)commitGraphLine;

@end
