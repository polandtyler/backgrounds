//
//  FNGitDiffChunkLine.h
//  FNGit
//
//  Created by Alexander Rinass on 14.01.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, FNGitDiffChunkLineType) {
	FNGitDiffChunkContextLineType,
	FNGitDiffChunkAddedLineType,
	FNGitDiffChunkDeletedLineType,
	FNGitDiffChunkNoNewlineAtEndOfFileLineType,
};

@interface FNGitDiffChunkLine : NSObject
@property (nonatomic, readonly) NSArray *lineNumbers;
@property (nonatomic, readonly) FNGitDiffChunkLineType type;
@property (nonatomic, readonly) NSString *status;
@property (nonatomic, readonly) NSString *content;
@property (nonatomic, readonly) NSString *contentWithStatus;
@property (nonatomic, readonly) BOOL isContextLine;
@property (nonatomic, readonly) BOOL isAddedLine;
@property (nonatomic, readonly) BOOL isDeletedLine;
@property (nonatomic, readonly) BOOL isNoNewlineAtEndOfFileLine;

/** @name Creating DiffChunkLine Objects */

+ (id)diffChunkLineWithLineNumbers:(NSArray *)theLineNumbers type:(FNGitDiffChunkLineType)theLineType status:(NSString *)theLineStatus content:(NSString *)theLineContents;
- (id)initWithLineNumbers:(NSArray *)theLineNumbers type:(FNGitDiffChunkLineType)theLineType status:(NSString *)theLineStatus content:(NSString *)theLineContents;

@end
