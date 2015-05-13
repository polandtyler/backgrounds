//
//  FNGitCommitParser.h
//  FNGit
//
//  Created by Alexander Rinass on 01.07.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import "FNGitOutputParser.h"
#import "FNGitCommitOutputParserResultItem.h"

@interface FNGitCommitOutputParser : FNGitOutputParser
@property (nonatomic, readonly) NSArray *prettyFormat;
@property (nonatomic, readonly) NSArray *commits;

#pragma mark - Factory Methods

+ (id)commitParserWithData:(NSData *)commitOutputData prettyFormat:(NSArray *)prettyFormat;

#pragma mark - Initialization

- (id)initWithData:(NSData *)commitOutputData prettyFormat:(NSArray *)prettyFormat;

#pragma mark - Retrieving Common Pretty Formats

+ (NSArray *)gitCommitLogPrettyFormat;
+ (NSString *)gitCommitLogPrettyFormatString;

+ (NSArray *)gitCommitHashLogPrettyFormat;
+ (NSString *)gitCommitHashLogPrettyFormatString;

+ (NSArray *)gitStashListPrettyFormat;
+ (NSString *)gitStashListPrettyFormatString;

@end
