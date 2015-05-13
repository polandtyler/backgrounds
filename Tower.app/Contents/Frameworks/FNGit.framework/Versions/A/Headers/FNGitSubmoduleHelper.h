//
//  FNGitSubmoduleHelper.h
//  FNGit
//
//  Created by Alexander Rinass on 12.08.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FNGitSubmoduleOptions.h"

@class FNGitRepository;
@class FNGitSubmodule;
@interface FNGitSubmoduleHelper : NSObject

+ (NSString *)absoluteWorkingDirectoryPathForSubmodulePath:(NSString *)releativeSubmodulePath inRepository:(FNGitRepository *)repository;
+ (NSString *)absoluteGitDirectoryPathForSubmodulePath:(NSString *)releativeSubmodulePath inRepository:(FNGitRepository *)repository;

+ (NSString *)absoluteWorkingDirectoryPathForSubmodule:(FNGitSubmodule *)submodule inRepository:(FNGitRepository *)repository;
+ (NSString *)absoluteGitDirectoryPathForSubmodule:(FNGitSubmodule *)submodule inRepository:(FNGitRepository *)repository;

+ (NSString *)stringRepresentationForSubmoduleStatus:(FNGitSubmoduleStatus)submoduleStatus;

@end
