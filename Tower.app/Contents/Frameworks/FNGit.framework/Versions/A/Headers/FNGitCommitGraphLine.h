//
//  FNGitCommitGraphLine.h
//  FNGit
//
//  Created by Alexander Rinass on 05.05.10.
//  Copyright 2010 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef struct {
    CGPoint fromPoint;
    CGPoint toPoint;
} Line;

extern const NSUInteger GTCommitLineColumnWidth;
extern const NSUInteger GTCommitLineColumnMiddle;

@interface FNGitCommitGraphLine : NSObject

/**
 Unique graph line ID (to assign different colors to each graph line).
 */
@property (nonatomic) NSUInteger lineID;

/**
 The index the graph line originates from.
 */
@property (nonatomic) NSUInteger startIndex;

/**
 The index the graph line continues on.
 */
@property (nonatomic) NSUInteger endIndex;

/**
 Wether or not the graph line is spawned here.
 */
@property (nonatomic) BOOL isStarting;

/**
 Wether or not the graph line ends here.
 */
@property (nonatomic) BOOL isEnding;

- (Line)lineForFNGitCommitGraphLine:(CGRect)drawingRect commitIndex:(NSUInteger)commitIndex;

@end
