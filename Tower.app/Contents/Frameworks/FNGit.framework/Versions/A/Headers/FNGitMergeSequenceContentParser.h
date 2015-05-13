//
//  FNGitMergeSequenceContentParser.h
//  FNGit
//
//  Created by Alexander Rinass on 20/02/14.
//  Copyright (c) 2014 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface FNGitMergeSequenceContentParser : NSObject
@property (nonatomic) NSString *contents;
@property (nonatomic, readonly) NSUInteger revisionsCount;
@property (nonatomic, readonly) NSString *nextRevision;
@property (nonatomic, readonly) NSString *lastRevision;

- (id)initWithContentsOfFile:(NSString *)filePath;
- (id)initWithContents:(NSString *)contents;

- (BOOL)parse:(NSError * __autoreleasing *)error;

- (NSArray *)allRevisions;

@end
