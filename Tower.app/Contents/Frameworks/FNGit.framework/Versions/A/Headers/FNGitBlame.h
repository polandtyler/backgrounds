//
//  FNGitBlame.h
//  FNGit
//
//  Created by Alexander Rinass on 22.06.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FNGitAnnotatedLine.h"

@class FNGitRepository;
@interface FNGitBlame : NSObject
@property (nonatomic, weak, readonly) FNGitRepository *repository;
@property (nonatomic, readonly) NSString *filePath;
@property (nonatomic, readonly) NSString *revision;
@property (nonatomic, readonly) NSArray *annotatedLines;

#pragma mark - Retrieving Blame for File Path and Revision for a Repository

+ (id)blameForFilePath:(NSString *)filePath revision:(NSString *)revision repository:(FNGitRepository *)repository error:(NSError * __autoreleasing *)error;

#pragma mark - Factory Methods

+ (id)blameWithRepository:(FNGitRepository *)repository filePath:(NSString *)filePath revision:(NSString *)revision annotatedLines:(NSArray *)annotatedLines;

#pragma mark - Initialization

- (id)initWithRepository:(FNGitRepository *)repository filePath:(NSString *)filePath revision:(NSString *)revision annotatedLines:(NSArray *)annotatedLines;

@end
