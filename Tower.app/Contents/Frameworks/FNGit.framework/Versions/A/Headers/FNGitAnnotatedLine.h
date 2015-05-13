//
//  FNGitAnnotatedLine.h
//  FNGit
//
//  Created by Alexander Rinass on 22.06.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@class FNGitCommit;
@interface FNGitAnnotatedLine : NSObject
@property (nonatomic, readonly) NSString *filePath;
@property (nonatomic, readonly) NSString *lineContents;
@property (nonatomic, readonly) NSUInteger originalLineNumber;
@property (nonatomic, readonly) NSUInteger finalLineNumber;
@property (nonatomic, readonly) NSUInteger lineGroup;
@property (nonatomic, readonly) FNGitCommit *commit;

#pragma mark - Factory Methods

+ (id)annotatedLineWithFilePath:(NSString *)filePath 
				   lineContents:(NSString *)lineContents
			 originalLineNumber:(NSUInteger)originalLineNumber
				finalLineNumber:(NSUInteger)finalLineNumber
					  lineGroup:(NSUInteger)lineGroup
						 commit:(FNGitCommit *)commit;

#pragma mark - Initialization

- (id)initWithFilePath:(NSString *)filePath 
		  lineContents:(NSString *)lineContents
	originalLineNumber:(NSUInteger)originalLineNumber
	   finalLineNumber:(NSUInteger)finalLineNumber
			 lineGroup:(NSUInteger)lineGroup
				commit:(FNGitCommit *)commit;

@end
