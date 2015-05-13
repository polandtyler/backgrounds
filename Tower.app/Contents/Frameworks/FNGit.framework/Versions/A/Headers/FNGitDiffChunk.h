//
//  FNGitDiffChunk.h
//  FNGit
//
//  Created by Alexander Rinass on 14.01.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FNGitDiffChunkLine.h"

@interface FNGitDiffChunk : NSObject
@property (nonatomic, readonly) NSString *rawChunk;
@property (nonatomic, readonly) NSArray *fileRanges;
@property (nonatomic, readonly) NSArray *lines;
@property (nonatomic, readonly) NSString *header;
@property (nonatomic, readonly) NSString *content;
@property (nonatomic, readonly) NSUInteger insertions;
@property (nonatomic, readonly) NSUInteger deletions;

/** @name Creating Diff Chunk Objects */

+ (id)diffChunkWithRawChunk:(NSString *)rawChunk fileRanges:(NSArray *)headerFileRanges lines:(NSArray *)chunkLines;
- (id)initWithRawChunk:(NSString *)rawChunk fileRanges:(NSArray *)headerFileRanges lines:(NSArray *)chunkLines;

@end
