//
//  FNGitMergeTool.h
//  FNGit
//
//  Created by Alexander Rinass on 09.09.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@class FNGitRepository;
@interface FNGitMergeTool : NSObject
@property (nonatomic, readonly) FNGitRepository *repository;
@property (nonatomic, readonly) NSString *name;
@property (nonatomic) BOOL keepsBackupFiles;

/** @name Creating Merge Tool Objects */

+ (id)mergeToolWithRepository:(FNGitRepository *)repository name:(NSString *)name;
- (id)initWithRepository:(FNGitRepository *)repository name:(NSString *)name;

/** @name Launching the Merge Tool */

- (void)launchWithFilePath:(NSString *)filePath completionHandler:(void (^)(NSInteger exitCode, NSError *error))completionHandler;
- (void)cancel;

@end
