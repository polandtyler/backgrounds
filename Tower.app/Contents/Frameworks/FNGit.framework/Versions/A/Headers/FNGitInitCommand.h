//
//  FNGitInitRepositoryCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 01.08.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNGitCommand.h"

extern NSString *const FNGitInitOptionBare;
extern NSString *const FNGitInitOptionSharedMode;

extern NSString *const FNGitInitOptionSharedModeDefault;
extern NSString *const FNGitInitOptionSharedModeGroup;
extern NSString *const FNGitInitOptionSharedModeAll;

@interface FNGitInitCommand : FNGitCommand
@property (nonatomic, readonly) NSString *path;
@property (nonatomic, getter = isBare) BOOL bare;
@property (nonatomic) NSString *sharedMode;

#pragma mark - Factory Methods

+ (id)gitInitCommandWithPath:(NSString *)path options:(NSDictionary *)options;

#pragma mark - Initialization

- (id)initWithPath:(NSString *)path options:(NSDictionary *)options;

@end
