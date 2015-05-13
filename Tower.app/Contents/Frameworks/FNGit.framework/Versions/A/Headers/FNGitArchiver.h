//
//  FNGitExporter.h
//  FNGit
//
//  Created by Alexander Rinass on 26/02/14.
//  Copyright (c) 2014 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@class FNGitRepository;
@interface FNGitArchiver : NSObject
@property (nonatomic, readonly) FNGitRepository *repository;
@property (nonatomic, readonly) NSString *revision;
@property (nonatomic, readonly) NSArray *filePaths;
@property (nonatomic, readonly) NSString *destination;
@property (nonatomic, readonly, getter = isRunning) BOOL running;
@property (nonatomic, readonly) NSError *error;
@property (nonatomic, readonly) NSArray *archivedFilePaths;

/** @name Creating Instances */

- (id)initWithRepository:(FNGitRepository *)repository revision:(NSString *)revision filePaths:(NSArray *)filePaths destination:(NSString *)destination;

/** @name Launching the Archiver */

- (void)archiveWithProgressHandler:(void (^)(double progress, NSString *output))progressHandler completionHandler:(void (^)(NSArray *archivedFilePaths, NSError *error))completionHandler;

- (void)start;
- (void)cancel;
- (void)waitUntilFinished;

- (BOOL)run:(NSError * __autoreleasing *)error;

@end
