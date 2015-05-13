//
//  FNGitDiffOutputParser.h
//  FNGit
//
//  Created by Alexander Rinass on 08.07.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FNGitOutputParser.h"
#import "FNGitDiffChunkLine.h"
#import "FNGitDefines.h"

extern NSString *const FNGitDiffRawKey;
extern NSString *const FNGitDiffFilePathKey;
extern NSString *const FNGitDiffOldFilePathKey;
extern NSString *const FNGitDiffIsBinaryKey;
extern NSString *const FNGitDiffHeaderKey;
extern NSString *const FNGitDiffExtendedHeadersKey;
extern NSString *const FNGitDiffFileStatusKey;
extern NSString *const FNGitDiffFileStatusSimilarityIndexKey;
extern NSString *const FNGitDiffObjectHashKey;
extern NSString *const FNGitDiffOriginalObjectHashesKey;
extern NSString *const FNGitDiffFileModeKey;
extern NSString *const FNGitDiffOriginalFileModesKey;
extern NSString *const FNGitDiffChunksKey;

extern NSString *const FNGitDiffChunkRawKey;
extern NSString *const FNGitDiffChunkFileRangesKey;
extern NSString *const FNGitDiffChunkLinesKey;

extern NSString *const FNGitDiffChunkLineLineNumbersKey;
extern NSString *const FNGitDiffChunkLineTypeKey;
extern NSString *const FNGitDiffChunkLineStatusKey;
extern NSString *const FNGitDiffChunkLineContentsKey;

extern NSString *const FNGitDiffChunkLineTypeContext;
extern NSString *const FNGitDiffChunkLineTypeAdded;
extern NSString *const FNGitDiffChunkLineTypeDeleted;
extern NSString *const FNGitDiffChunkLineTypeNoNewlineAtEndOfFile;

extern NSString *const FNGitDiffFileStatusModified;
extern NSString *const FNGitDiffFileStatusAdded;
extern NSString *const FNGitDiffFileStatusDeleted;
extern NSString *const FNGitDiffFileStatusRenamed;
extern NSString *const FNGitDiffFileStatusCopied;

@interface NSDictionary (FNGitDiffOutputParser)

- (NSString *)gitDiffRaw;
- (NSString *)gitDiffFilePath;
- (NSString *)gitDiffOldFilePath;
- (FNGitFileStatus)gitDiffFileStatus;
- (NSUInteger)gitDiffFileStatusSimilarityIndex;
- (NSString *)gitDiffObjectHash;
- (NSArray *)gitDiffOriginalObjectHashes;
- (FNGitFileMode)gitDiffFileMode;
- (NSArray *)gitDiffOriginalFileModes;
- (NSString *)gitDiffHeader;
- (NSArray *)gitDiffExtendedHeaders;
- (NSArray *)gitDiffChunks;
- (BOOL)gitDiffIsBinary;

- (NSString *)gitDiffChunkRaw;
- (NSArray *)gitDiffChunkFileRanges;
- (NSArray *)gitDiffChunkLines;

- (NSArray *)gitDiffChunkLineLineNumbers;
- (FNGitDiffChunkLineType)gitDiffChunkLineType;
- (NSString *)gitDiffChunkLineStatus;
- (NSString *)gitDiffChunkLineContents;

@end
#pragma mark -

@interface FNGitDiffOutputParser : FNGitOutputParser {
@private
	BOOL isFinishedParsingHeader;
	NSUInteger numberOfParents;
	NSMutableArray *currentLineNumbers;
	NSMutableArray *maxCurrentLineNumbers;
}

#pragma mark - Accessing the Result

- (NSDictionary *)diff;

@end
