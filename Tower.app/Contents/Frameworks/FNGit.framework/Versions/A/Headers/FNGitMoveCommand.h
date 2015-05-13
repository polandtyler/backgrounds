//
//  FNGitMoveCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 30.07.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <FNGit/FNGit.h>

@class FNGitRepository;
@interface FNGitMoveCommand : FNGitCommand
@property (nonatomic) NSString *sourceFilePath;
@property (nonatomic) NSString *destinationFilePath;
@property (nonatomic) BOOL forcesRename;
@property (nonatomic) BOOL ignoresErrors;

#pragma mark - Factory Methods

+ (id)gitMoveCommandWithRepository:(FNGitRepository *)repository sourceFilePath:(NSString *)sourceFilePath destinationFilePath:(NSString *)destinationFilePath;

#pragma mark - Initialization

- (id)initWithRepository:(FNGitRepository *)repository sourceFilePath:(NSString *)sourceFilePath destinationFilePath:(NSString *)destinationFilePath;

@end
