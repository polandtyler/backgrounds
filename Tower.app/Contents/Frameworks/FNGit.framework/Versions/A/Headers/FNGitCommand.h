//
//  FNGitCommand.h
//  FNGit
//
//  Created by Alexander Rinass on 30.05.11.
//  Copyright 2011 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FNFoundation/FNFoundation.h>
#import "FNGitCommon.h"
#import "NSError+FNGit.h"
#import "FNGitCommandDelegate.h"
#import "FNGitCommandProgress.h"

typedef void (^FNGitCommandProgressHandler)(FNGitCommandProgress *progress);
typedef void (^FNGitCommandCompletionHandler)(FNGitCommand *command);

@class FNGitBinary;
@class FNGitRepository;
@class FNGitCommandProgress;
@interface FNGitCommand : FNCommandOperation <FNCommandOperationDelegate>
@property (nonatomic, readonly) FNGitBinary *gitBinary;
@property (nonatomic, readonly) NSString *repositoryPath;
@property (nonatomic, readonly) NSString *gitDirectoryPath;
@property (nonatomic, readonly) NSString *workingTreeDirectoryPath;
@property (nonatomic) BOOL sanitizesEnvironment;
@property (nonatomic) NSString *gitCommand;
@property (nonatomic) NSString *gitSubCommand;
@property (nonatomic) NSArray *gitOptions;
@property (nonatomic) NSArray *gitCommandOptions;
@property (nonatomic) NSArray *gitCommandArguments;
@property (nonatomic, readonly) NSString *standardOutputString;
@property (nonatomic, readonly) NSString *standardErrorString;
@property (nonatomic) NSError *error;
@property (nonatomic, readonly) FNGitCommandProgress *commandProgress;
@property (nonatomic, getter = isSupportingProgressOutput) BOOL supportsProgressOutput;

#pragma mark - Factory Methods

+ (id)gitCommandWithGitBinary:(FNGitBinary *)gitBinary;
+ (id)gitCommandWithRepository:(FNGitRepository *)repository;
+ (id)gitCommandWithRepositoryPath:(NSString *)repositoryPath;
+ (id)gitCommandWithGitBinary:(FNGitBinary *)gitBinary repositoryPath:(NSString *)repositoryPath;
+ (id)gitCommandWithGitBinary:(FNGitBinary *)gitBinary gitDirectoryPath:(NSString *)gitDirectoryPath workingTreeDirectoryPath:(NSString *)workingTreeDirectoryPath;

#pragma mark - Initializing a Git Command

- (id)initWithRepository:(FNGitRepository *)repository;
- (id)initWithRepositoryPath:(NSString *)repositoryPath;
- (id)initWithGitDirectoryPath:(NSString *)gitDirectoryPath workingTreeDirectoryPath:(NSString *)workingTreeDirectoryPath;
- (id)initWithGitBinary:(FNGitBinary *)gitBinary repositoryPath:(NSString *)repositoryPath gitDirectoryPath:(NSString *)gitDirectoryPath workingTreeDirectoryPath:(NSString *)workingTreeDirectoryPath;

#pragma mark - Managing Event Handlers

- (void)setProgressHandler:(FNGitCommandProgressHandler)progressHandler;
- (FNGitCommandProgressHandler)progressHandler;

- (void)setCompletionHandler:(FNGitCommandCompletionHandler)completionHandler;
- (FNGitCommandCompletionHandler)completionHandler;

#pragma mark - Managing Environment Variables

- (void)addEnvironmentVariables:(NSDictionary *)environmentVariables;
- (void)setValue:(NSString *)value forEnvironmentVariable:(NSString *)environmentVariable;

#pragma mark - Managing Git Options

- (void)addGitOption:(NSString *)gitOption;
- (void)addGitOptions:(NSArray *)gitOptions;
- (void)removeGitDirOption;
- (void)removeWorkTreeOption;

#pragma mark - Managing Git Command Options

- (void)addGitCommandOption:(NSString *)gitCommandOption;
- (void)addGitCommandOptions:(NSArray *)gitCommandOptions;

#pragma mark - Managing Git Command Arguments

- (void)addGitCommandArgument:(NSString *)gitCommandArgument;
- (void)addGitCommandArguments:(NSArray *)gitCommandArguments;

#pragma mark - Responding to GitCommand Events

- (void)gitCommandWillInitialize;
- (void)gitCommandDidInitialize;
- (NSDictionary *)gitCommandWillUseErrorUserInfo:(NSDictionary *)userInfo;
- (void)gitCommandDidTerminate;
- (BOOL)gitCommandShouldHandleError:(NSError *)error;
- (BOOL)gitCommandWillParseOutput:(NSError * __autoreleasing *)error;

- (NSError *)makeGitError;

#pragma mark - Running the Git Command Synchronously

- (BOOL)run:(NSError * __autoreleasing *)error;

@end
