//
//  FNCommandOperation.h
//  FNFoundation
//
//  Created by Alexander Rinass on 26.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FNCommandOperationDelegate.h"

@interface FNCommandOperation : NSOperation
@property (nonatomic, weak) id<FNCommandOperationDelegate> delegate;
@property (nonatomic, copy) NSString *identifier;
@property (nonatomic, copy) NSString *launchPath;
@property (nonatomic, copy) NSString *workingDirectory;
@property (nonatomic, copy) NSArray *modes;
@property (nonatomic, copy) NSArray *arguments;
@property (nonatomic, copy) NSDictionary *environment;
@property (nonatomic) id standardInput;
@property (nonatomic) NSPipe *standardOutput;
@property (nonatomic) NSPipe *standardError;
@property (atomic, copy, readonly) NSData *standardOutputData;
@property (atomic, copy, readonly) NSData *standardErrorData;
@property (atomic, readonly) NSInteger exitCode;

#pragma mark - Factory Methods

+ (BOOL)runCommandWithLaunchPath:(NSString *)launchPath arguments:(NSArray *)arguments error:(NSError * __autoreleasing *)error;
+ (BOOL)runCommandWithLaunchPath:(NSString *)launchPath workingDirectory:(NSString *)workingDirectory arguments:(NSArray *)arguments error:(NSError * __autoreleasing *)error;

+ (id)commandWithLaunchPath:(NSString *)launchPath arguments:(NSArray *)arguments;
+ (id)commandWithLaunchPath:(NSString *)launchPath arguments:(NSArray *)arguments delegate:(id<FNCommandOperationDelegate>)delegate;
+ (id)commandWithLaunchPath:(NSString *)launchPath workingDirectory:(NSString *)workingDirectory arguments:(NSArray *)arguments;
+ (id)commandWithLaunchPath:(NSString *)launchPath workingDirectory:(NSString *)workingDirectory arguments:(NSArray *)arguments delegate:(id<FNCommandOperationDelegate>)delegate;

#pragma mark - Initialization

- (id)initWithLaunchPath:(NSString *)launchPath workingDirectory:(NSString *)workingDirectory arguments:(NSArray *)arguments delegate:(id<FNCommandOperationDelegate>)delegate;

#pragma mark - Setting Enviroment Variables

- (void)setValue:(NSString *)value forEnvironmentVariable:(NSString *)environmentVariable;

#pragma mark - Retrieving the Full Command Call

- (NSString *)commandCall;

#pragma mark - Responding to Command Events

- (void)commandWillExecute;
- (void)commandDidFailToLaunch;
- (void)commandDidTerminate;

- (void)setExecuting:(BOOL)executing;
- (void)setFinished:(BOOL)finished;

@end
