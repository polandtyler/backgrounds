//
//  FNGitOutputParser.h
//  FNGit
//
//  Created by Alexander Rinass on 17.06.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FNFoundation/FNFoundation.h>

@interface FNGitOutputParser : NSObject
@property (nonatomic, readonly) NSArray *outputLines;
@property (nonatomic, readonly) NSMutableDictionary *resultCache;
@property (nonatomic, readonly) NSMutableArray *indexedResultCache;

#pragma mark - Newline Delimiter

+ (BOOL)usesNULByteAsNewlineDelimiter;

#pragma mark - Factory Methods

+ (id)outputParserWithOutputData:(NSData *)outputData;
+ (id)outputParserWithOutputLines:(NSArray *)outputLines;

#pragma mark - Initialization

- (id)initWithOutputData:(NSData *)outputData;
- (id)initWithOutputData:(NSData *)outputData usesNULByteAsNewlineDelimiter:(BOOL)usesNULByteAsNewlineDelimiter;
- (id)initWithOutputLines:(NSArray *)outputLines;

#pragma mark - Parsing Output

- (BOOL)parse:(NSError * __autoreleasing *)error;
- (BOOL)parseOutputLine:(NSString *)outputLine;

//- (BOOL)gitParserShouldUseNULByteDelimiter;
//- (BOOL)gitParserWillParseOutputLine:(NSString *)outputLine;

- (NSRegularExpression *)regularExpressionWithPattern:(NSString *)pattern options:(NSRegularExpressionOptions)options;

@end
