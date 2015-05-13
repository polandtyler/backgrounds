//
//  FNGitStashCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 30.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import "FNGitCommand.h"

@interface FNGitStashCommand : FNGitCommand
@property (nonatomic) NSString *refName;
@property (nonatomic) NSString *message;
@property (nonatomic) BOOL savesStash;
@property (nonatomic) BOOL appliesStash;
@property (nonatomic) BOOL deletesStash;
@property (nonatomic) BOOL includesUntrackedFiles;
@property (nonatomic) BOOL keepsIndex;
@property (nonatomic) BOOL restoresIndex;
@property (nonatomic, readonly) NSArray *stashes;

#pragma mark - Factory Methods

+ (id)gitSaveStashCommandWithRepository:(FNGitRepository *)repository message:(NSString *)message;
+ (id)gitDeleteStashCommandWithRepository:(FNGitRepository *)repository refName:(NSString *)refName;
+ (id)gitApplyStashCommandWithRepository:(FNGitRepository *)repository refName:(NSString *)refName deletingStash:(BOOL)deletesStash;

+ (id)gitStashCommandWithRepository:(FNGitRepository *)repository;

@end
