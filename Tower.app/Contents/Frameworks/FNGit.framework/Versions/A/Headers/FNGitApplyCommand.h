//
//  FNGitApplyCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 27.09.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNGitCommand.h"

extern NSString *const FNGitApplyOptionCached;
extern NSString *const FNGitApplyOptionReverse;
extern NSString *const FNGitApplyOptionUnidiffZero;

@class FNGitRepository;
@interface FNGitApplyCommand : FNGitCommand
@property (nonatomic) NSArray *filePaths;
@property (nonatomic) NSData *patch;
@property (nonatomic) BOOL appliesPatchToIndex;
@property (nonatomic) BOOL appliesPatchInReverse;
@property (nonatomic) BOOL checksApplicability;
@property (nonatomic) BOOL unidiffZero;

#pragma mark - Factory Methods

+ (id)gitApplyCommandWithRepository:(FNGitRepository *)repository;
+ (id)gitApplyCommandWithRepository:(FNGitRepository *)repository filePaths:(NSArray *)filePaths options:(NSDictionary *)options;
+ (id)gitApplyCommandWithRepository:(FNGitRepository *)repository patch:(NSData *)patch options:(NSDictionary *)options;

#pragma mark - Initialization

- (id)initWithRepository:(FNGitRepository *)repository options:(NSDictionary *)options;

@end
