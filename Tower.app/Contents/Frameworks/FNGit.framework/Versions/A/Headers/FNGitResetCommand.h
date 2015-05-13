//
//  FNGitResetCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 12.09.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNGitCommand.h"

typedef NS_ENUM(NSInteger, FNGitResetMode) {
    FNGitResetModeDefault = 0,
    FNGitResetModeSoft,
    FNGitResetModeHard,
    FNGitResetModeKeep,
    FNGitResetModeMixed
};

@class FNGitRepository;
@interface FNGitResetCommand : FNGitCommand
@property (nonatomic) FNGitResetMode mode;
@property (nonatomic) NSString *revision;
@property (nonatomic) NSArray *filePaths;

#pragma mark - Factory Methods

+ (id)gitResetCommandWithRepository:(FNGitRepository *)repository
                               mode:(FNGitResetMode)mode
                           revision:(NSString *)revision;

+ (id)gitResetCommandWithRepository:(FNGitRepository *)repository
                               mode:(FNGitResetMode)mode
                           revision:(NSString *)revision
                          filePaths:(NSArray *)filePaths;

#pragma mark - Initialization

- (id)initWithRepository:(FNGitRepository *)repository
                    mode:(FNGitResetMode)mode
                revision:(NSString *)revision
               filePaths:(NSArray *)filePaths;

@end
