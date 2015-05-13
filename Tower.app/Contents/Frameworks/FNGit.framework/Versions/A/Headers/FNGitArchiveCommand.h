//
//  FNGitExportCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 26/02/14.
//  Copyright (c) 2014 Fournova GmbH. All rights reserved.
//

#import <FNGit/FNGit.h>

@class FNGitRepository;
@interface FNGitArchiveCommand : FNGitCommand
@property (nonatomic) NSString *revision;
@property (nonatomic) NSArray *filePaths;
@property (nonatomic) NSString *destination;
@property (nonatomic) FNGitArchiveFormat format;

/** @name Creating Instances */

+ (instancetype)gitArchiveCommandWithRepository:(FNGitRepository *)repository revision:(NSString *)revision filePaths:(NSArray *)filePaths destination:(NSString *)destination;

- (instancetype)initWithRepository:(FNGitRepository *)repository revision:(NSString *)revision filePaths:(NSArray *)filePaths destination:(NSString *)destination;

- (NSArray *)archivedFilePathsResult;

@end
